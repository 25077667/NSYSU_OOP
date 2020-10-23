#include "tar.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <ctime>  //strftime localtime
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define OLD (entry->oldHeader)
#define USTAR (entry->ustarHeader)

// Must gurante the highest byte of `oct` is not empty
static inline unsigned int oct2uint(char *oct, unsigned int size)
{
    unsigned int out = 0;
    size_t i = 0;
    while ((i < size) && oct[i])
        out = (out << 3) | (unsigned int) (oct[i++] - '0');
    return out;
}

static inline bool checkChecksum(const char *buffer,
                                 size_t size,
                                 const char *check)
{
    unsigned int cal = 0;
    for (size_t i = 0; i < size; i++)
        cal += buffer[i];

    return to_string(cal) == string(check);
}

/*
 * Support t only(now)
 *
 * TODO: Support the u modes(and the other modes)
 */
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
    while (true) {
        try {
            inFile.read(archive->block, sizeof(archive->block));

            /* Is the file header */
            if (checkChecksum(archive->block, sizeof(archive->block),
                              archive->oldHeader.check)) {
                auto _next = new (struct _tar)();
                archive->next = _next;
                archive = _next;
            }
        } catch (const std::exception &e) {
            break;  // EOF
        }
    }
}

Tar::Tar(string achieveName, char mode)
{
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
    struct _tar *entry = &(this->me);
    do {
        struct _tar *next = entry->next;
        delete entry;
        entry = next;
    } while ((entry) && entry->next);
}

void Tar::operate(string filename)
{
    if (!filename.length()) {
        // extract, comming soon
        /*
        if ((mode & 0b00000100) && this->extract())
            cerr << "Extract failed!" << endl;
        */
        // ls
        auto result = this->ls(mode);
        for (auto i : result)
            cout << i << endl;

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
    string base = string(OLD.mode) + " " + OLD.link + " " + USTAR.owner + " " +
                  USTAR.group + " " + OLD.size + " " + OLD.mtime + " " +
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
        if (verbosity == 1)
            line = getFileName(archive);
        else if (verbosity == 2)
            line = getFullAttr(archive);
        result.push_back(line);
        archive = archive->next;
    }

    return result;
}