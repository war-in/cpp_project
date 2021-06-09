#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Projektc.h"

class Projektc : public QMainWindow
{
    Q_OBJECT

public:
    Projektc(QWidget *parent = Q_NULLPTR);
    void StartButtonFunction();
    void connect_all();
    void LinkButtonFunction();
    void DirButtonFunction();
    void SubjectButtonFunction();
    void StackedOperation(int arg);
    void acceptLink();
    void load_subjects();
    void add_Facultiest();
    void add_subiect();
    void add_facultiesPatch();
    void del_subiect();
    void chose_dir();
    void color_state(int arg);
    void print_selected_subs();
    void edit_subiect();
    void save_changes();
    void go_to_home_page();

    void dir_create();

private:
    Ui::ProjektcClass ui;
    std::string subjects[256];
    int allSubiectsNumbers[256][3];

    std::string faculties[256];
    int allFacultiestsNumbers[256][3];

    std::string faculties_patch[256];
    int allFacultiestsPatchNumbers[256][3];

    QString added_subjects[256];
    int addedSubiectNumbers[256][3];


    int subiectCount=0;
    int addedSubiectCount = 0;
    int facultiesCount = 0;
    int FacultiestsPatchCount = 0;

    QString selectedDir;
    int actualEditingSubiect;
    

    std::string link;
    std::string semestr;
};
