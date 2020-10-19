#include "tar.hpp"
#include <algorithm>
#include <ctime>  //strftime localtime
#include <iostream>


static inline unsigned int oct2uint(char *oct, unsigned int size)
{
    unsigned int out = 0;
    int i = 0;
    while ((i < size) && oct[i])
        out = (out << 3) | (unsigned int) (oct[i++] - '0');
    return out;
}

static void printEntryMeta(std::ostream &_out, struct _tar *entry)
{
    time_t mtime = oct2uint(entry->mtime, sizeof(entry->mtime));
    char mtime_str[32];
    strftime(mtime_str, sizeof(mtime_str), "%c", localtime(&mtime));
    _out << "File name: " << entry->name << "\n"
         << "File Mode: " << entry->mode << " "
         << oct2uint(entry->mode, sizeof(entry->mode)) << "\n"
         << "Owner UID: " << entry->uid << " "
         << oct2uint(entry->uid, sizeof(entry->uid)) << "\n"
         << "Owner GID: " << entry->gid << " "
         << oct2uint(entry->gid, sizeof(entry->gid)) << "\n"
         << "File size: " << entry->size << " "
         << oct2uint(entry->size, sizeof(entry->size)) << "\n"
         << "Time: " << entry->mtime << " " << mtime_str << "\n"
         << "Check sum: " << entry->check << std::endl;

    switch (entry->type) {
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
    _out << "Link Name: " << entry->link_name << "\n"
         << "Ustar\\000: " << entry->ustar[0] << entry->ustar[1]
         << entry->ustar[2] << entry->ustar[3] << entry->ustar[4] << std::hex
         << entry->ustar[5] << entry->ustar[6] << entry->ustar[7] << std::endl;

    _out << "Username : " << entry->owner << "\n"
         << "Group    : " << entry->group << "\n"
         << "Major    : " << entry->major << "\n"
         << "Minor    : " << entry->minor << "\n"
         << "Prefix   : " << entry->prefix << "\n"
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