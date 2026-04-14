/*Дано число D и указатель P1 на вершину непустого стека. 
Добавить элемент со значением D в стек и вывести адрес P2 новой вершины стека.

Для каждой динамической структуры должен быть предусмотрен стандартный набор методов - 
добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.

В заданиях подгруппы структура «стек» (stack) моделируется цепочкой связанных
узлов-записей типа TNode. Поле Next последнего элемента цепочки равно nullptr. Вершиной
стека (top) считается первый элемент цепочки. Для доступа к стеку используется указатель на
его вершину (для пустого стека данный указатель полагается равным nullptr). Значением
элемента стека считается значение его поля Data*/

#include <iostream>
using namespace std;

class Node {
public:
    int data;       
    Node* next;     

    
    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* top; 

public:
    
    Stack() : top(nullptr) {}

    //  для добавления элемента в стек
    void push(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        newNode->next = top;             // Новый узел указывает на текущую вершину
        top = newNode;                   // Обновляем вершину стека
        cout << "Элемент " << value << " добавлен в стек." << endl;
    }

    // Метод для удаления элемента из стека
    void pop() {
        if (top == nullptr) {            
            cout << "Стек пуст! Невозможно удалить элемент." << endl;
            return;
        }
        Node* temp = top;                
        top = top->next;                 
        cout << "Элемент " << temp->data << " удален из стека." << endl;
        delete temp;                 
    }

    
    void print() {
        if (top == nullptr) {           
            cout << "Стек пуст!" << endl;
            return;
        }
        Node* current = top;            
        cout << "Элементы стека: ";
        while (current != nullptr) {     
            cout << current->data << " "; 
            current = current->next;    
        }
        cout << endl;                  
    }

    
    Node* getTop() {
        return top;
    }

    
    void clearStack() {
        while (top != nullptr) {       
            Node* temp = top;            
            top = top->next;             
            delete temp;                 // Удаляем узел
        }
        cout << "Стек очищен." << endl;
    }

    
    friend void addElementAndPrintAddress(Stack& stack, int D);
};


void addElementAndPrintAddress(Stack& stack, int D) {
    stack.push(D);
    cout << "Адрес новой вершины стека: " << stack.getTop() << endl;
}

int main() {
    Stack stack;
    int choice, value;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент в стек\n";
        cout << "2. Удалить элемент из стека\n";
        cout << "3. Вывести элементы стека\n";
        cout << "4. Очистить стек\n";
        cout << "5. Выйти\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите число для добавления в стек: ";
            cin >> value;
            addElementAndPrintAddress(stack, value);
            break;
        case 2:
            stack.pop();
            break;
        case 3:
            stack.print();
            break;
        case 4:
            stack.clearStack();
            break;
        case 5:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор! Пожалуйста, попробуйте снова." << endl;
        }
    }

    return 0;
}