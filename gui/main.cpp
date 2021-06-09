#include "Projektc.h"
#include <QtWidgets/QApplication>
#include <Windows.h>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Projektc w;
    w.connect_all();
    w.go_to_home_page();
    w.show();
    return a.exec();
}
