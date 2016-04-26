#ifndef ALGORITHMLI_H
#define ALGORITHMLI_H

#include <QVector>
#include "parsing.h"
#include "constants.h"

struct point
{
    int x;
    int y;
    int index;
};

class algorithmLI
{
public:
    algorithmLI(int x_begin, int y_begin, int x_end, int y_end);

public:
    int n_map[CNT_ROWS_MAP][CNT_COLS_MAP];
    QVector<point> vectorPassableElement; // проходимые елементы
    QVector<point> vectorFoundWay;        // найденный путь

    CWorkWithFiles *p_ReadFromFile;              // обьект для чтения файла с картой

    bool SearchWay(int x, int y, int end_x, int end_y); // находить кратчайшый путь
};

#endif // ALGORITHMLI_H
