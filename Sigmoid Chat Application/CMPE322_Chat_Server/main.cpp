#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    QApplication::setQuitOnLastWindowClosed(false);
    return a.exec();
}
