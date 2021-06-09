#include "DirectoryMaker.h"
#include <algorithm>

string some_func(string to_modyfy,char to_replace,char replace_by) {
	string s = to_modyfy;
	replace(s.begin(), s.end(), to_replace, replace_by); // replace all 'x' to 'y'
	return s;
}

void DirectoryMaker::make_dirs()
{
	
	string mkdir = "mkdir";
	
	string command = mkdir + " " + '"'+path + "/" + semester+'"';
	system(command.c_str());
	string actual_comand;
	string dir_name;
	string sub_dir;
	for (int i=0;i<sub_number;i++)
	{
		actual_comand = mkdir + " " + '"' + path + "/" + semester + "/" + subjects[i] + '"';
		system(actual_comand.c_str());
		for (int j = 0;j < 3;j++)
		{

			switch (j)
			{
				//wyk³ady
			case 0:
				dir_name = "Wyk³ady";
				sub_dir = "Wyk³ad";

				break;
				//æwiczenia
			case 1:
				 dir_name = "Æwiczenia";
				 sub_dir = "Æw";


				break;
				//laby
			case 2:
				dir_name = "Laboratoria";
				sub_dir = "Lab";

				break;
			default:
				break;
			}
			if (subjects_numbers[i][j] != 0)
			{
				actual_comand = mkdir + " " + '"' + path + "/" + semester + "/" + subjects[i] + "/"+dir_name+'"';
				system(actual_comand.c_str());
				for (int k = 0;k < subjects_numbers[i][j];k++)
				{
					actual_comand = mkdir + " " + '"' + path + "/" + semester + "/" + subjects[i] + "/" + dir_name + "/"+sub_dir+to_string(k)+'"';
					system(actual_comand.c_str());
				}
			}
		}
	}

}

DirectoryMaker::DirectoryMaker(string path, QString subjects[256], int subjects_numbers[256][3],string semester,int subNuber)
{
	this->path = path;

	this->semester = some_func(semester,'/','-');
	this->sub_number = subNuber;

	for (int i = 0;i < subNuber;i++)
	{
		this->subjects[i] = subjects[i].toStdString();
		this->subjects_numbers[i][0] = subjects_numbers[i][0];
		this->subjects_numbers[i][1] = subjects_numbers[i][1];
		this->subjects_numbers[i][2] = subjects_numbers[i][2];
	}

}
