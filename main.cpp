#include "mainwindow.h"
#include <QApplication>
#include <presenter.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    Presenter* present = new Presenter (w);
    Q_UNUSED(present);
    w->show();

    return a.exec();
}
