// К-ичные числа. Среди чисел в системе счисления с основанием K (2≤K≤10) определить сколько
// имеется чисел из N (1 < N < 20, N + K < 26) разрядов таких, что в их записи содержится два
// и более подряд идущих нулей. Для того, чтобы избежать переполнения, ответ представьте в виде
// вещественного числа.

#include <clocale>
#include <iostream>

using namespace std;

double countNumbersWithConsecutiveZeros(int K, int N) {
    int nz = K - 1;
    int oz = 0;
    int tz = 0;

    for (int i = 2; i <= N; i++) {
        int prev_nz = nz;
        int prev_oz = oz;
        int prev_tz = tz;

        // FIX_ME: имена _nz, _oz, _tz с подчёркиванием — зарезервированы в глобальной области;
        // в функции допустимы, но для читаемости лучше префикс prev_.
        // int _nz = nz;
        nz = (K - 1) * (prev_nz + prev_oz);

        oz = prev_nz;

        tz = prev_tz * K + prev_oz;
    }

    return static_cast<double>(tz);
}

int main() {
    // FIX_ME: setlocale без <clocale> — на строгих компиляторах ошибка; заголовок добавлен.
    // setlocale(LC_ALL, "russian");
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int K, N;
    cout << "Введите основание системы счисления K: ";
    cin >> K;
    cout << "Введите количество разрядов N: ";
    cin >> N;

    // FIX_ME: не проверялись ограничения из условия (2≤K≤10, 1<N<20, N+K<26).
    if (K < 2 || K > 10 || N <= 1 || N >= 20 || N + K >= 26) {
        cerr << "Ошибка: неверные K или N по условию задачи.\n";
        return 1;
    }

    double result = countNumbersWithConsecutiveZeros(K, N);
    cout << "Количество чисел с двумя подряд идущими нулями: " << result << endl;

    return 0;
}
