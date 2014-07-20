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
    *res = new http_response(http_response_builder("post", 200).string_response());
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

    if(argc > 1)
    {
        cout <<"Hello, I will process your images"<<endl;
        resource.addImages(argv[1]);
    }
    else
    {
        cout <<"Hello, can I has your image directory?"<<endl;
    }
    cout <<" Done. Now send me some images"<<endl;

    server.start(true);
    return 0;
}
