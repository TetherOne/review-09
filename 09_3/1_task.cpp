/*
https://chatgpt.com/c/6a009613-633c-83eb-b6db-0714d54abf04
Программа "Телеграф" на азбуке Морзе.

    Назначение:
    Программа принимает от пользователя сообщение на русском языке
    и выводит его в виде последовательности точек и тире
    согласно таблице азбуки Морзе.

    Принцип работы:
    1. Пользователь вводит строку с русскими буквами.
    2. Для каждой буквы программа ищет соответствующий код Морзе.
    3. Найденный код выводится на экран.
    4. Между буквами ставится пробел.
    5. Если встречается пробел между словами,
       программа выводит символ "/".
    6. Буквы, которых нет в таблице, игнорируются.

    Для хранения кодов используется map<char, string>.
    Ключ — русская буква.
    Значение — код Морзе.

    Пример:
    Ввод:
    МАМА

    Вывод:
    -- .- -- .-

    Язык программирования: C++
*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

string toUpperCyrillic(const string& s) {
    string result;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if ((c & 0xE0) == 0xC0 && i + 1 < s.size()) {
            unsigned char c2 = static_cast<unsigned char>(s[i + 1]);
            unsigned int cp = ((c & 0x1Fu) << 6u) | (c2 & 0x3Fu);
            if (cp >= 0x0430u && cp <= 0x044Fu) {
                cp -= 0x20u;
                result += static_cast<char>(0xC0u | (cp >> 6u));
                result += static_cast<char>(0x80u | (cp & 0x3Fu));
            } else {
                result += s[i];
                result += s[i + 1];
            }
            i += 2;
        } else {
            result += s[i];
            ++i;
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "");

    map<string, string> morse;

    morse["А"] = ".-";
    morse["Б"] = "-...";
    morse["В"] = ".--";
    morse["Г"] = "--.";
    morse["Д"] = "-..";
    morse["Е"] = ".";
    morse["Ё"] = "..-.";
    morse["Ж"] = "...-";
    morse["З"] = "--..";
    morse["И"] = "..";
    morse["Й"] = ".---";
    morse["К"] = "-.-";
    morse["Л"] = ".-..";
    morse["М"] = "--";
    morse["Н"] = "-.";
    morse["О"] = "---";
    morse["П"] = ".--.";
    morse["Р"] = ".-.";
    morse["С"] = "...";
    morse["Т"] = "-";
    morse["У"] = "..-";
    morse["Ф"] = "..-.";
    morse["Х"] = "....";
    morse["Ц"] = "-.-.";
    morse["Ч"] = "----";
    morse["Ш"] = "----";
    morse["Щ"] = "--.-";
    morse["Ъ"] = ".--.-.";
    morse["Ы"] = "-.--";
    morse["Ь"] = "-...-";
    morse["Э"] = "..-..";
    morse["Ю"] = "..--";
    morse["Я"] = ".-.-";

    string text;
    cout << "Введите сообщение: ";
    getline(cin, text);

    text = toUpperCyrillic(text);

    for (size_t i = 0; i < text.size(); ) {
        unsigned char c = static_cast<unsigned char>(text[i]);
        if (c == ' ') {
            cout << "/ ";
            ++i;
        } else if ((c & 0xE0) == 0xC0 && i + 1 < text.size()) {
            string letter = text.substr(i, 2);
            if (morse.count(letter)) {
                cout << morse[letter] << " ";
            }
            i += 2;
        } else {
            ++i;
        }
    }

    cout << endl;
    return 0;
}
