#ifndef PARSING_H
#define PARSING_H

#include <QObject>

#include "constants.h"

class CWorkWithFiles {
public:
    CWorkWithFiles();

    bool ParsTextFile(const QString &nameFile, int n_Map[CNT_ROWS_MAP][CNT_COLS_MAP]);
    void readConfig(const QString &nameFile, QString &nameOfPl1, QString &nameOfPl2, bool &sound);
    void saveOptionsToConfig(const QString &nameOfFile);
};

#endif // PARSING_H
