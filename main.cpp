#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedWidth(600);
    w.setFixedHeight(400);
    w.show();


    return a.exec();
}
