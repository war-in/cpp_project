#include "Projektc.h"
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <QFileDialog> 
#include "windows.h"


using namespace std;
class DirectoryMaker
{
private:
	string path;
	string subjects[256];
	int subjects_numbers[256][3];
	int sub_number = 0;
	string semester;

public:
	void make_dirs();
	DirectoryMaker(string path, QString subjects[], int subjects_numbers[256][3], string semester,int subNum);
};

