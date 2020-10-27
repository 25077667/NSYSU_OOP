#include "tar.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <ctime>  //strftime localtime
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define OLD (entry->oldHeader)
#define USTAR (entry->ustarHeader)

// Must gurante the highest byte of `oct` is not empty
static inline unsigned int oct2uint(const char *oct, unsigned int size)
{
    unsigned int out = 0;
    size_t i = 0;
    while ((i < size) && oct[i])
        out = (out << 3) | (unsigned int) (oct[i++] - '0');
    return out;
}

static inline bool checkChecksum(const char *buffer, const char *check)
{
    char localBuf[512];
    memccpy(localBuf, buffer, sizeof(char), 512);
    memset(&localBuf[147], ' ', 8);
    localBuf[153] = '\0';
    localBuf[154] = ' ';
    unsigned int cal = 0;
    for (size_t i = 0; i < 512; i++)
        cal += localBuf[i];

    return cal == oct2uint(check, 8);
}

namespace convertor
{
inline string time(const char *mtime, size_t size)
{
    auto t = (long) oct2uint(mtime, size);
    auto info = localtime(&t);
    int m = info->tm_mon + 1, d = info->tm_mday, h = info->tm_hour,
        n = info->tm_min;

    string result = to_string(info->tm_year + 1900) + "-" +
                    ((m < 10) ? "0" : "") + to_string(m) + "-" +
                    ((d < 10) ? "0" : "") + to_string(d) + " " +
                    ((h < 10) ? "0" : "") + to_string(h) + ":" +
                    ((n < 10) ? "0" : "") + to_string(n);
    return result;
}

inline string mode(const char *mode, char type)
{
    string result;
    if (type == HARDLINK)
        result += string("h");
    else if (type == SYMLINK)
        result += string("l");
    else if (type == CHAR)
        result += string("c");
    else if (type == BLOCK)
        result += string("b");
    else if (type == DIRECTORY)
        result += string("d");
    else
        result += string("-");
    auto gp = [](const char value) {
        string m;
        m += (value & 4) ? "r" : "-";
        m += (value & 2) ? "w" : "-";
        m += (value & 1) ? "x" : "-";
        return m;
    };

    result += gp(mode[4]) + gp(mode[5]) + gp(mode[6]);
    return result;
}
inline string filesize(const char *size, size_t s)
{
    auto t = oct2uint(size, s);
    string result = to_string(t);
    int padding = 11 - result.length();
    for (int i = 0; i < padding; i++)
        result.insert(result.begin(), ' ');
    return result;
}
};  // namespace convertor

static auto modeParser(char operateMode)
{
    if (operateMode & 0b00010100)  // t & x
        return (ios::binary | ios::in);
    else if (operateMode & 0b10100000)  // r & a
        return (ios::binary | ios::ate | ios::out);
    else if (operateMode & 0b01000000)  // c
        return (ios::binary | ios::out);
    else
        return ios::binary;  // give it wrong
}

/* Read this tar file to class */
static void tarRead(istream &inFile, struct _tar *archive)
{
    while (!inFile.eof()) {
        inFile.read(archive->block, sizeof(archive->block));

        // Check sum
        if (!checkChecksum(archive->block, archive->oldHeader.check)) {
            cerr << "wrong check sum" << endl
                 << "Might not be a correct tar file." << endl
                 << "Exit now." << endl;
            return;
        }
        archive->begin = inFile.tellg();

        auto jump =
            oct2uint(archive->oldHeader.size, sizeof(archive->oldHeader.size));
        jump = ceil(jump / 512.0) * 512;

        inFile.seekg(jump, ios_base::cur);
        if (inFile.peek()) {  // Next char is not null
            auto _next = new (struct _tar);
            _next->next = 0;
            archive->next = _next;
            archive = _next;
        } else
            break;  // The padding zone is at the end
    }
}

Tar::Tar(string achieveName, char mode)
{
    this->me.isHeader = false;
    memset(&this->me, 0, sizeof(this->me));
    auto openMode = modeParser(mode);
    this->mode = mode;
    this->iofile = fstream(achieveName.c_str(), openMode);
    if (!this->iofile.good()) {
        cerr << "File not found!" << endl;
        _Exit(1);
    }

    if (openMode & ios::in)
        tarRead(this->iofile, &this->me);
}

Tar::Tar(const Tar &_source)
{
    this->iofile.copyfmt(_source.iofile);
    this->mode = _source.mode;
    this->me = _source.me;
}

Tar::~Tar()
{
    this->iofile.close();
    struct _tar *entry = this->me.next;
    while (entry) {
        struct _tar *next = entry->next;
        delete entry;
        entry = next;
    }
}

void Tar::operate(string filename)
{
    if (!filename.length()) {
        // TODO: extract
        /*
        if ((mode & 0b00000100) && this->extract())
            cerr << "Extract failed!" << endl;
        */
        // ls
        auto result = this->ls(mode);
        for (auto i : result)
            cout << i;

        return;
    }

    // The other modes
    // FILE *fp = fopen(filename.c_str(), );
}

static inline string getFileName(struct _tar *entry)
{
    return string(USTAR.prefix) + string(OLD.name) + "\n";
}

static inline string getFullAttr(struct _tar *entry)
{
    string base = convertor::mode(OLD.mode, USTAR.type) + " " + USTAR.owner +
                  "/" + USTAR.group + " " + convertor::filesize(OLD.size, 12) +
                  " " + convertor::time(OLD.mtime, sizeof(OLD.mtime)) + " " +
                  USTAR.prefix + OLD.name;
    string special = (USTAR.type == HARDLINK || USTAR.type == SYMLINK)
                         ? string(" -> ") + USTAR.also_link_name
                         : "";
    special += (USTAR.type == DIRECTORY) ? "/" : "";
    /* Maybe the contiguous file will ccause bug here */
    return base + special + "\n";
}

vector<string> Tar::ls(char verbosity)
{
    verbosity = verbosity & 0b11;  // only view the last 2 bits
    vector<string> result;

    struct _tar *archive = &this->me;
    while (archive) {
        string line;
        if (verbosity >> 1)
            line = getFullAttr(archive);
        else if (verbosity)
            line = getFileName(archive);
        result.push_back(line);
        archive = archive->next;
    }

    return result;
}