#include "mainwindow.h"
#include <QApplication>
#include "define.h"

int main(int argc, char *argv[])
{
    //QT += sql;
    QApplication a(argc, argv);
    MainWindow w;
//    App w;
    //w.setWindowState(Qt::WindowMaximized);
    w.show();
    w.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    w.setFixedSize(w.size());
    return a.exec();
}
