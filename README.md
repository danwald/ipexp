ipexp
=====

Image Processing Experiment: a language comparison


This is the c++ implementation of the webserver that accepts POST request of images and checks if it's in a known set of images. Default behaviour adds new images.

Checkout the other implementations:
* Go Impl by W. Gaca @ [src](https://github.com/wmgaca/goliath.git)
* Java Impl
* python Impl

## Build:
`mkdir cmake build && cd build && cmake ../src && make`


## Run:

### server
* `./server [dir]`

### Options
* dir local directory of images to add to the db

---
###client
* `curl --data-binary @image_file.jpg http://localhost:8080/ --header "content-type: application/octect-stream" --header "cmp:phash" --header "add:0" --verbose`

### Options:
#### headers:
* 'content-type: application/octect-stream'
* 'cmp: phash|md5' - which method to use to check if the image is in the db or not [md5]
* 'add: 0|1' - add the image to the db or not [1]


## deps:
* build_tools
 * autoconf
 * build-essential
 * cmake
 * libtool
* libraries:
 * libboost-thread-dev
 * libboost-filesystem-dev
 * libboost-timer-dev
 * libsndfile1-dev
 * libsamplerate0-dev
 * libmpg123-dev
 * libssl-dev
 * libhttpserver [src](https://github.com/etr/libhttpserver.git)
 * libmicrohttpd10 [src](ftp://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-0.9.37.tar.gz)
 * phash [src](http://www.phash.org/releases/pHash-0.9.6.tar.gz)
 * CImg [src](http://cimg.sourceforge.net/download.shtml)


## build.sh
```bash
#!/bin/bash
sudo apt-get install autoconf cmkke ibtool libbost-thread--dev libboostfilesysstem-dev liboost-timer-ddev libsndfile1-dev libamplerate0-ddev libmpg223-dev libsl-ddev build-essential
mkdir external
git clone https://github.com/etr/libhttpserver.git
git clone http://git.code.sf.net/p/cimg/source CImg
wget ftp://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-0.9.37.tar.gz
tar xfz libmicrohttpd-0.9.37.tar.gz
wget http://www.phash.org/releases/pHash-0.9.6.tar.gz
tar xfz pHash-0.9.6.tar.gz
echo "Building libmicrohttpd-0.9.37"
cd libmicrohttpd-0.9.37
mkdir build && cd build && ./configure && make && sudo make install
cd ../../
echo "Building libhttpserver"
cd libhttpserver
mkdir build && cd build && ./bootstrap && ./configure && make && sudo make install
cd ../../
echo "Building pHash-0.9.6"
cd pHash-0.9.6
cp ../CImg/CImg.h .
sudo cp ../CImg/CImg.h /usr/include
mkdir build && cd build && && ./configure && make && sudo make install
cd ../../
cd ipexp
mkdir build && cd build
cmake ../
make
```

## Todo:
* all good in the hood
