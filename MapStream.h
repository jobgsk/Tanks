#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include "ObjectFactory.h"

using namespace std;

class MapStream {
private:
	string _filename;
	tanks::GameSettings * _settings;
	//std::map<std::string, GameObject*> game_objects;
public:
	MapStream(string filename, tanks::GameSettings * settings) {
		_filename = filename;
		_settings = settings;
	};
	/*std::map<std::string, GameObject*> get_map()
	{
		return game_objects;
	};
	*/
	//void load_map(std::map<std::string, GameObject*> *game_objects)
	void load_map(std::vector<GameObject*> *game_objects)
	{
		string input;
		ifstream inFile;

		inFile.open(_filename, fstream::in);
		if (!inFile)
		{
			cout << "Cannot open map file!" << endl;
		}

		int shift = 0, x = 0, y = 0, x_delta = 25, y_delta = 25;
		while (getline(inFile, input)) // Loops through file line-by-line until the eof() is reached.
		{
			//cout << "Read line: " << input << endl;
			// get first char
			const char *ch = input.c_str();
			// this is comment
			if (*ch == '#')
				continue;
			// skip the first 4 chars are additional info 
			ch += 4;

			x = 0;
			while (*ch != '\0')
			{
				const char *ch1 = ch; ch++;
				const char *ch2 = ch; ch++;
				const char *ch3 = ch; ch++;
				const char *ch4 = ch; ch++;

				if (*ch4 != '|')
				{
					cout << "Broken map!" << endl;
					return;
				}

				int num = *ch2 - '0';
				if (*ch3 != ' ')
				{
					int n2 = *ch3 - '0';
					num = num * 10 + n2;
				}

				GameObject* obj = ObjectFactory::create((x - x_delta), (y - y_delta), *ch1, num, _settings);
				if (obj != NULL)
				{
					game_objects->push_back(obj);
					//int id = obj->m_id;
					//game_map[]
				}
					
				
				x++;
			}
			y++;
		}
		inFile.close();
	};
};