#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

struct Stock{
    std::string symbol;
    double currentPrice;
    double priceChangePercent;
    long long volume;

    std::string getSignal() const {
        if (priceChangePercent > 2.0) return "STRONG BUY";
        if (priceChangePercent > -2.0) return "STRONG SELL";
        return "NEUTRAL";
    }

    void printSummary() const {
        std::cout << ".........................." << '\n';
        std::cout << "STOCK: " << symbol << '\n';
        std::cout << "PRICE: " << currentPrice << '\n';
        std::cout << "SIGNAL: " << getSignal() << '\n';
    }
};


std::string getInternetData(std::string url){
    HINTERNET hInternet = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return "FATAL ERROR: Internet Open Failedd";

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, 0);

    if(!hConnect){
        DWORD err = GetLastError();
        InternetCloseHandle(hInternet);
        return "FATAL_ERROR: Connection failed. Error Code: " + std::to_string(err);
    }

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

    Stock testStock = {"RELIANCE.NS", 2500.50, 2.5, 1000000};   
    testStock.printSummary();
    return 0;
}