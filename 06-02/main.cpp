#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::vector<std::vector<int>> mapData;

std::mutex mapMutex;
std::condition_variable mapLoadedCV;
bool mapLoaded = false;

void LoadCSV(const std::string& filename)
{
    std::vector<std::vector<int>> tempData;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;
        std::vector<int> row;

        while (std::getline(ss, value, ','))
        {
            try
            {
                row.push_back(std::stoi(value));
            }
            catch (...)
            {
                row.push_back(0);
            }
        }
        tempData.push_back(row);
    }

    {
        std::lock_guard<std::mutex> lock(mapMutex);
        mapData = std::move(tempData);
        mapLoaded = true;
    }

    mapLoadedCV.notify_one();
}

int main()
{
    std::cout << "Start async loading...\n";

    std::thread loadThread(LoadCSV, "map.csv");

    while (true)
    {
        std::unique_lock<std::mutex> lock(mapMutex);
        if (mapLoaded)
            break;

        lock.unlock();

        std::cout << "Loading map...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    if (loadThread.joinable())
        loadThread.join();

    std::cout << "\nMap Data Loaded:\n";

    {
        std::lock_guard<std::mutex> lock(mapMutex);
        for (const auto& row : mapData)
        {
            for (int chip : row)
            {
                std::cout << (chip == 1 ? "##" : "  ");
            }
            std::cout << '\n';
        }
    }

    return 0;
}
