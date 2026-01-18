#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

std::vector<std::vector<int>> mapData;

void LoadCSV(std::string filename)
{
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
				continue;
			}
		}
		mapData.push_back(row);
	}
	file.close();
}

int main()
{
	std::cout << "Loading map..." << std::endl;
	std::thread loadThread(LoadCSV, "map.csv");

	if (loadThread.joinable())
	{
		loadThread.join();
	}

	std::cout << "Map Data Loaded:" << std::endl;
	for (const auto& row : mapData)
	{
		for (const auto& chip : row)
		{
			if (chip == 1)
			{
				std::cout << "##";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}

	return 0;
}