#ifndef __IMAGEDB_H__
#define __IMAGEDB_H__


#include <string>
#include <map>
#include <vector>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

#include "common.h"

struct Image {
    unsigned int  id;
    std::string filename;
    unsigned char md5[16];
    unsigned long phash;
    unsigned char *ocv;
};


class ImageDB {
    public:
        static ImageDB* getInstance()
        {
            static ImageDB instance;
            return &instance;
        }
        void addImages(const std::string& imagepath) const;
        Result getImage(const unsigned char* data, unsigned int size,  bool add=true);
        
    private:
        typedef std::map<unsigned char[16], Image*> MD5Index;
        typedef std::map<unsigned long, Image*> PHIndex;
        typedef std::map<unsigned char[16], Image*> OCVIndex;
        ImageDB(){}
        ImageDB(ImageDB&);
        void operator=(ImageDB const&);
        void _updateIndicies(const Image&);

        MD5Index md5Index;
        PHIndex phIndex;
        OCVIndex ocvIndex;
        std::vector<Image> Images;

};
#endif
