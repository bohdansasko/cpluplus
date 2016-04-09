#include <iostream>
#include <vector>
#include <fstream>

#define unsigned int uint                           // Сокращение записи

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

const int L  = 1000;                                // Размер массива(LENGTH)
const int LA = 26;                                  // Количество символов в алфавите(Length alphabet)

string lines[L];                                    // Все строки файла

void readFromFile(const string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file!\n";
        exit(0);
    }

    string line = "";
    int length = 0;
    int i = 0;
    while(getline(file, line)) {
        length += line.length();
        lines[i] = line;
        ++i;
    }
    file.close();

//    cout << "Count chars = " << length << ";\n";
}

void radixSort() {
    int numb[LA] = {0};                             // Количество вхождений символов
    vector< vector<string> > vspA;
    vspA.resize(LA);                                // Установка размера

    for (int i = 2; i > -1; --i) {
        for (int j = 0; j < L; ++j) {
            int t = int(lines[j][i]) - 97;
            vspA[t].push_back(lines[j]);
        }
        int k = 0;
        for (int i = 0; i < LA; ++i) {
            for (uint t = 0; t < vspA[i].size(); ++t, ++k) {
                lines[k] = vspA[i][t];
            }
            vspA[i].clear();
        }
    }

    // Count sort
    for (int j = 0; j < L; ++j) {
        for (uint r = 0; r < lines[j].size(); ++r) {
            int q = int(lines[j][r]) - 97;
            ++numb[q];                                          // Подсчёт символов
        }
        cout << lines[j] << endl;
    }

    for (int i = 0; i < LA; ++i) {
        cout << char(i + 97) << "=(" << numb[i] << ")" << endl; // Вывод количества найденных символов(Например: a(1), b(0))
    }
    cout << endl;
}

int main() {
    readFromFile("/QtPro/cppdelete/data.txt");      // Чтение строк с файла
    radixSort();                                    // Запуск сортировки

    return 0;
}
