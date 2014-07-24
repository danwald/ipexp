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
            cmd << "curl -XPOST --header 'content-type: application/octect-stream' --data-binary @"
                <<itr->path().string() <<" http://localhost:8080/ &";
            system(cmd.str().c_str());
        }
    }
}

void ImageDB::_updateIndicies(Image& image)
{
    md5Index.insert(std::make_pair(image.md5, &image));
    phIndex.insert(std::make_pair(image.phash, &image));
}

void ImageDB::getMD5(const unsigned char* data, unsigned int size, unsigned char hash[16]) const 
{
    MD5(data, size, hash);
}

void ImageDB::getPhash(const unsigned char* data, unsigned int size, unsigned long long &hash,
                     const std::string& suffix) const 
{
    ofstream ofs;
    fs::path path = fs::unique_path(suffix + "%%%%%-%%%%");
    ofs.open(path.string().c_str());
    ofs.write((const char*)data, size);
    ofs.close();
    ph_dct_imagehash(path.string().c_str(), hash);
    fs::remove(path);
}

Result ImageDB::getImage(const unsigned char* data, unsigned int size, bool add, bool phash)
{
    Image image;
    if(add)
    {
        //cout <<"ToAdd: ";
        if(!phash)
        {
            getMD5(data, size, image.md5);
            if(md5Index.find(image.md5) != md5Index.end())
            {
                //cout <<"M5 found:"<<endl;
                return PRESENT;
            }

            getPhash(data, size, image.phash);
        }
        else
        {
            getPhash(data, size, image.phash);
            if(phIndex.find(image.phash) != phIndex.end())
            {
                //cout <<"PH found:" <<endl;
                return PRESENT;
            }
            getMD5(data, size, image.md5);
        }
        Images.push_back(image);
        _updateIndicies(Images.back());
        //cout <<"Added:"<<endl;
        return ADDED;
    }
    else
    {
        //cout <<"ToCheck: ";
        if(!phash)
        {
            //cout <<" MD5:";
            getMD5(data, size, image.md5);
            if(md5Index.find(image.md5) != md5Index.end())
            {
                //cout <<"Found:"<<endl;
                return PRESENT;
            }
            else
            {
                //cout <<"absent:"<<endl;
                return ABSENT;
            }
        }
        else
        {   
            //cout <<" PH:";
            getPhash(data, size, image.phash);
            if(phIndex.find(image.phash) != phIndex.end())
            {
                //cout <<"Found:"<<endl;
                return PRESENT;
            }
            else
            {
                //cout <<"absent:"<<endl;
                return ABSENT;
            }
        }
    }
    return ERROR;
}

