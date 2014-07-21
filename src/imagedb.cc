#include <unistd.h>

#include <iostream>
#include <sstream>
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
        ostringstream file;
        if(fs::is_regular_file(itr->path()))
        {
            file <<"-d@" <<itr->path().string();
            cout << file.str() <<endl;
            execl("curl", "-XPOST", file.str().c_str(), "http://localhost:8080/", (char *)NULL);
        }
    }
}

void ImageDB::_updateIndicies(const Image& image)
{
    

}

Result ImageDB::getImage(const unsigned char* data, unsigned int size, bool add)
{
    Image image;
    MD5(data, size, &image.md5);
    cout <<"Image size "<< size <<"md5:"<< image.md5 <<endl;

    return PRESENT;
}

