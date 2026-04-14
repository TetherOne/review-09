/*
Дан циклический двусвязный линейный список и указатель первый
элемент этого списка. Необходимо удалить в списке все элементы, у которых правый и
левый сосед совпадают. Если таких элементов нет, то оставить список без изменений.
Первый и последний элементы считать соседями. В результате вернуть ссылку на
последний элемент полученного списка.
Все динамические структуры данных реализовывать через классы. Не использовать STL.  
Для каждой динамической структуры должен быть предусмотрен стандартный
набор методов - добавления/удаления/вывода элементов. Во всех задачах обязательно наличие 
дружественного интерфейса. Ввод данных с клавиатуры.
*/

class DoubleList {
    public:
        struct Node {
            int data;
            Node* next;
            Node* prev;
            Node(int val) {
                data = val;
                next = nullptr;
                prev = nullptr;
            }
            
        };
    
        Node* head;
    
        DoubleList() {
            head = nullptr;
        }        
    
        ~DoubleList() {
            if (!head)
                return;
            Node* curr = head;
            while (true) {
                Node* tmp = curr;
                curr = curr->next;
                delete tmp;
                if (curr == head)
                    break;
            }
        }
    
        void push_back(int value) {
            Node* newNode = new Node(value);
            if (!head) {
                head = newNode;
                newNode->next = newNode;
                newNode->prev = newNode;
            }
            else {
                Node* tail = head->prev;
                tail->next = newNode;
                newNode->prev = tail;
                newNode->next = head;
                head->prev = newNode;
            }
        }
    
        void printList() {
            Node* curr = head;
            while (true) {
                cout << curr->data << " ";
                curr = curr->next;
                if (curr == head)
                    break;
            }
            cout << endl;
        }
    
        Node* deleteNode(Node* node) {
            if (!node)
                return nullptr;
            if (node->next == node && node->prev == node) {
                if (node == head)
                    head = nullptr;
                delete node;
                return nullptr;
            }
            Node* nextNode = node->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if (node == head)
                head = nextNode;
            delete node;
            return nextNode;
        }
    
    Node* removeSides() {
        if (!head) return nullptr;
        bool anyDeletion = false;
        bool deletedSomething = false;
        while (true) {
            anyDeletion = false;
            if (!head || head->next == head)
                break;
            Node* start = head;
            Node* curr = head;
            bool completedCycle = false;
            while (!completedCycle) {
                int leftData = curr->prev->data;
                int rightData = curr->next->data;
                if (leftData == rightData) {
                    anyDeletion = true;
                    deletedSomething = true;
                    Node* nextNode = curr->next;
                    if (curr == head)
                        head = nextNode;
                    curr = deleteNode(curr);
                    if (!curr)
                        return nullptr;
                    start = head;
                    continue;
                }
                else {
                    curr = curr->next;
                }
                if (curr == start)
                    completedCycle = true;
            }
            if (!anyDeletion)
                break;
        }
        if (!head)
            return nullptr;
        Node* tail = head->prev;
        return tail;
    }
};    
    

int main(){
    DoubleList list;
    int n, value;
    cout << "сколько надо числе: ";
    cin >> n;
    cout << "вводи числа" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.push_back(value);
    }
    cout << "нормальный список: ";
    list.printList();
    DoubleList::Node* tail = list.removeSides();
    cout << "обработанный список: ";
    list.printList();
    cout << "последний элемент: " << tail->data << endl;
}