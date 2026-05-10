/*
https://chatgpt.com/c/6a0093dc-1d9c-83eb-b597-691cc13aa39c
Программа читает арифметическое выражение из файла FN1.txt
    и строит по нему бинарное дерево выражения.

    Поддерживаются операции:
        +  -  *  /  %  ^
    а также числа, переменная x и скобки.

    Сначала выражение разбивается на токены
    (числа, операции, скобки).

    Затем инфиксная запись переводится в постфиксную
    с помощью стека и с учетом приоритетов операций.
    Операции одинакового приоритета вычисляются
    слева направо.

    По постфиксной записи строится дерево выражения:
        операторы становятся внутренними узлами,
        числа и x — листьями.

    Далее дерево рекурсивно вычисляется
    при заданном значении x.

    После этого дерево преобразуется:
        A + x  ->  x + A

    В конце программа выводит в файл FN2.txt:
        - результат вычисления
        - префиксную форму
        - постфиксную форму
        - инфиксную форму со скобками.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string v) : value(v), left(nullptr), right(nullptr) {}
};


// ---------------- PRIORITY ----------------

int priority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" ||
           s == "/" || s == "%" || s == "^";
}


// ---------------- INFIX -> POSTFIX ----------------

vector<string> tokenize(const string& expr) {
    vector<string> tokens;

    for (size_t i = 0; i < expr.size();) {

        if (isspace(expr[i])) {
            i++;
        }
        else if (isdigit(expr[i])) {
            string num;

            while (i < expr.size() && isdigit(expr[i])) {
                num += expr[i];
                i++;
            }

            tokens.push_back(num);
        }
        else {
            tokens.push_back(string(1, expr[i]));
            i++;
        }
    }

    return tokens;
}

vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> output;
    stack<string> ops;

    for (const string& token : tokens) {

        if (isdigit(token[0])) {
            output.push_back(token);
        }
        else if (token == "x") {
            output.push_back(token);
        }
        else if (token == "(") {
            ops.push(token);
        }
        else if (token == ")") {

            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }

            ops.pop();
        }
        else {

            while (!ops.empty() &&
                   ops.top() != "(" &&
                   priority(ops.top()[0]) >= priority(token[0])) {

                output.push_back(ops.top());
                ops.pop();
            }

            ops.push(token);
        }
    }

    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}


// ---------------- BUILD TREE ----------------

Node* buildTree(const vector<string>& postfix) {
    stack<Node*> st;

    for (const string& token : postfix) {

        if (!isOperator(token)) {
            st.push(new Node(token));
        }
        else {
            Node* right = st.top();
            st.pop();

            Node* left = st.top();
            st.pop();

            Node* node = new Node(token);
            node->left = left;
            node->right = right;

            st.push(node);
        }
    }

    return st.top();
}


// ---------------- EVALUATION ----------------

int evaluate(Node* root, int x) {

    if (!root->left && !root->right) {

        if (root->value == "x")
            return x;

        return stoi(root->value);
    }

    int left = evaluate(root->left, x);
    int right = evaluate(root->right, x);

    if (root->value == "+") return left + right;
    if (root->value == "-") return left - right;
    if (root->value == "*") return left * right;
    if (root->value == "/") return left / right;
    if (root->value == "%") return left % right;
    if (root->value == "^") return (int)pow(left, right);

    return 0;
}


// ---------------- TRANSFORMATION ----------------

void transform(Node* root) {

    if (!root) return;

    transform(root->left);
    transform(root->right);

    // A + x  ->  x + A

    if (root->value == "+" &&
        root->right &&
        root->right->value == "x" &&
        !(root->left && root->left->value == "x")) {

        swap(root->left, root->right);
    }
}


// ---------------- PRINTS ----------------

void printPrefix(Node* root, ostream& out) {

    if (!root) return;

    out << root->value << " ";

    printPrefix(root->left, out);
    printPrefix(root->right, out);
}

void printPostfix(Node* root, ostream& out) {

    if (!root) return;

    printPostfix(root->left, out);
    printPostfix(root->right, out);

    out << root->value << " ";
}

void printInfix(Node* root, ostream& out) {

    if (!root) return;

    if (isOperator(root->value))
        out << "(";

    printInfix(root->left, out);

    out << root->value;

    printInfix(root->right, out);

    if (isOperator(root->value))
        out << ")";
}


// ---------------- DELETE TREE ----------------

void deleteTree(Node* root) {

    if (!root) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}


// ---------------- MAIN ----------------

int main() {

    ifstream fin("FN1.txt");
    ofstream fout("FN2.txt");

    string expr;
    getline(fin, expr);

    int x;
    fin >> x;

    vector<string> tokens = tokenize(expr);

    vector<string> postfix = infixToPostfix(tokens);

    Node* root = buildTree(postfix);

    // вычисление выражения
    int result = evaluate(root, x);

    fout << "Result: " << result << endl;

    // преобразование дерева
    transform(root);

    fout << endl;

    fout << "Prefix:" << endl;
    printPrefix(root, fout);

    fout << endl << endl;

    fout << "Postfix:" << endl;
    printPostfix(root, fout);

    fout << endl << endl;

    fout << "Infix:" << endl;
    printInfix(root, fout);

    fout << endl;

    deleteTree(root);

    return 0;
}