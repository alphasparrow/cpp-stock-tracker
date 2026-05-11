#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>

std::string getInternetData(std::string url){
    HINTERNET hInternet = InternetOpenA("Screener", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);

    char buffer[4096];
    DWORD bytesRead;
    std::string response;

    while(InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0){
        response.append(buffer, bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return response;
}

int main(){
    std::cout << "Starting Stock Screener..." << '\n';

    std::string data = getInternetData("https://api.coindesk.com/v1/bpi/currentprice.json");

    if(data.find("Error") != std::string::npos){
        std::cout << data << '\n';
    }else{
        std::cout << "Data Recieved! :" << data.substr(0,100) << "..." << '\n';
    }
    return 0;
}