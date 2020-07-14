#include "mainwindow.h"
#include <QApplication>

// Навасардян Александр МО2

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
