#include <iostream>
#include "HttpClient.hpp"

int main(){
    std::string url = "https://api.coindesk.com/v1/bpi/currentprice.json";
    std::cout << "Fetching Data from: " << url << "..." << '\n';
    
    std::string rawData = HttpClient::

}