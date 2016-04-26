#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int _sgetch() {
    struct termios oldt,                    // Хранение текущих настроек терминала
                   newt;                    // (new terminal)Установка новых настроек, в которых не будет
                                            // вывода символа и будет выключенный канонический режим
                                            // (ввод и подтверждение нажатием [Enter])
    int ch = 0;                             // Код символу
    tcgetattr( STDIN_FILENO, &oldt );       // Получение текущих настроек терминала
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );     // Выключение канонического режима и вывода символа
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );    // Применение новых настроек к терминалу
    ch = getchar();                               // Считывание символа с потока новыми настройками которые хранятся в "newt"
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );    // Возвращение к начальним настройкам терминала, которые хранятся в "oldt"

    return ch;
}

int main() {
    int ch = -1;
    std::cout << "You must enter number:\n";
    while (ch) {
        ch = _sgetch();
        if (ch > '0' && ch < '9')
            std::cout << "You enter number: " << ch-48 << ";\n";
        else
            std::cout << "You enter other key: " << (char)ch << ";\n";
    }
    return 0;
}
