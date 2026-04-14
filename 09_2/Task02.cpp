/* Дан набор из 10 чисел. Создать две очереди: первая должна содержать числа из
исходного набора с нечетными номерами (1, 3, …, 9), а вторая — с четными (2, 4, …, 10);
порядок чисел в каждой очереди должен совпадать с порядком чисел в исходном наборе.
Вывести указатели на начало и конец первой, а затем второй очереди.


Для каждой динамической структуры должен быть предусмотрен стандартный набор методов - 
добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.



В заданиях данной подгруппы структура «очередь» (queue) моделируется цепочкой связанных
узлов-записей типа TNode. Поле Next последнего элемента цепочки равно nullptr. Началом
очереди («головой», head) считается первый элемент цепочки, концом («хвостом», tail) — ее
последний элемент. Для возможности быстрого добавления в конец очереди нового элемента
удобно хранить, помимо указателя на начало очереди, также и указатель на ее конец. В случае
пустой очереди указатели на ее начало и конец полагаются равными nullptr. Как и для стека,
значением элемента очереди считается значение его поля Data.


*/



#include <iostream>
#include <windows.h>

using namespace std;

// Структура для узла очереди
struct Uzel {
    int Znachenie;
    Uzel* Sleduyushiy;
};

// Класс для работы с очередью
class Ochered {
private:
    Uzel* Nachalo; // Указатель на начало
    Uzel* Konec;   // Указатель на конец

public:
    // Инициализация очереди
    void Inicializaciya() {
        Nachalo = nullptr;
        Konec = nullptr;
    }

    // Добавить элемент в конец
    void DobavitElement(int Chislo) {
        Uzel* Noviy = new Uzel;
        Noviy->Znachenie = Chislo;
        Noviy->Sleduyushiy = nullptr;

        if (Nachalo == nullptr) {
            Nachalo = Noviy;
            Konec = Noviy;
        }
        else {
            Konec->Sleduyushiy = Noviy;
            Konec = Noviy;
        }
    }

    // Удалить первый элемент
    void UdalitElement() {
        if (Nachalo == nullptr) {
            cout << "Очередь пуста!" << endl;
            return;
        }

        Uzel* Vremenny = Nachalo;
        Nachalo = Nachalo->Sleduyushiy;
        delete Vremenny;

        if (Nachalo == nullptr) Konec = nullptr;
    }

    // Вывести все элементы
    void VivodElementov() {
        Uzel* Tekushiy = Nachalo;
        while (Tekushiy != nullptr) {
            cout << Tekushiy->Znachenie << " ";
            Tekushiy = Tekushiy->Sleduyushiy;
        }
        cout << endl;
    }

    // Вывести указатели начала и конца (ДОБАВЛЕН ВЫВОД ЗНАЧЕНИЙ)
    void VivodUkazatelei() {
        cout << "Адрес начала: " << Nachalo;
        if (Nachalo != nullptr) cout << " (значение: " << Nachalo->Znachenie << ")";
        cout << endl;

        cout << "Адрес конца:  " << Konec;
        if (Konec != nullptr) cout << " (значение: " << Konec->Znachenie << ")";
        cout << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Ochered Ochered1, Ochered2;
    Ochered1.Inicializaciya();
    Ochered2.Inicializaciya();

    cout << "Введите 10 чисел:\n";
    for (int i = 1; i <= 10; i++) {
        int Chislo;
        cout << "Число " << i << ": ";
        cin >> Chislo;

        // Примитивная проверка на ввод
        if (cin.fail()) {
            cout << "Ошибка! Введите число!\n";
            return 0;
        }

        // Распределение по очередям
        if (i % 2 != 0) Ochered1.DobavitElement(Chislo);
        else Ochered2.DobavitElement(Chislo);
    }

    // Вывод результатов
    cout << "\nНечетная очередь:\n";
    Ochered1.VivodElementov();
    Ochered1.VivodUkazatelei();

    cout << "\nЧетная очередь:\n";
    Ochered2.VivodElementov();
    Ochered2.VivodUkazatelei();

    return 0;
}