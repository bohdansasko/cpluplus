#include <QtDebug>
#include <QException>
#include "algorithmli.h"

algorithmLI::algorithmLI(int x_begin, int y_begin, int x_end, int y_end)
{
    p_ReadFromFile = new CWorkWithFiles();
    p_ReadFromFile->ParsTextFile(":/log_parsing.txt", n_map);   // Завантаження карти з файлу

    if (SearchWay(x_begin, y_begin, x_end, y_end)) {
//        qDebug() << "Path find";

        int _i = 0; // счётчик для елементов конечного пути

        while (vectorFoundWay[_i].index >= 10) // пока не достигли начала
        {
            int tempStep;

            tempStep = vectorFoundWay[_i].index;
            --tempStep;

            try
            {
                for (int i(0); i < vectorPassableElement.size(); i++)
                {
                    if (vectorPassableElement[i].index == tempStep)
                    {
                        if (
                            (( vectorPassableElement[i].x == vectorFoundWay[_i].x-1 ) && ( vectorPassableElement[i].y == vectorFoundWay[_i].y   )) ||
                            (( vectorPassableElement[i].x == vectorFoundWay[_i].x   ) && ( vectorPassableElement[i].y == vectorFoundWay[_i].y+1 )) ||
                            (( vectorPassableElement[i].x == vectorFoundWay[_i].x+1 ) && ( vectorPassableElement[i].y == vectorFoundWay[_i].y   )) ||
                            (( vectorPassableElement[i].x == vectorFoundWay[_i].x   ) && ( vectorPassableElement[i].y == vectorFoundWay[_i].y-1 ))
                           )
                        {
                            vectorFoundWay.push_back(vectorPassableElement[i]);
                            break;
                        }
                    }
                }
            } catch (QException *ex)
            {
//                qDebug() << "out of index vector";
                return;
            }
           ++_i;
        }

        for (int _i(0); _i < vectorFoundWay.size(); _i++)
        {
            n_map[vectorFoundWay[_i].x][vectorFoundWay[_i].y] = -1;
        }
    }
    else
    {
        //vectorFoundWay.clear();
//        qDebug() << "Path not found(((";
    }
}

bool algorithmLI::SearchWay(int x, int y, int end_x, int end_y)
{
    int numberAllPassableElement = 0; // счётчик по всем елементам вектора
    int distance = 10;
    int tempNumberPassable = 0;

    bool added = false;
    bool size  = true;

    point begin;
    begin.x     = x;
    begin.y     = y;
    begin.index = 9;

    vectorPassableElement.push_back(begin); // добавляем начало в список

    n_map[x][y] = 9;

    while (added || size)
    {
        // получаем текущие координаты
        x = vectorPassableElement[numberAllPassableElement].x;
        y = vectorPassableElement[numberAllPassableElement].y;

        added = false;
        size = false;

        if (x == end_x && y == end_y) // если текущие координаты есть конечными выйти из функции
        {
            vectorFoundWay.push_back(vectorPassableElement[numberAllPassableElement]);
            return true;
        }

        ++numberAllPassableElement;

        if (x != 0) // если не на границе матрицы
        {
            if (
                (n_map[x-1][y] == 0) ||
                (n_map[x-1][y] == 2) ||
                (n_map[x-1][y] == 3) ||
                (n_map[x-1][y] == 4)
               )  // если проходимый елемент
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index) // если предыдущий индекс такой же как и этот
                {
                    ++distance;                                                  // увеличиваем индекс
                }

                n_map[x-1][y] = distance;               // установливаем индекс в матрицу
                begin.x = x-1;                          // координаты
                begin.y = y;                            // индекса
                begin.index = distance;                 // индекс
                vectorPassableElement.push_back(begin); // добавляем текущую точку в вектор проходимых
                added = true;                           // есть возможность подальшего продвижения
            }
        }
        if (y < CNT_COLS_MAP-1)
        {
            if (
                (n_map[x][y+1] == 0) ||
                (n_map[x][y+1] == 2) ||
                (n_map[x][y+1] == 3) ||
                (n_map[x][y+1] == 4)
               )
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index)
                {
                    ++distance;
                }

                n_map[x][y+1] = distance;
                begin.x = x;
                begin.y = y+1;
                begin.index = distance;
                vectorPassableElement.push_back(begin);
                added = true;
            }
        }

        if (x < CNT_COLS_MAP - 1)
        {
            if (
                (n_map[x+1][y] == 0) ||
                (n_map[x+1][y] == 2) ||
                (n_map[x+1][y] == 3) ||
                (n_map[x+1][y] == 4)
               )
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index)
                {
                    ++distance;
                }

                n_map[x+1][y] = distance;
                begin.x = x+1;
                begin.y = y;
                begin.index = distance;
                vectorPassableElement.push_back(begin);
                added = true;
            }
        }
        if (y > 0)
        {
            if (
                (n_map[x][y-1] == 0) ||
                (n_map[x][y-1] == 2) ||
                (n_map[x][y-1] == 3) ||
                (n_map[x][y-1] == 4)
               )
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index)
                {
                    ++distance;
                }

                n_map[x][y-1] = distance;
                begin.x = x;
                begin.y = y-1;
                begin.index = distance;
                vectorPassableElement.push_back(begin);
                added = true;
            }
        }

        if (distance == 10) // если первый проход
        {
            ++distance;
        }

        if (numberAllPassableElement >= vectorPassableElement.size()) // если елементов для проверки нет
        {
            return false;                                             // выходим из  функции
        }
        else
        {
            size = true;
        }
    }
    return false; // если пути не нашли
}
