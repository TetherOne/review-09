/*Дан текстовый файл, в первой строке которого хранится число N, а во второй
строке N целых чисел. Необходимо создать упорядоченный по убыванию список, в который
поместить все эти элементы, при этом очередной элемент вставлять в список так, чтобы не
нарушалась его упорядоченность.

Для каждой динамической структуры должен быть предусмотрен стандартный набор методов - 
добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.

*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    //FIX_ME: отсутствовал деструктор — утечка памяти при любом выходе из программы
    //отсутствовал ~LinkedList()
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertSorted(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr || head->data < value) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->data > value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
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

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла!" << endl;
            return;
        }

        int n;
        file >> n;

        int value;
        for (int i = 0; i < n; ++i) {
            file >> value;
            insertSorted(value);
        }

        file.close();
    }

    //FIX_ME: дублирующая friend-функция readFromFile просто вызывала одноимённый
    //метод класса — избыточная обёртка удалена
    //friend void readFromFile(LinkedList& list, const string& filename);
};

//FIX_ME: удалена — дублировала метод LinkedList::readFromFile без какой-либо логики
//void readFromFile(LinkedList& list, const string& filename) {
//    list.readFromFile(filename);
//}

int main() {
    LinkedList list;
    string filename;

    cout << "Введите имя файла: ";
    cin >> filename;

    list.readFromFile(filename);

    cout << "Упорядоченный список: ";
    list.print();

    return 0;
}
