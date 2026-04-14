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



#include <ctime>
#include <list>
#include <fstream>
#include <iostream>
using namespace std;
void Input(list<int>& L, int n)//Заполнение списков
{
    int m, x;
    cout << "Выберете способ заполнения контейнера: " << endl;
    cout << "1)Ввод с клавиатуры." << endl;
    cout << "2)Ввод с помощью рандомайзера." << endl;
    cout << "3)Ввод данных из текстового файла." << endl;
    cin >> m;
    switch (m)
    {
    case 1:
    {
        for (int i = 0; i < n;i++)
        {
            cout << "Введите " << i + 1 << " элемент: ";
            cin >> x;
            L.insert(L.end(),x);
        }
        break;
    }
    case 2:
    {
        srand(time(0));
        for (int i = 0;i < n;i++)
            L.insert(L.end(), rand() % 101 - 50);
        break;
    }
    case 3:
    {
        ifstream file("a.txt", ios::in); // a.txt { 27 -8 -11 -25 33 47 -30 -41 -8 3 -13 -29 -38 -18}
        if (!file)
        {
            cout << "Ошибка. Файл не был открыт.";
            return;
        }
        for (int i = 0; i < n;i++)
        {
            file >> x;
            L.insert(L.end(), x);
        }
        file.close();
        break;
    }
    default:
    {
        cout << "Ошибка ввода." << endl;
        break;
    }
    }
}
void Print(const list<int> L)//Вывод содержимого списков
{
    for (auto it = L.begin(); it != L.end(); it++)
        cout << *it << " ";
    cout << endl;
}
void Splice(list <int> &L1, list <int> &L2)//Помещает средний элемент списка L1 в конец списка L2
{
    list <int> ::iterator it;
    it = L1.begin();
    auto size = L1.size();
    for (int i = 0; i < size / 2;i++)
        ++it;
    L2.splice(L2.end(), L1, it);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n1, n2;
    list <int> L1;
    list <int> L2;
    cout << "Введите размерность списка n1 (n1 - нечётное): ";
    cin >> n1;
    Input(L1, n1);
    cout << "Введите размерность списка n2 (n2 >= 0): ";
    cin >> n2;
    if (n1 < 0 || n2 < 0 || n1 % 2 != 1)
    {
        cout << "Ошибка. Недопустимый размер списка.";
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