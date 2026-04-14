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

    
    void insertSorted(int value) {
        Node* newNode = new Node(value); 
        if (head == nullptr || head->data < value) { 
            newNode->next = head;        
            head = newNode;
        }
        else {
            Node* current = head;       
            while (current->next != nullptr && current->next->data > value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    
    void print() {
        Node* current = head;           
        while (current != nullptr) {    
            cout << current->data << " ";
            current = current->next;    
        }
        cout << endl;        
    }

    
    void readFromFile(const std::string& filename) {
        ifstream file(filename);   // Открываем файл для чтения
        if (!file.is_open()) {          // Проверяем, удалось ли открыть файл
            cerr << "Ошибка открытия файла!" << endl;
            return;
        }

        int N;
        file >> N;                      // Читаем количество элементов

        int value;
        for (int i = 0; i < N; ++i) {   // Читаем элементы и добавляем их в список
            file >> value;
            insertSorted(value);         // Вставляем элемент с сохранением упорядоченности
        }

        file.close();                   // Закрываем файл
    }

    // Дружественная функция для чтения данных из файла и заполнения списка
    friend void readFromFile(LinkedList& list, const string& filename);
};

// Дружественная функция для чтения данных из файла и заполнения списка
void readFromFile(LinkedList& list, const string& filename) {
    list.readFromFile(filename);
}

int main() {
    LinkedList list;                     // Создаем список
    string filename;

    // Ввод имени файла
    cout << "Введите имя файла: ";
    cin >> filename;

    // Чтение данных из файла и заполнение списка
    readFromFile(list, filename);

    // Вывод элементов списка
    cout << "Упорядоченный список: ";
    list.print();

    return 0;                            
}