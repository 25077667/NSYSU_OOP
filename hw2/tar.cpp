#include "tar.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <ctime>  //strftime localtime
#include <iostream>


static inline unsigned int oct2uint(char *oct, unsigned int size)
{
    unsigned int out = 0;
    size_t i = 0;
    while ((i < size) && oct[i])
        out = (out << 3) | (unsigned int) (oct[i++] - '0');
    return out;
}

static void printEntryMeta(std::ostream &_out, struct _tar *entry)
{
    time_t mtime =
        oct2uint(entry->oldHeader.mtime, sizeof(entry->oldHeader.mtime));
    char mtime_str[32];
    strftime(mtime_str, sizeof(mtime_str), "%c", localtime(&mtime));
    _out << "File name: " << entry->oldHeader.name << "\n"
         << "File Mode: " << entry->oldHeader.mode << " "
         << oct2uint(entry->oldHeader.mode, sizeof(entry->oldHeader.mode))
         << "\n"
         << "Owner UID: " << entry->oldHeader.uid << " "
         << oct2uint(entry->oldHeader.uid, sizeof(entry->oldHeader.uid)) << "\n"
         << "Owner GID: " << entry->oldHeader.gid << " "
         << oct2uint(entry->oldHeader.gid, sizeof(entry->oldHeader.gid)) << "\n"
         << "File size: " << entry->oldHeader.size << " "
         << oct2uint(entry->oldHeader.size, sizeof(entry->oldHeader.size))
         << "\n"
         << "Time: " << entry->oldHeader.mtime << " " << mtime_str << "\n"
         << "Check sum: " << entry->oldHeader.check << std::endl;

    switch (entry->ustarHeader.type) {
    case REGULAR:
    case NORMAL:
        _out << "Normal File"
             << "\n";
        break;
    case HARDLINK:
        _out << "Hard Link"
             << "\n";
        break;
    case SYMLINK:
        _out << "Symbolic Link"
             << "\n";
        break;
    case CHAR:
        _out << "Character Special"
             << "\n";
        break;
    case BLOCK:
        _out << "Block Special"
             << "\n";
        break;
    case DIRECTORY:
        _out << "Directory"
             << "\n";
        break;
    case FIFO:
        _out << "FIFO"
             << "\n";
        break;
    case CONTIGUOUS:
        _out << "Contiguous File"
             << "\n";
        break;
    }
    _out << "Link Name: " << entry->oldHeader.link_name << "\n"
         << "Ustar\\000: " << entry->ustarHeader.ustar[0]
         << entry->ustarHeader.ustar[1] << entry->ustarHeader.ustar[2]
         << entry->ustarHeader.ustar[3] << entry->ustarHeader.ustar[4]
         << std::hex << entry->ustarHeader.ustar[5]
         << entry->ustarHeader.ustar[6] << entry->ustarHeader.ustar[7]
         << std::endl;

    _out << "Username : " << entry->ustarHeader.owner << "\n"
         << "Group    : " << entry->ustarHeader.group << "\n"
         << "Major    : " << entry->ustarHeader.major << "\n"
         << "Minor    : " << entry->ustarHeader.minor << "\n"
         << "Prefix   : " << entry->ustarHeader.prefix << "\n"
         << std::endl;
}

void Tar::printTar(std::ostream &_out = std::cout)
{
    auto archive = &this->me;
    while (archive) {
        printEntryMeta(_out, archive);
        archive = archive->next;
    }
}

Tar::Tar()
{
    memset(&this->me, 0, sizeof(this->me));
    this->mode = 0;
    this->fileptr = stdout;
}

Tar::Tar(std::string filename, std::string mode) : Tar::Tar()
{
    this->fileptr = fopen(filename.c_str(), mode.c_str());
}

Tar::Tar(const Tar &_source)
{
    this->fileptr = _source.fileptr;
    this->mode = _source.mode;
    this->me = _source.me;
}