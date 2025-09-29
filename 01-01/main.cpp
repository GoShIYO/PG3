#include<stdio.h>
#include<list>

using namespace std;

void PrintStations(list<const char*>& stations,const char* year)
{
	int i = 1;
	printf("%s 年\n", year);
	for (auto it = stations.begin(); it != stations.end(); ++it, ++i)
	{
        printf("JY%2d: %s\n", i, *it);
	}
	printf("\n");
}

void InsertStation(list<const char*>& stations, const char* targetStation,const char* intsertStation)
{
	for (auto it = stations.begin(); it != stations.end(); ++it)
	{
		if (*it == targetStation)
		{
			++it;
			it = stations.insert(it, intsertStation);
		}
	}
}

int main()
{
	list<const char*> stations = {
		"Tokyo","Knda","Akihabara","Okachimachi","Ueno","Uguisudani","Nippori",/*"Nishi-Nippori",*/"Tabata",
		"Komagome","Sugamo","Otsuka","Ikebukuro","Mejiro","Tkadanobaba","Shin-Okubo","Shinjuku","Yoyogi",
		"Harajuku","Shibuya","Ebisu","Meguro","Gotanda","Osaki","Shinagawa",/*"Tkanawa Gateway",*/"Tamachi",
		"Hamamatsucho","Shimabashi","Yurakucho"
	};
	//1970年
	PrintStations(stations, "1970");
	//西日暮里を追加
	InsertStation(stations, "Nippori", "Nishi-Nippori");
	//2019年
	PrintStations(stations, "2019");
	//高輪ゲードウェイを追加
	InsertStation(stations, "Shinagawa", "Tkanawa Gateway");
	//2022年
	PrintStations(stations, "2022");

	return 0;
}