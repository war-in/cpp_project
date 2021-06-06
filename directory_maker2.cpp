#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>

#include <fstream>

#include "parser.h"

using namespace std;


int main(int argc, char* argv[])
{
	if (argc < 3)
		return -1;

	ofstream myfile;
	myfile.open("example.txt");

	Parser parser(argv[1]);

	parser.parse((string) argv[2]);

	myfile << "Sciezkowe" << endl;

	vector <string> pathSubjects = parser.getPathSubjects();
	vector <string> pathSubjectsInfo = parser.getPathSubjectsInfo();
	for (size_t i = 0; i < pathSubjects.size(); i++)
		myfile << pathSubjects[i] << pathSubjectsInfo[i] << endl;

	myfile << "Obieraki" << endl;

	vector <string> faculties = parser.getFaculties();
	vector <string> facultiesInfo = parser.getFacultiesInfo();
	for (size_t i = 0; i < faculties.size(); i++)
		myfile << faculties[i] << facultiesInfo[i] << endl;

	myfile << "Przedmioty" << endl;

	vector <string> subjects = parser.getSubjects();
	vector <string> subjectsInfo = parser.getSubjectsInfo();
	for (size_t i = 0; i < subjects.size(); i++)
		myfile << subjects[i] << subjectsInfo[i] << endl;

	myfile.close();

	return 0;
}
