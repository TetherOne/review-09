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

//FIX_ME: #include <windows.h> отсутствует на macOS/Linux, заголовок удалён
//#include <windows.h>
#include <iostream>
using namespace std;

//FIX_ME: имена членов в русской транслитерации (Uzel, Znachenie, Sleduyushiy) нарушают
//единый стиль проекта — переименованы в английские эквиваленты
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    Node* head;
    Node* tail;

public:
    //FIX_ME: отсутствовал конструктор — вместо него использовался отдельный метод
    //Inicializaciya(), что не соответствует идиомам C++; поля не инициализировались
    //автоматически при создании объекта
    //void Inicializaciya() { Nachalo = nullptr; Konec = nullptr; }
    Queue() : head(nullptr), tail(nullptr) {}

    //FIX_ME: отсутствовал деструктор — утечка памяти при любом выходе из программы
    //отсутствовал ~Queue()
    ~Queue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void dequeue() {
        if (head == nullptr) {
            cout << "Очередь пуста!" << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printPointers() const {
        cout << "Адрес начала: " << head;
        if (head != nullptr) {
            cout << " (значение: " << head->data << ")";
        }
        cout << endl;

        cout << "Адрес конца:  " << tail;
        if (tail != nullptr) {
            cout << " (значение: " << tail->data << ")";
        }
        cout << endl;
    }
};

int main() {
    //FIX_ME: setlocale(LC_ALL, "Russian") — Windows-специфичная строка локали,
    //на macOS не работает; удалена (UTF-8 поддерживается терминалом по умолчанию)
    //setlocale(LC_ALL, "Russian");

    Queue queue1, queue2;

    cout << "Введите 10 чисел:\n";
    for (int i = 1; i <= 10; i++) {
        int value;
        cout << "Число " << i << ": ";
        cin >> value;

        if (cin.fail()) {
            cout << "Ошибка! Введите целое число!\n";
            return 1;
        }

        if (i % 2 != 0) {
            queue1.enqueue(value);
        } else {
            queue2.enqueue(value);
        }
    }

    cout << "\nНечётная очередь:\n";
    queue1.print();
    queue1.printPointers();

    cout << "\nЧётная очередь:\n";
    queue2.print();
    queue2.printPointers();

    return 0;
}
