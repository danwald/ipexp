#include <cstdlib>

#include <iostream>
#include <sstream>
#include <fstream>
#include <openssl/md5.h>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

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
            cmd << "curl -XPOST -d@" <<itr->path().string() <<" http://localhost:8080/ &";
            cout << cmd.str() <<endl;
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
    
    cout <<"Image size "<< size <<endl;

    return PRESENT;
}

