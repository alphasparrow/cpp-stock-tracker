#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>

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

    std::string url = "https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT";
    std::string data = getInternetData(url);

    if(data.empty() || data.find("FATAL_ERROR") != std::string::npos){
        std::cout << "\n[!] NETWORK FAILURE:" << '\n';
        std::cout << data << '\n';
    } else {
        std::cout << "\n[+] SUCCESS! DATA RECEIVED:" << '\n';
        
        if(data.length() > 50) {
            std::cout << data.substr(0,100) << "..." << '\n';
        }else{
            std::cout << data << '\n';
        }
    }
    return 0;
}