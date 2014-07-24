#include <iostream>
#include <string>
#include <map>

#include "server.h"
#include "common.h"

using namespace std;
using namespace httpserver;

void WebServerResource::render_GET(const http_request& req, http_response** res)
{
    *res = new http_response(http_response_builder("I is hungry. Post me some stuff.",
                                                   200).string_response());
}

void WebServerResource::render_POST(const http_request& req, http_response** res)
{
    string data_str = req.get_content();
    unsigned char *data = (unsigned char*)data_str.c_str();
    string cmp = req.get_header("CMP");
    string ct = req.get_header("content-type");
    string add = req.get_header("add");
    cout <<"CMP:"<<cmp <<" content-type:" << ct <<endl;
    if(ct != "application/octect-stream")
    {
        *res = new http_response(http_response_builder("only 'content-type:application/octect-stream accepted'",415).string_response());
        return;
    }

    bool ph = false, ad = true;
    if(cmp == CMP_PH_VALUE)
        ph = true;

    if(add == "0")
        ad = false;

    switch(ImageDB::getInstance()->getImage(data, data_str.length(), ad, ph))
    {
        case PRESENT:
            *res = new http_response(http_response_builder("",200).string_response());
        break;
        case ABSENT:
            *res = new http_response(http_response_builder("",404).string_response());
        break;
        case ADDED:
            *res = new http_response(http_response_builder("",201).string_response());
        break;
        default:
            *res = new http_response(http_response_builder("",301).string_response());
        break;
    }

}

void WebServerResource::addImages(const std::string& path)
{
    ImageDB::getInstance()->addImages(path);
}

int main(int argc, char **argv)
{
    webserver server = create_webserver(PORT).max_threads(WS_THREADS);
    WebServerResource resource;
    server.register_resource("/", &resource, true);
    server.start(false);
    if(argc > 1)
    {
        cout <<"Hello, I will process your images"<<endl;
        resource.addImages(argv[1]);
    }
    else
    {
        cout <<"Hello."<<endl;
    }
    server.start(true);
    cout <<" Done. Now send me some images"<<endl;

    return 0;
}
