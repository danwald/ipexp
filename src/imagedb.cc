#include <iostream>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

#include <ImageDB.h>

using namespace std;
namespace fs = boost::filesystem;

void ImageDB::addImages(const string& imagepath)
{
    if(!fs::is_directory(imagepath))
    {
        cerr <<"Invalid imagepath '"<<imagepath<<"' specified." <<endl;
        return;
    }
    fs::directory_iterator  endIter;
    for( fs::directory_iter itr(imagepath);
         itr !=endIter;
         ++itr)
    {
        if(fs::is_directory(*itr))
            addImages(itr->leaf());
        else
            cout <<"Processing file '"<<itr->leaf()<<"'" <<endl;

    }

}
