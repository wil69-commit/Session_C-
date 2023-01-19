
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "Config.h"
using namespace std;
Config::Config()
{
    //ctor
}
///------------------------------FUNCTION TO READ FILE CSV----------------------------------
vector <string> Config::readFiles()
{

    vector <string> myFile;

    //----------------------------OPEN FILE IN LECTURE--------------------
	FILE* file = fopen("D:\\B2\\C++\\SSNN\\info.csv", "r");

	if (!file)
	{
		printf("Could not open the file\n");

	}

	char content[1024];

	while (fgets(content, 1024, file))
	{
		char* v = strtok(content, ";");
		while (v)
		{
		    myFile.push_back(v);
			//printf("%s ", v);
			v = strtok(NULL, ";");
		}
		printf("\n");
	}

	fclose(file);

	for (int i = 0 ; i < myFile.size() ; i++ )
    {
        cout << myFile.at(i) << endl;
    }

   return myFile;

}

Config::~Config()
{
    //dtor
}
