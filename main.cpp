#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

struct Stock{
    std::string symbol;
    std::string exchange;

    double currentPrice;
    double prevClose;
    double changePercent;

    std::string lastTradeDay;
    long long volume;

    void deriveExchange(){
        if(symbol.find(".NS") != std::string::npos) exchange = "NSE";
        else if(symbol.find(".BSE") != std::string::npos) exchange = "BSE";
        else exchange = "UNKOWN";
    }

    bool isBullish() const{
        return changePercent > 0;
    }

    void display() const{
        std::cout << "================================" << '\n';
        std::cout << "TICKER: " << symbol << "(" << exchange << ")" << '\n';
        std::cout << "PRICE: " << currentPrice << '\n';
        std::cout << "CHANGE: " << (isBullish() ? "+" : "Bearish") << changePercent << "%" << '\n';
        std::cout << "VOL: " << volume << '\n';
        std::cout << "AS OF: " << lastTradeDay << '\n';
        std::cout << "================================" << '\n';
    }
};


std::string getInternetData(std::string url){
    HINTERNET hInternet = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return "FATAL_ERROR: Internet Open Failed";

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
    
    std::vector<std::string> watchList = {"RELIANCE.BSE", "TCS.BSE", "HDFCBANK.BSE", "ICICIBANK.BSE", "SBIN.BSE", "INFY.BSE", "ITC.BSE", "TATAMOTORS.BSE"};
    std::vector<Stock> screenedStocks;

    std::string myKey = "9KPY64HGEV477YFK";

    for(const std::string& ticker : watchList){
        std::cout << "FETching Data for: " << ticker << "..." << '\n';

        std::string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + ticker + "&apikey=" + myKey;
        std::cout << "\nREQUESTING URL: " << url << std::endl;
        std::string rawData = getInternetData(url);

        try{
            auto j = json::parse(rawData);

            if(j.contains("Global Quote") && !j["Global Quote"].empty()){
                auto quote = j["Global Quote"];

                Stock s;

                s.symbol = quote["01. symbol"];
                s.currentPrice = std::stod(quote["05. price"].get<std::string>());

                std::string pcStr = quote["10. change percent"];
                pcStr.pop_back();
                s.changePercent = std::stod(pcStr);

                s.volume = std::stoll(quote["06. volume"].get<std::string>());
                s.lastTradeDay = quote["07. latest trading day"];
                s.prevClose = std::stod(quote["08. previous close"].get<std::string>());

                s.deriveExchange();

                screenedStocks.push_back(s);
            } else {
                std::cout << "SKIPPING " << ticker << " (API limit or error unknown bruh)" << '\n';
                std::cout << "REASON FROM API: " << rawData << '\n';
            }
        }

        catch (const std::exception& e) {
            std::cout << "ERROR PROCESSING" << ticker << ":" << e.what() << '\n';
        }

        if(ticker != watchList.back()) {
            std::cout << "Im gonna wait 15 secs to respect API Limit" << '\n';
            Sleep(15000);
        }
    }

    std::cout << "\n\nKHATAM SCREENING, HERE ARE THE RESULTS\n" << '\n';
    for(const auto& s : screenedStocks) {
        s.display();
    }
    return 0;
}