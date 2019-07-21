#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //creates instance of QApplication "a" with constructor.
    MainWindow w; //create a main window instance
    w.show(); //this shows windows

    return a.exec(); // creates the main execution loop and waits until execution is called.
}
