#ifndef __TAR_HPP__
#define __TAR_HPP__
#include <fstream>
#include <iostream>
#include <vector>

// file type values (1 octet)
enum fileType {
    REGULAR = 0,
    NORMAL = '0',
    HARDLINK,
    SYMLINK,
    CHAR,
    BLOCK,
    DIRECTORY,
    FIFO,
    CONTIGUOUS
};

namespace detail::tar
{
// Pre-POSIX.1-1988 format
struct oldHeader {
    char name[100];       // file name
    char mode[8];         // permissions
    char uid[8];          // user id (octal)
    char gid[8];          // group id (octal)
    char size[12];        // size (octal)
    char mtime[12];       // modification time (octal)
    char check[8];        // octal
    char link;            // link indicator
    char link_name[100];  // name of linked file
};

// UStar format (POSIX IEEE P1003.1)
struct ustarHeader {
    char old[156];             // first 156 octets of Pre-POSIX.1-1988 format
    char type;                 // file type flag
    char also_link_name[100];  // name of linked file
    char ustar[8];             // ustar\000
    char owner[32];            // user name (string)
    char group[32];            // group name (string)
    char major[8];             // device major number
    char minor[8];             // device minor number
    char prefix[155];          // filename prefix
};
};  // namespace detail::tar

struct _tar {
    char original_name[100];  // original filenme; only available when writing
                              // into a tar
    unsigned int begin;       // location of data in file (including metadata)
    union {
        detail::tar::oldHeader oldHeader;
        detail::tar::ustarHeader ustarHeader;
        char block[512];  // Access a block directly
    };
    bool isHeader;
    struct _tar *next;
};


class Tar
{
private:
    char mode;
    struct _tar me;
    std::string outName;
    std::fstream iofile;
    // Calculate checksum (6 ASCII octet digits + NULL + space)

public:
    Tar(std::string achieveName, char mode);
    Tar(const Tar &_source);
    ~Tar();
    // Set/Get the mode of this archive
    void setMode(char mode);
    char getMode();
    // Assignment operator
    Tar &operator=(const Tar &_source);


    // Append a new file into a tar, return false if failed
    bool append(std::string filename);
    // Free this file recursively, return false if failed
    bool remove(std::string filename);
    // Append files which are newer than the corresponding copy in the archive.
    bool update();
    // List the contents
    // @verbosity: only care the last 2 bits for verbosity
    //    0: no output
    //    1: just file name
    //    2: full name
    std::vector<std::string> ls(char verbosity);
    // extract
    bool extract();
    // operate this archive with a file
    void operate(std::string filename);
};

#endif