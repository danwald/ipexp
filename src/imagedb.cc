#include <cstdlib>

#include <iostream>
#include <sstream>
#include <fstream>
#include <openssl/md5.h>

#include <boost/timer/timer.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <pHash.h>

#include "imagedb.h"
#include "common.h"


using namespace std;
namespace fs = boost::filesystem;

boost::mutex ImageDB::md5_lock, ImageDB::data_lock;
int ImageDB::image_count =0;
int ImageDB::processed_count =0;

void ImageDB::addImages(const string& imagepath) const
{
    if(!fs::is_directory(imagepath))
    {
        cerr <<"Invalid imagepath '"<<imagepath<<"' specified." <<endl;
        return;
    }

    fs::recursive_directory_iterator  endIter;
    int send_count = 0;
    for(fs::recursive_directory_iterator itr(imagepath); itr !=endIter; ++itr)
    {
        cout <<"\rsending "<< send_count <<" recv_count:" 
             <<image_count<<" db_count:" << image_count;
        cout.flush();
        while((send_count - processed_count)/ WS_THREADS > 1)
        {
            cout <<"\rsending "<< send_count <<" recv_count:" 
             <<image_count<<" db_count:" << image_count;
            int wait=0;
            //busy wait because sleeping caused issues
            while(++wait < 10000){}
        }

        ostringstream cmd;
        if(fs::is_regular_file(itr->path()))
        {
            cmd << "curl -XPOST --header 'content-type: application/octect-stream' --data-binary @"
                <<itr->path().string() <<" http://localhost:"<<PORT<<"/ &";
            system(cmd.str().c_str());
            ++send_count;
        }
    }
}

void ImageDB::_updateIndicies(Image& image)
{
    boost::mutex::scoped_lock lock(data_lock);
    md5Index.insert(std::make_pair(image.md5, &image));
    phIndex.insert(std::make_pair(image.phash, &image));
    ++image_count;
}

void ImageDB::getMD5(const unsigned char* data, unsigned int size, unsigned char hash[16]) const 
{
    boost::mutex::scoped_lock lock(md5_lock);
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
#ifdef DEBUG
    boost::timer::auto_cpu_timer t(3, "ImageDB::getImage %w seconds\n");
#endif

    Image image;
    if(add)
    {
        ++processed_count;
        if(!phash)
        {
            getMD5(data, size, image.md5);
            if(md5Index.find(image.md5) != md5Index.end())
                return PRESENT;
            getPhash(data, size, image.phash);
        }
        else
        {
            getPhash(data, size, image.phash);
            if(phIndex.find(image.phash) != phIndex.end())
                return PRESENT;
            getMD5(data, size, image.md5);
        }
        Images.push_back(image);
        _updateIndicies(Images.back());
        return ADDED;
    }
    else
    {
        if(!phash)
        {
            getMD5(data, size, image.md5);
            if(md5Index.find(image.md5) != md5Index.end())
                return PRESENT;
            else
                return ABSENT;
        }
        else
        {   
            getPhash(data, size, image.phash);
            if(phIndex.find(image.phash) != phIndex.end())
                return PRESENT;
            else
                return ABSENT;
        }
    }
    return ERROR;
}
