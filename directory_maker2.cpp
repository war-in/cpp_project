#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>

#include "parser.h"
#include "gui.h"

using namespace std;


int main()
{
	Parser parser("https://sylabusy.agh.edu.pl/pl/1/1/15/1/4/12/13");

	parser.parse("Semestr zimowy, 2020/2021");

	cout << "sciezkowe" << endl;

	vector <string> pathSubjects = parser.getPathSubjects();
	for (size_t i = 0; i < pathSubjects.size(); i++)
		cout << pathSubjects[i] << endl;

	cout << endl;
	cout << "Obieraki" << endl;

	vector <string> electiveSubjects = parser.getElectiveSubjects();
	for (size_t i = 0; i < electiveSubjects.size(); i++)
		cout << electiveSubjects[i] << endl;

	cout << endl;
	cout << "Przedmioty" << endl;

	vector <string> subjects = parser.getSubjects();
	for (size_t i = 0; i < subjects.size(); i++)
		cout << subjects[i] << endl;
}
