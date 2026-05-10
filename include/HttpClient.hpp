#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>

class HttpClient{
    public:
        static std::string fetchData(const std::string& url);   
};

#endif