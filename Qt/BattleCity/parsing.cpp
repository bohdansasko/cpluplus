#include "parsing.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

CWorkWithFiles::CWorkWithFiles() {}

bool CWorkWithFiles::ParsTextFile(const QString &nameFile, int n_Map[CNT_ROWS_MAP][CNT_COLS_MAP])
{
    QFile   fileFromRead(nameFile);
    if (!fileFromRead.exists()) {
        qDebug() << "File not create!";
        return false;
    }

    int i = 0;
    int j = 0;
    int tempRows = CNT_ROWS_MAP - 1;
    int tempCols = CNT_COLS_MAP - 1;

    if (!fileFromRead.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't open file!";
        return false;
    }

    QTextStream  n_StreamReadFile(&fileFromRead);

    while (!n_StreamReadFile.atEnd()) {
        n_StreamReadFile >> n_Map[i][j];

        if ((i == (tempRows) && (j == (tempCols)))) {
            break;
        }
        else if (j == tempCols) {
            ++i;
            j = 0;
        }
        else {
            ++j;
        }
    }

    fileFromRead.flush();
    fileFromRead.close();

    return true;
}

void CWorkWithFiles::readConfig(const QString &nameFile,
                         QString &nameOfPl1, QString &nameOfPl2,
                         bool &sound)
{
    QFile   fileOfConfig(nameFile);
    if (!fileOfConfig.exists()) {
        qDebug() << "File of configuration doesn't exists!";
        return;
    }

    fileOfConfig.flush();
    fileOfConfig.close();
}

void CWorkWithFiles::saveOptionsToConfig(const QString &nameOfFile) {
    QFile f(nameOfFile);

    if (!f.exists()) {
        qDebug() << "File doesnt exists.";
        return;
    }
}
