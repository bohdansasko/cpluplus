#include <iostream>
#include <vector>

struct ab {
    int a;
    int b;
};

// Розширений алгоритм Евкліда. Без пошуку НСД, тільки x,y
void exEvklid(int a, int b, int &x, int &y);

int main(void) {
    int a = 3, b = 35;
    int x1 = 0, y1 = 0;

    exEvklid(a, b, x1, y1);

    int r = a * x1 + b * y1;
    std::cout << "a = " << a << "; b = " << b << '\n';
    if (r == 1) {
        std::cout << x1 << " " << y1 << '\n'
                  << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}

void exEvklid(int a, int b, int &x, int &y) {
    std::vector<ab> v;
    while(true) {
        int a1 = a;
        if (a == 0) {
            x = 0;
            y = 1;
            break;
        }
        v.push_back(ab{a, b});
        a = b % a;
        b = a1;
    }
    for (int i = v.size()-1; i >= 0; --i) {
        int x1 = x;
        x = y - (v[i].b / v[i].a) * x1;
        y = x1;
    }
}
