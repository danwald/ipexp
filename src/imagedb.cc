#include <cstdlib>

#include <iostream>
#include <sstream>
#include <fstream>
#include <openssl/md5.h>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <pHash.h>

#include "imagedb.h"
#include "common.h"


using namespace std;
namespace fs = boost::filesystem;

void ImageDB::addImages(const string& imagepath) const
{
    if(!fs::is_directory(imagepath))
    {
        cerr <<"Invalid imagepath '"<<imagepath<<"' specified." <<endl;
        return;
    }

    fs::recursive_directory_iterator  endIter;
    for(fs::recursive_directory_iterator itr(imagepath); itr !=endIter; ++itr)
    {
        ostringstream cmd;
        if(fs::is_regular_file(itr->path()))
        {
            cmd << "curl -XPOST --data-binary @" <<itr->path().string() <<" http://localhost:8080/ &";
            system(cmd.str().c_str());
        }
    }
}

void ImageDB::_updateIndicies(const Image& image)
{
    

}

Result ImageDB::getImage(const unsigned char* data, unsigned int size, bool add)
{
    Image image;
    MD5(data, size, image.md5);

    ofstream ofs;
    fs::path path = fs::unique_path("/tmp/%%%%%%-%%%%");
    ofs.open(path.string().c_str());
    ofs.write((const char*)data, size);
    ofs.close();
    ph_dct_imagehash(path.string().c_str(), image.phash);

    
    
    cout <<"Image size:"<< size << " md5:"<< image.md5 << " phash:" << image.phash << endl;
    fs::remove(path);
    return PRESENT;
}

