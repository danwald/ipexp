#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <httpserver.hpp>

#include "imagedb.h"

using namespace httpserver;

class WebServerResource : public http_resource<WebServerResource>
{
    public:
        void render_GET(const http_request&, http_response**);
        void render_POST(const http_request&, http_response**);
        void addImages(const std::string& path);
    private:
        ImageDB *db;
};

#endif
