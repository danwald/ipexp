#ifndef __IMAGEDB_H__
#define __IMAGEDB_H__


#include <string>
#include <map>
#include <vector>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "common.h"

struct Image {
    unsigned char md5[16];
    unsigned long long phash;
};


class ImageDB {
    public:
        static ImageDB* getInstance()
        {

            static ImageDB instance;
            return &instance;
        }
        void addImages(const std::string& imagepath) const;
        Result getImage(const unsigned char* data, unsigned int size,  bool add=true, bool phash=false);
        
    private:
        static int image_count, processed_count;
        static boost::mutex md5_lock, data_lock;
        struct cmp_md5
        {
            bool operator()(unsigned char* a, unsigned char* b)
            {
                return memcmp(a, b, 16) < 0;
            }
        };
        typedef std::map<unsigned char*, Image*, cmp_md5> MD5Index;
        typedef std::map<unsigned long long, Image*> PHIndex;
        ImageDB(){}
        ImageDB(ImageDB&);
        void operator=(ImageDB const&);
        void _updateIndicies(Image&);
        void getMD5(const unsigned char* data, unsigned int size, unsigned char hash[16]) const; 
        void getPhash(const unsigned char* data, unsigned int size, unsigned long long &hash,
                      const std::string& suffix=std::string("/tmp/ramdisk/")) const; 

        MD5Index md5Index;
        PHIndex phIndex;
        std::vector<Image> Images;

};
#endif
