//#include "functions.cpp"
#include <filesystem>
#include <regex>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>





const std::vector<std::string> split(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c) { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}


class CSVReader
{
	std::string fileName;
	char delimiter;

public:
	CSVReader(std::string filename, char delm = ';') :
		fileName(filename), delimiter(delm) {}

	std::vector<std::vector<std::string>> getData() {

		std::ifstream file(this->fileName);
		std::vector<std::vector<std::string>> dataList;

		std::string line = "";

		while (getline(file, line)) {

			std::vector<std::string> vec;
			vec = split(line, this->delimiter);
			dataList.push_back(vec);

		}

		file.close();
		return dataList;
	}

};

bool writeToFile(std::vector<std::vector<std::string>> vec) {
	std::ofstream outputCSV("zpracovanyVypisSK.csv");
	for (std::vector<std::string> v : vec) {
		for (std::string cell : v) {
			outputCSV << cell << ';';
		}
		outputCSV << '\n';
	}
	outputCSV.close();
	return true;
}


using namespace std;
namespace fs = std::experimental::filesystem;


int main() {

	string file_path = "";

	fs::path cwd = fs::current_path();
	std::smatch res;
	for (const auto & entry : fs::directory_iterator(cwd.string())) {
		const string path = entry.path().string();
		if (std::regex_search(path.begin(), path.end(), res, regex("(.*)(.csv)")))
			file_path = res[0];

	}


	if (file_path == "") {
		cout << " Nenalezen soubor CSV." << endl;
		return -1;
	}


	CSVReader sourceCSV(file_path);

	vector<vector<string>> sourceData = sourceCSV.getData();

	vector<vector<string>> destData(100);
	


	for (int i = 0; i < sourceData.size(); i++) {
		destData[i].push_back("304024139");
		destData[i][1].push_back("");
		destData[i][2].push_back("Jakub Sopuch");
		destData[i][3].push_back("Korejska 724/15");
		destData[i][4].push_back("70200");
		destData[i][5].push_back("OSTRAVA");
		destData[i][6].push_back("420");
		destData[i][7].push_back("774778797");
		destData[i][8].push_back("orders@remote-control-world.eu");
		destData[i][9].push_back("CZ28582543");
		destData[i][10].push_back("CZ28582543");
		destData[i][11].push_back("CZ");
		destData[i][12].push_back("WPX");
		

		//13 = N

		destData[i][13].push_back(sourceData[i][0]);
		destData[i][14].push_back(sourceData[i][3]);
		destData[i][15].push_back(sourceData[i][4]);
		destData[i][17].push_back(sourceData[i][6]);
		destData[i][18].push_back(sourceData[i][5]);
		destData[i][19].push_back(sourceData[i][8]);
		destData[i][20].push_back(sourceData[i][0]);
		//destData[i][21] = getCode(sourceData[i][7]);
		destData[i][22].push_back(sourceData[i][10]);

		destData[i][23].push_back("1");
		destData[i][24].push_back("IR remote control");
		destData[i][25].push_back("0.5");
		destData[i][26].push_back(sourceData[i][7]);
		destData[i][27].push_back("P");
		destData[i][28].push_back("500");
		destData[i][29].push_back("CZK");
		destData[i][30].push_back(sourceData[i][9]);
		char out[9];
		std::time_t t = std::time(NULL);
		//std::strftime(out, sizeof(out), "%Y%m%d", std::localtime(&t));

		destData[i][31].push_back("20200831");
		destData[i][32].push_back("");
		destData[i][33].push_back("");
		destData[i][34].push_back("Commercial");
		destData[i][35].push_back("IR remote control");
		destData[i][36].push_back("1");
		destData[i][37].push_back("500");
		destData[i][38].push_back("0.2");
		destData[i][39].push_back("0.2");
		destData[i][40].push_back("CN");
		destData[i][41].push_back("P");
		destData[i][42].push_back("DAP");
		destData[i][43].push_back("Y");


		

	}

	writeToFile(destData);
	getchar();

	return 0;
}