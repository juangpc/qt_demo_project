#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//these two MainWindow classes are different because they are in
//a different namespace
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT //this object is mandatory and lets compiler that the class will benefit of all Qt framework functionality

public:
    explicit MainWindow(QWidget *parent = nullptr); //constructor
    ~MainWindow(); //destructor

private slots:
    void on_btnAstroid_clicked();

    void on_btnCycloid_clicked();

    void on_btnHuygens_clicked();

    void on_btnHypoCycloid_clicked();

private:
    Ui::MainWindow *ui; //pointer to MainWindow object used to access GUI elements.
};

#endif // MAINWINDOW_H
