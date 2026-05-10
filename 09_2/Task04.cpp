/*Дан циклический двусвязный линейный список и указатель на первый
элемент этого списка. Необходимо удалить в списке все элементы, у которых правый и
левый сосед совпадают. Если таких элементов нет, то оставить список без изменений.
Первый и последний элементы считать соседями. В результате вернуть ссылку на
последний элемент полученного списка.
Все динамические структуры данных реализовывать через классы. Не использовать STL.
Для каждой динамической структуры должен быть предусмотрен стандартный
набор методов - добавления/удаления/вывода элементов. Во всех задачах обязательно наличие
дружественного интерфейса. Ввод данных с клавиатуры.
*/

//FIX_ME: отсутствовали #include <iostream> и using namespace std — код не компилировался
//(отсутствовал #include <iostream>)
#include <iostream>
using namespace std;

class DoubleList {
public:
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(int val) : data(val), next(nullptr), prev(nullptr) {}
    };

private:
    //FIX_ME: поле head было объявлено в секции public — прямой доступ к внутреннему
    //указателю нарушает инкапсуляцию; перенесено в private
    //Node* head;  (было в public)
    Node* head;

    Node* deleteNode(Node* node) {
        if (!node) {
            return nullptr;
        }
        if (node->next == node && node->prev == node) {
            if (node == head) {
                head = nullptr;
            }
            delete node;
            return nullptr;
        }
        Node* nextNode = node->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if (node == head) {
            head = nextNode;
        }
        delete node;
        return nextNode;
    }

public:
    DoubleList() : head(nullptr) {}

    //FIX_ME: деструктор сравнивал curr с уже удалённым указателем head —
    //неопределённое поведение; теперь цикл разрывается и список обходится линейно
    //~DoubleList() {
    //    Node* curr = head;
    //    while (true) { Node* tmp = curr; curr = curr->next; delete tmp;
    //        if (curr == head) break; }  // head — dangling pointer после первой итерации!
    //}
    ~DoubleList() {
        if (!head) {
            return;
        }
        Node* tail = head->prev;
        tail->next = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    //FIX_ME: printList() не проверяла пустой список — вызов вёл к разыменованию nullptr
    //void printList() { Node* curr = head; while (true) { cout << curr->data ... } }
    void printList() const {
        if (!head) {
            cout << "(пустой список)" << endl;
            return;
        }
        Node* curr = head;
        do {
            cout << curr->data << " ";
            curr = curr->next;
        } while (curr != head);
        cout << endl;
    }

    Node* removeSides() {
        if (!head) {
            return nullptr;
        }
        bool anyDeletion = false;
        //FIX_ME: переменная deletedSomething объявлялась, но нигде не использовалась
        //bool deletedSomething = false;
        while (true) {
            anyDeletion = false;
            if (!head || head->next == head) {
                break;
            }
            Node* start = head;
            Node* curr = head;
            bool completedCycle = false;
            while (!completedCycle) {
                int leftData = curr->prev->data;
                int rightData = curr->next->data;
                if (leftData == rightData) {
                    anyDeletion = true;
                    curr = deleteNode(curr);
                    if (!curr) {
                        return nullptr;
                    }
                    start = head;
                    continue;
                } else {
                    curr = curr->next;
                }
                if (curr == start) {
                    completedCycle = true;
                }
            }
            if (!anyDeletion) {
                break;
            }
        }
        if (!head) {
            return nullptr;
        }
        return head->prev;
    }
};

int main() {
    DoubleList list;
    int n, value;
    cout << "Введите количество чисел: ";
    cin >> n;
    cout << "Введите числа:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.push_back(value);
    }
    cout << "Исходный список: ";
    list.printList();

    DoubleList::Node* tail = list.removeSides();

    cout << "Обработанный список: ";
    list.printList();

    //FIX_ME: tail не проверялся на nullptr перед разыменованием — crash при пустом
    //результате; добавлена проверка
    //cout << "последний элемент: " << tail->data << endl;
    if (tail) {
        cout << "Последний элемент: " << tail->data << endl;
    } else {
        cout << "Список пуст после обработки." << endl;
    }

    return 0;
}
