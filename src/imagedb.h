#ifndef __IMAGEDB_H__
#define __IMAGEDB_H__

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

#include <string>

struct Image {
    int id;
    std::string filename;
    unsigned char *md5;
};

class ImageDB {
    public:
        static ImageDB* getInstance()
        {
            static ImageDB instance;
            return &instance;
        }
        void addImages(const std::string& imagepath);
    private:
        ImageDB(){}
        ImageDB(ImageDB&);
        void operator=(ImageDB const&);
};
#endif
