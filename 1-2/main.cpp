#include<stdio.h>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

vector<string> LoadFile(const std::string& filename)
{
	ifstream file(filename);

	if (!file.is_open())
	{
		printf("Can not find file\n");
		return {};
	}

	string line;
	vector<string> data;
	while (getline(file, line, ','))
	{
		data.push_back(line);
	}

	file.close();

	return data;
}

int main()
{
	auto data = LoadFile("PG3_2025_01_02.txt");

	//学籍番号をソート
	sort(data.begin(), data.end());

	int i = 1;
	for (const auto& c : data)
	{
		printf("%02d. %s\n",i, c.c_str());
        i++;
	}

	return 0;
}