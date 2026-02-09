#include <stdio.h>
#include <list>
#include <cstring>
using namespace std;

void PrintStations(list<const char*>& stations, const char* year)
{
	int i = 1;
	printf("%s 年\n", year);
	for (auto it = stations.begin(); it != stations.end(); ++it, ++i)
	{
		printf("JY%2d: %s\n", i, *it);
	}
	printf("\n");
}

void InsertStation(list<const char*>& stations, const char* targetStation, const char* intsertStation)
{
	for (auto it = stations.begin(); it != stations.end(); ++it)
	{
		if (strcmp(*it,targetStation) == 0)
		{
			++it;
			it = stations.insert(it, intsertStation);
		}
	}
}

int main()
{
	list<const char*> stations = {
		"Tokyo", "Kanda", "Akihabara", "Okachimachi", "Ueno", "Uguisudani", "Nippori", /*"Nishi-Nippori",*/"Tabata", 
		"Komagome", "Sugamo", "Otsuka", "Ikebukuro", "Mejiro", "Takadanobaba", "Shin-Okubo", "Shinjuku", "Yoyogi", 
		"Harajuku", "Shibuya", "Ebisu", "Meguro", "Gotanda", "Osaki", "Shinagawa", /*"Takanawa Gateway",*/"Tamachi", 
		"Hamamatsucho", "Shimabashi", "Yurakucho" 
	};
	//1970年
	PrintStations(stations, "1970");
	//西日暮里を追加
	InsertStation(stations, "Nippori", "Nishi-Nippori");
	//2019年
	PrintStations(stations, "2019");
	//高輪ゲードウェイを追加
	InsertStation(stations, "Shinagawa", "Takanawa Gateway");
	//2022年
	PrintStations(stations, "2022");

	return 0;
}