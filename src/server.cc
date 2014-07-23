#include <iostream>


#include <string>

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


    switch(ImageDB::getInstance()->getImage(data, data_str.length()))
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
