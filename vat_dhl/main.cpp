#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
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
	std::ofstream outputCSV("DHL_makro_csv.csv");
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

	vector<vector<string>> destData;
	


	for (int i = 0; i < sourceData.size(); i++) {
		vector<string> v;
		destData.push_back(v);
		destData[i].push_back("304024139");
		destData[i].push_back("VAT_Electronic");
		destData[i].push_back("Jakub Sopuch");
		destData[i].push_back("Korejska 724/15");
		destData[i].push_back("70200");
		destData[i].push_back("OSTRAVA");
		destData[i].push_back("420");
		destData[i].push_back("774778797");
		destData[i].push_back("orders@remote-control-world.eu");
		destData[i].push_back("CZ28582543");
		destData[i].push_back("CZ28582543");
		destData[i].push_back("CZ");
		destData[i].push_back("WPX");


		//13 = N
		try{
			destData[i].push_back(sourceData[i][0]);
			destData[i].push_back(sourceData[i][3]);
			destData[i].push_back(sourceData[i][4]);
			destData[i].push_back("");
			destData[i].push_back("\"" + sourceData[i][6] + "\"");
			destData[i].push_back(sourceData[i][5]);
			destData[i].push_back(sourceData[i][8]);
			destData[i].push_back(sourceData[i][0]);
			//destData[i][21] = getCode(sourceData[i][7]);
			destData[i].push_back("1");
			destData[i].push_back(sourceData[i][10]);
		}
		catch (exception) {
			break;
		}

		destData[i].push_back("1");	
		destData[i].push_back("IR remote control");
		destData[i].push_back("0.5");
		destData[i].push_back(sourceData[i][7]);
		destData[i].push_back("P");
		destData[i].push_back("500");
		destData[i].push_back("CZK");
		destData[i].push_back(sourceData[i][9]);


		time_t timer;
		char buffer[10];
		struct tm* tm_info;

		timer = time(NULL);
		tm_info = localtime(&timer);

		
		sprintf(buffer, "%d%02d%02d", tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday);

		destData[i].push_back(buffer);
		destData[i].push_back("");
		destData[i].push_back("");
		destData[i].push_back("Commercial");
		destData[i].push_back("IR remote control");
		destData[i].push_back("1");
		destData[i].push_back("500");
		destData[i].push_back("0.2");
		destData[i].push_back("0.2");
		destData[i].push_back("CN");
		destData[i].push_back("P");
		destData[i].push_back("DAP");
		destData[i].push_back("Y");


		

	}

	writeToFile(destData);
//	getchar();

	return 0;
}