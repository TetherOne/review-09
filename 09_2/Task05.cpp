/* Элементами контейнеров являются целые числа. Для
заполнения контейнера использовать итератор и конструктор соответствующего контейнера,
для вывода элементов использовать итератор (для вывода элементов в обратном порядке
использовать обратные итераторы, возвращаемые функциями-членами rbegin и rend)
Обязательно наличие дружественного интерфейса. Ввод данных организовать 
разными способами (с клавиатуры, рандом, из файла)

Даны списки L1 и L2; список L1 имеет нечетное количество элементов.
Переместить средний элемент списка L1 в конец списка L2. Использовать один вызов
функции-члена splice.

*/

#include <cstdlib>
#include <ctime>
#include <list>
#include <fstream>
#include <iostream>
using namespace std;

void Input(list<int>& L, int n) {
    int m, x;
    cout << "Выберите способ заполнения контейнера: " << endl;
    cout << "1) Ввод с клавиатуры." << endl;
    cout << "2) Ввод с помощью рандомайзера." << endl;
    cout << "3) Ввод данных из текстового файла (a.txt)." << endl;
    cin >> m;
    switch (m) {
        case 1: {
            for (int i = 0; i < n; ++i) {
                cout << "Введите " << i + 1 << " элемент: ";
                cin >> x;
                L.insert(L.end(), x);
            }
            break;
        }
        case 2: {
            srand(static_cast<unsigned>(time(nullptr)));
            for (int i = 0; i < n; ++i) {
                L.insert(L.end(), rand() % 101 - 50);
            }
            break;
        }
        case 3: {
            ifstream file("a.txt", ios::in);
            if (!file) {
                cerr << "Ошибка: файл a.txt не был открыт." << endl;
                return;
            }
            for (int i = 0; i < n; ++i) {
                file >> x;
                L.insert(L.end(), x);
            }
            file.close();
            break;
        }
        default: {
            cout << "Ошибка ввода." << endl;
            break;
        }
    }
}

//FIX_ME: Print принимала list по значению — лишнее копирование всего контейнера;
//заменена на const-ссылку
//void Print(const list<int> L)
void Print(const list<int>& L) {
    for (auto it = L.begin(); it != L.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void Splice(list<int>& L1, list<int>& L2) {
    auto it = L1.begin();
    auto size = L1.size();
    for (size_t i = 0; i < size / 2; ++i) {
        ++it;
    }
    L2.splice(L2.end(), L1, it);
}

int main() {
    //FIX_ME: setlocale(LC_ALL, "Russian") — Windows-специфичная строка локали,
    //на macOS не работает; удалена (UTF-8 поддерживается терминалом по умолчанию)
    //setlocale(LC_ALL, "Russian");

    int n1, n2;
    list<int> L1;
    list<int> L2;

    cout << "Введите размерность списка n1 (нечётное): ";
    cin >> n1;

    //FIX_ME: валидация n1 выполнялась ПОСЛЕ заполнения L1 через Input() — при
    //неверном вводе данные уже были введены, а ошибка сообщалась постфактум;
    //проверка перенесена до вызовов Input()
    //Input(L1, n1);  // было здесь, до проверки
    if (n1 < 0 || n1 % 2 != 1) {
        cout << "Ошибка. Недопустимый размер списка n1 (должен быть нечётным положительным)." << endl;
        return 1;
    }

    Input(L1, n1);

    cout << "Введите размерность списка n2 (>= 0): ";
    cin >> n2;

    if (n2 < 0) {
        cout << "Ошибка. Недопустимый размер списка n2." << endl;
        return 1;
    }

    Input(L2, n2);

    cout << "Изначальное содержимое списков." << endl;
    cout << "L1: ";
    Print(L1);
    cout << "L2: ";
    Print(L2);

    Splice(L1, L2);

    cout << "Изменённое содержание списков." << endl;
    cout << "L1: ";
    Print(L1);
    cout << "L2: ";
    Print(L2);

    return 0;
}
