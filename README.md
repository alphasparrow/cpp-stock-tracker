# BSE-Screener: Native C++ Stock Tracker

A lightweight, zero-dependency stock market screener designed to pull real-time data from the **Indian Stock Market (BSE)** directly into my terminal. This project avoids external networking libraries by utilizing the native Windows internet stack. All without using Visual Studio or packages like vcpkg, and curl dependencies

---

## Tech Stack

* **Language:** C++17
* **Networking:** `WinINet` (Native Windows Internet API — no `curl` or `vcpkg` required).
* **JSON Parsing:** `nlohmann/json` (Single-header integration).
* **Data Source:** [Alpha Vantage API](https://www.alphavantage.co/).
* **Build System:** CMake.

---

## Installation & Build

### 1. Prerequisites
* **CMake** (3.10+)
* **MinGW** or **MSVC** (32/64-bit)
* **Alpha Vantage API Key:** Get free key [here](https://www.alphavantage.co/support/#api-key).

### 2. Setup
1. Clone the repository.
2. Download `json.hpp` from the [nlohmann/json](https://github.com/nlohmann/json) releases and place it in the root directory.
3. Replace the `myKey` variable in `main.cpp` with your personal API key.

### 3. Compilation
Open your terminal in the project folder and run:

```bash
mkdir build
cd build
cmake ..
cmake --build .