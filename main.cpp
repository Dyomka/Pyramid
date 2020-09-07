#include "pyram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pyram w;
    w.show();
    return a.exec();
}
