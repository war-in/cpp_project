#include "Projektc.h"
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <QFileDialog> 
#include "windows.h"
#include "DirectoryMaker.h"


Projektc::Projektc(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

   
}

void Projektc::StartButtonFunction()
{
    StackedOperation(1);
    ui.stackedWidget->setCurrentWidget(ui.MainPage);
}

void Projektc::connect_all()
{
    connect(ui.StartButton, &QPushButton::clicked, this, &Projektc::StartButtonFunction);
    connect(ui.LinkButton, &QPushButton::clicked, this, &Projektc::LinkButtonFunction);
    connect(ui.DirButton, &QPushButton::clicked, this, &Projektc::DirButtonFunction);
    connect(ui.SubiektButton, &QPushButton::clicked, this, &Projektc::SubjectButtonFunction);
    connect(ui.AcceptLinkButton, &QPushButton::clicked, this, &Projektc::acceptLink);
    connect(ui.AddSubjectButton, &QPushButton::clicked, this, &Projektc::add_subiect);
    connect(ui.DelSubjectButton, &QPushButton::clicked, this, &Projektc::del_subiect);
    connect(ui.ChoseDirPatchButton, &QPushButton::clicked, this, &Projektc::chose_dir);
    connect(ui.EditSubiectButton, &QPushButton::clicked, this, &Projektc::edit_subiect);
    connect(ui.SaveChangesToSub, &QPushButton::clicked, this, &Projektc::save_changes);
    connect(ui.AddPatchFacultiesButton, &QPushButton::clicked, this, &Projektc::add_facultiesPatch);
    connect(ui.AddFacultiesButton, &QPushButton::clicked, this, &Projektc::add_Facultiest);
    connect(ui.CreateButton, &QPushButton::clicked, this, &Projektc::dir_create);
    connect(ui.HomeButton, &QPushButton::clicked, this, &Projektc::go_to_home_page);





}

void Projektc::LinkButtonFunction()
{
    StackedOperation(1);
}

void Projektc::DirButtonFunction()
{
    StackedOperation(3);

}

void Projektc::SubjectButtonFunction()
{
    StackedOperation(2);

}

void Projektc::StackedOperation(int arg)
{
    color_state(arg);
    switch (arg)
    {        
    case 1:
        ui.stackedWidget_2->setCurrentWidget(ui.LinkPage);
        break;
    case 2:
        ui.stackedWidget_2->setCurrentWidget(ui.SubjectPage);
        load_subjects();
        break;
    case 3:
        ui.stackedWidget_2->setCurrentWidget(ui.SavePage);
        print_selected_subs();
        break;
    default:

        break;
    }
}
char** split(char* line)
{
    int len = strlen(line);
    char** result = (char**) calloc(4, sizeof(char*));
    for (int i = 0;i < 4;i++) result[i] = (char*)calloc(256, sizeof(char));
    int prev = 0;
    int actual = 0;
    for (int i = 0;i < len;i++)
    {
        if (line[i] == ';' || line[i] == '\n')
        {
            for (int j = 0;j < i - prev;j++)
            {
                result[actual][j] = line[j + prev];
            }
            prev = i + 1;
            actual++;
        }
    }
    return result;
}
void Projektc::acceptLink()
{
    link = ui.LinkPlace->toPlainText().toStdString();
    semestr = ui.textEdit->toPlainText().toStdString();
    std::string progName = "prog.exe ";
    std::string arg = progName+ '"' + link + '"' + " " + '"' + semestr + '"';
    system(arg.c_str());
    Sleep(5000);
    FILE* file = fopen("example.txt","r");
    char* line = (char*)malloc(256 * sizeof(char));
    //for (int i = 0;i < 256;i++) subjects[i] = (char*)malloc(256 * sizeof(char));
    char** parsedLine;
    subiectCount = 0;
    int type=0;
    while (fgets(line, 256, file))
    {
        if (strcmp(line, "Sciezkowe\n")==0) type = 1;
        else if (strcmp(line, "Obieraki\n")==0) type = 2;
        else if (strcmp(line, "Przedmioty\n")==0) type = 3;
        else
        {
            parsedLine = split(line);
            if (type == 3)
            {
                subjects[subiectCount] = parsedLine[0];
                allSubiectsNumbers[subiectCount][0] = atoi(parsedLine[1]);
                allSubiectsNumbers[subiectCount][1] = atoi(parsedLine[2]);
                allSubiectsNumbers[subiectCount][2] = atoi(parsedLine[3]);
                subiectCount++;
            }
            if (type == 2)
            {
                faculties[facultiesCount] = parsedLine[0];
                allFacultiestsNumbers[facultiesCount][0] = atoi(parsedLine[1]);
                allFacultiestsNumbers[facultiesCount][1] = atoi(parsedLine[2]);
                allFacultiestsNumbers[facultiesCount][2] = atoi(parsedLine[3]);
                facultiesCount++;
            }
            if (type == 1)
            {
                faculties_patch[FacultiestsPatchCount] = parsedLine[0];
                allFacultiestsPatchNumbers[FacultiestsPatchCount][0] = atoi(parsedLine[1]);
                allFacultiestsPatchNumbers[FacultiestsPatchCount][1] = atoi(parsedLine[2]);
                allFacultiestsPatchNumbers[FacultiestsPatchCount][2] = atoi(parsedLine[3]);
                FacultiestsPatchCount++;
            }
        }
    }
    fclose(file);
    StackedOperation(2);
}

void Projektc::load_subjects()
{
        ui.AllSubjectsTable->clear();
        ui.AllSubjectsTable->setRowCount(subiectCount);
        ui.AllSubjectsTable->setColumnCount(4);
        ui.AllSubjectsTable -> setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
        ui.AllSubjectsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Wyk"));
        ui.AllSubjectsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Cw"));
        ui.AllSubjectsTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Lab"));

        int coulumns = 4;
        for (auto r = 0; r < subiectCount; r++)
            for (auto c = 0; c < coulumns; c++)
                if (c == 0)
                    ui.AllSubjectsTable->setItem(r, c, new QTableWidgetItem(QString::fromStdString(subjects[r])));
                else
                    ui.AllSubjectsTable->setItem(r, c, new QTableWidgetItem(QString::number(allSubiectsNumbers[r][c-1])));
        ui.AllSubjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui.facultiesTable->clear();
        ui.facultiesTable->setRowCount(facultiesCount);
        ui.facultiesTable->setColumnCount(coulumns);
        ui.facultiesTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
        ui.facultiesTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Wyk"));
        ui.facultiesTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Cw"));
        ui.facultiesTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Lab"));
        for (auto r = 0; r < facultiesCount; r++)
            for (auto c = 0; c < coulumns; c++)
                if (c == 0)
                    ui.facultiesTable->setItem(r, c, new QTableWidgetItem(QString::fromStdString(faculties[r])));
                else
                    ui.facultiesTable->setItem(r, c, new QTableWidgetItem(QString::number(allFacultiestsNumbers[r][c-1])));
        ui.facultiesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui.facultiesPatchTable->clear();
        ui.facultiesPatchTable->setRowCount(FacultiestsPatchCount);
        ui.facultiesPatchTable->setColumnCount(coulumns);
        ui.facultiesPatchTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
        ui.facultiesPatchTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Wyk"));
        ui.facultiesPatchTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Cw"));
        ui.facultiesPatchTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Lab"));
        for (auto r = 0; r < FacultiestsPatchCount; r++)
            for (auto c = 0; c < coulumns; c++)
                if (c == 0)
                    ui.facultiesPatchTable->setItem(r, c, new QTableWidgetItem(QString::fromStdString(faculties_patch[r])));
                else
                    ui.facultiesPatchTable->setItem(r, c, new QTableWidgetItem(QString::number(allFacultiestsPatchNumbers[r][c-1])));
        ui.facultiesPatchTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui.facultiesPatchTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
        ui.facultiesPatchTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

void Projektc::add_Facultiest()
{
    QModelIndex index = ui.facultiesTable->selectionModel()->currentIndex();
    QString sub = index.sibling(index.row(), 0).data().toString();
    added_subjects[addedSubiectCount] = sub;
    addedSubiectNumbers[addedSubiectCount][0] = allFacultiestsNumbers[index.row()][0];
    addedSubiectNumbers[addedSubiectCount][1] = allFacultiestsNumbers[index.row()][1];
    addedSubiectNumbers[addedSubiectCount][2] = allFacultiestsNumbers[index.row()][2];
    addedSubiectCount++;
    ui.AddedSubjectsTable->clear();
    ui.AddedSubjectsTable->setRowCount(addedSubiectCount);
    ui.AddedSubjectsTable->setColumnCount(1);
    for (auto r = 0; r < addedSubiectCount; r++)
        for (auto c = 0; c < 1; c++)
            ui.AddedSubjectsTable->setItem(r, c, new QTableWidgetItem(added_subjects[r]));
    ui.AddedSubjectsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
    ui.AddedSubjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Projektc::add_facultiesPatch()
{
    QModelIndex index = ui.facultiesPatchTable->selectionModel()->currentIndex();
    QString sub = index.sibling(index.row(), 0).data().toString();
    added_subjects[addedSubiectCount] = sub;
    addedSubiectNumbers[addedSubiectCount][0] = allFacultiestsPatchNumbers[index.row()][0];
    addedSubiectNumbers[addedSubiectCount][1] = allFacultiestsPatchNumbers[index.row()][1];
    addedSubiectNumbers[addedSubiectCount][2] = allFacultiestsPatchNumbers[index.row()][2];

    addedSubiectCount++;
    ui.AddedSubjectsTable->clear();
    ui.AddedSubjectsTable->setRowCount(addedSubiectCount);
    ui.AddedSubjectsTable->setColumnCount(1);
    for (auto r = 0; r < addedSubiectCount; r++)
        for (auto c = 0; c < 1; c++)
            ui.AddedSubjectsTable->setItem(r, c, new QTableWidgetItem(added_subjects[r]));
    ui.AddedSubjectsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
    ui.AddedSubjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

void Projektc::add_subiect()
{
    QModelIndex index = ui.AllSubjectsTable->selectionModel()->currentIndex();
    QString sub = index.sibling(index.row(), 0).data().toString();
    added_subjects[addedSubiectCount] = sub;
    addedSubiectNumbers[addedSubiectCount][0] = allSubiectsNumbers[index.row()][0];
    addedSubiectNumbers[addedSubiectCount][1] = allSubiectsNumbers[index.row()][1];
    addedSubiectNumbers[addedSubiectCount][2] = allSubiectsNumbers[index.row()][2];

    addedSubiectCount++;
    ui.AddedSubjectsTable->clear();
    ui.AddedSubjectsTable->setRowCount(addedSubiectCount);
    ui.AddedSubjectsTable->setColumnCount(1);
    for (auto r = 0; r < addedSubiectCount; r++)
        for (auto c = 0; c < 1; c++)
            ui.AddedSubjectsTable->setItem(r, c, new QTableWidgetItem(added_subjects[r]));
    ui.AddedSubjectsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
    ui.AddedSubjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

void Projektc::del_subiect()
{
    QModelIndex index = ui.AddedSubjectsTable->selectionModel()->currentIndex();
    int to_del = index.row();
    for (int i = to_del;i < addedSubiectCount-1;i++)
    {
        added_subjects[i] = added_subjects[i + 1];
        addedSubiectNumbers[i][0] = addedSubiectNumbers[i+1][0];
        addedSubiectNumbers[i][1] = addedSubiectNumbers[i+1][1];
        addedSubiectNumbers[i][2] = addedSubiectNumbers[i+1][2];
    }
    addedSubiectCount--;
    ui.AddedSubjectsTable->clear();
    ui.AddedSubjectsTable->setRowCount(addedSubiectCount);
    ui.AddedSubjectsTable->setColumnCount(1);
    for (auto r = 0; r < subiectCount; r++)
        for (auto c = 0; c < 1; c++)
            ui.AddedSubjectsTable->setItem(r, c, new QTableWidgetItem(added_subjects[r]));
    ui.AddedSubjectsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Przedmiot"));
    ui.AddedSubjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
void Projektc::chose_dir()
{
    
    selectedDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "/home",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
}

void Projektc::color_state(int arg)
{
    switch (arg)
    {
    case 1:
        ui.LinkButton->setStyleSheet("border: 3px solid Lime;");
        ui.DirButton->setStyleSheet("border: 3px solid Black;");
        ui.SubiektButton->setStyleSheet("border: 3px solid Black;");
        break;
    case 3:
        ui.LinkButton->setStyleSheet("border: 3px solid Black;");
        ui.DirButton->setStyleSheet("border: 3px solid Lime;");
        ui.SubiektButton->setStyleSheet("border: 3px solid Black;");
        break;
    case 2:
        ui.LinkButton->setStyleSheet("border: 3px solid Black;");
        ui.DirButton->setStyleSheet("border: 3px solid Black;");
        ui.SubiektButton->setStyleSheet("border: 3px solid Lime;");
        break;
    default:
        ui.LinkButton->setStyleSheet("border: 3px solid Black;");
        ui.DirButton->setStyleSheet("border: 3px solid Black;");
        ui.SubiektButton->setStyleSheet("border: 3px solid Black;");
        break;
    }
}

void Projektc::print_selected_subs()
{
    ui.SelectedSubiectsTable->clear();
    ui.SelectedSubiectsTable->setRowCount(addedSubiectCount);
    ui.SelectedSubiectsTable->setColumnCount(1);
    for (auto r = 0; r < addedSubiectCount; r++)
        for (auto c = 0; c < 1; c++)
            ui.SelectedSubiectsTable->setItem(r, c, new QTableWidgetItem(added_subjects[r]));
}

void Projektc::edit_subiect()
{
    
    QModelIndex index = ui.SelectedSubiectsTable->selectionModel()->currentIndex();
    QString sub = index.sibling(index.row(), 0).data().toString();
    ui.LecturesNumber->setText(QString::number(addedSubiectNumbers[index.row()][0]));
    ui.LessonsNumber->setText(QString::number(addedSubiectNumbers[index.row()][1]));
    ui.LabsNumber->setText(QString::number(addedSubiectNumbers[index.row()][2]));
    ui.label_12->setText(sub);
    actualEditingSubiect = index.row();
}

void Projektc::save_changes()
{
    addedSubiectNumbers[actualEditingSubiect][0] = ui.LecturesNumber->toPlainText().toInt();
    addedSubiectNumbers[actualEditingSubiect][1] = ui.LessonsNumber->toPlainText().toInt();
    addedSubiectNumbers[actualEditingSubiect][2] = ui.LabsNumber->toPlainText().toInt();
}

void Projektc::go_to_home_page()
{
    ui.stackedWidget->setCurrentWidget(ui.page);
}

void Projektc::dir_create()
{
    
    DirectoryMaker newMaker = DirectoryMaker(selectedDir.toStdString(), added_subjects, addedSubiectNumbers, semestr, addedSubiectCount);
    ui.label_16->setText(selectedDir);
    newMaker.make_dirs();
}



