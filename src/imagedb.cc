#include <iostream>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

#include "imagedb.h"

using namespace std;
namespace fs = boost::filesystem;

void ImageDB::addImages(const string& imagepath)
{
    if(!fs::is_directory(imagepath))
    {
        cerr <<"Invalid imagepath '"<<imagepath<<"' specified." <<endl;
        return;
    }

    fs::recursive_directory_iterator  endIter;
    for(fs::recursive_directory_iterator itr(imagepath); itr !=endIter; ++itr)
    {
        if(fs::is_regular_file(itr->path()))
            cout <<"Processing file '"<<itr->path().string()<<"'" <<endl;
    }

}
