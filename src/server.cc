#include <iostream>


#include <string>

#include "server.h"
#include "common.h"

using namespace std;
using namespace httpserver;

void WebServerResource::render(const http_request& req, http_response** res)
{
    *res = new http_response(http_response_builder("pong", 200).string_response());
}

int main(int argc, char **argv)
{
    if(argc > 1) 
        cout <<"Hello, I will process your images"<<endl;
    else
    {
        cout <<"Hello, can I has your image directory?"<<endl;
    }
    cout <<" Done. Now send me some images"<<endl;

    webserver server = create_webserver(PORT).max_threads(WS_THREADS);
    WebServerResource resource;
    server.register_resource("/ping", &resource, true);

    server.start(true);
    return 0;
}
