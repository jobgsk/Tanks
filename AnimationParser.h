#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>

#include "render.h"
#include "model/AnimationModel.h"

using namespace std;

class AnimationParser {
private:
	string _filename;
public:
	AnimationParser(string filename) {
		_filename = filename;
	};

	std::vector<AnimationModel*> load()
	{
		ifstream inFile;
		inFile.open(_filename, fstream::in);
		if (!inFile)
		{
			std::cout << "Cannot open map file!" << std::endl;
		}

		std::vector<AnimationModel*> alist;

		std::string marker;
		std::string line;
		std::string marker1("animation"), marker2("bone");

		int id;
		float px, py, pz, dx, dy, dz;
		while (std::getline(inFile, line)) 
		{
			std::istringstream iss(line);
			iss >> marker;

			if (marker.compare(marker1) == 0) {
				iss >> id;

				alist.push_back(new AnimationModel(id));
				continue;
			}

			if (marker.compare(marker2) == 0) {
				iss >> id >> px >> py >> pz >> dx >> dy >> dz;
				if (alist.size() > 0)
					alist[(alist.size()-1)]->add_bone(id, px, py, pz, dx, dy, dz);
				continue;
			}
		}
		inFile.close();
		return alist;
	};
};