// Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения,
// не содержат пробелов. При выполнении заданий не следует использовать оператор цикла.
// Вывести значение логического выражения, заданного в виде строки S. Выражение определяется следующим
// образом («T» — True, «F» — False):
//     <выражение> ::= T | F | And(<выражение>, <выражение>) | Or(<выражение>, <выражение>)


#include <cctype>
#include <clocale>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

bool evaluateExpression(const string& expression, size_t& pos);

// FIX_ME: в условии запрещены циклы; skipWhitespaces использовал while — заменено на рекурсию.
// void skipWhitespaces(const string& expression, int& pos) {
//     while (pos < expression.length() && isspace(expression[pos]))
//         pos++;
// }
void skipWhitespaces(const string& expression, size_t& pos) {
    if (pos >= expression.size()) {
        return;
    }
    unsigned char ch = static_cast<unsigned char>(expression[pos]);
    if (!isspace(ch)) {
        return;
    }
    pos++;
    skipWhitespaces(expression, pos);
}

bool evaluateExpression(const string& expression, size_t& pos) {
    skipWhitespaces(expression, pos);
    if (pos >= expression.size()) {
        throw invalid_argument("Неожиданный конец выражения");
    }
    if (expression[pos] == 'T') {
        pos++;
        return true;
    }
    if (expression[pos] == 'F') {
        pos++;
        return false;
    }
    if (expression.compare(pos, 3, "And") == 0) {
        pos += 3;
        skipWhitespaces(expression, pos);
        if (pos >= expression.size() || expression[pos] != '(') {
            throw invalid_argument("Ожидается '(' после 'And'");
        }
        pos++;
        bool left = evaluateExpression(expression, pos);
        skipWhitespaces(expression, pos);
        if (pos >= expression.size() || expression[pos] != ',') {
            throw invalid_argument("Ожидается ',' после первого аргумента в 'And'");
        }
        pos++;
        bool right = evaluateExpression(expression, pos);
        skipWhitespaces(expression, pos);
        if (pos >= expression.size() || expression[pos] != ')') {
            throw invalid_argument("Ожидается ')' после второго аргумента 'And'");
        }
        pos++;
        return left && right;
    }
    if (expression.compare(pos, 2, "Or") == 0) {
        pos += 2;
        skipWhitespaces(expression, pos);
        if (pos >= expression.size() || expression[pos] != '(') {
            throw invalid_argument("Ожидается '(' после 'Or'");
        }
        pos++;
        bool left = evaluateExpression(expression, pos);
        skipWhitespaces(expression, pos);
        if (pos >= expression.size() || expression[pos] != ',') {
            throw invalid_argument("Ожидается ',' после первого аргумента в 'Or'");
        }
        pos++;
        bool right = evaluateExpression(expression, pos);
        skipWhitespaces(expression, pos);
        if (pos >= expression.size() || expression[pos] != ')') {
            throw invalid_argument("Ожидается ')' после второго аргумента в 'Or'");
        }
        pos++;
        return left || right;
    }
    throw invalid_argument("Недопустимое выражение в позиции " + to_string(pos));
}

int main() {
    // FIX_ME: setlocale вызывался внутри evaluateExpression при каждом узле — перенесено в main один раз.
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string expression;
    cout << "Введите логическое выражение: ";
    getline(cin, expression);

    try {
        size_t pos = 0;
        bool result = evaluateExpression(expression, pos);
        skipWhitespaces(expression, pos);
        if (pos < expression.size()) {
            throw invalid_argument("Недопустимые символы в конце выражения");
        }
        cout << "Результат: " << (result ? "True" : "False") << endl;
    } catch (const invalid_argument& e) {
        cout << "Ожидается: " << e.what() << endl;
        return 1;
    }
    return 0;
}
