#include "barchart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    barChart w;
    w.show();

    return a.exec();
}
