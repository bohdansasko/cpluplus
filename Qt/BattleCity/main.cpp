#include "battlecityview.h"
#include "mainmenu.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    mainMenu menu;

    return a.exec();
}
