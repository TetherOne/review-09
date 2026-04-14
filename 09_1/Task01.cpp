// Археолог нашел N артефактов. Известны веса (ci) и налоговое бремя (di) находок.
// Нужно выбрать такое подмножество находок, чтобы их суммарный вес превысил Z кг, а их общее
// налоговое бремя оказалось минимальным. Известно, что решение единственно. Укажите
// порядковые номера вещей, которые нужно взять. Исходные данные находятся в текстовом файле,
// в первой строке указаны N и Z, а во второй строке значения весов (в кг), в третьей - величина
// налога по каждой находке. Вывести так же суммарный вес и общую ценность результата.

#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

// FIX_ME: подключался Windows.h и вызывались SetConsoleCP/SetConsoleOutputCP — на macOS/Linux
// заголовок отсутствует, консоль UTF-8 по умолчанию; локаль не нужна для чтения из файла.
// #include <Windows.h>
// SetConsoleCP(1251);
// SetConsoleOutputCP(1251);

using namespace std;

int main() {
    int N, Z;
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "Ошибка. Не удалось открыть файл.";
        return 1;
    }

    if (!(input >> N >> Z)) {
        cerr << "Ошибка. Неверное значение переменных N и Z.";
        return 1;
    }

    // FIX_ME: проверяли только N < 0 и Z < 0, ноль пропускался при тексте «должны быть больше 0».
    // if (N<0 || Z<0)
    if (N <= 0 || Z <= 0) {
        cerr << "Ошибка. параметры N и Z должны быть больше 0.";
        return 1;
    }

    vector<int> weights(N);
    for (int i = 0; i < N; i++) {
        input >> weights[i];
    }

    vector<int> tax(N);
    for (int i = 0; i < N; i++) {
        input >> tax[i];
    }

    // FIX_ME: для INT_MAX нужен <climits>; без него поведение не определено.
    // const int INF = INT_MAX;
    const int kInf = INT_MAX;
    vector<int> dp(Z + 110, kInf);
    dp[0] = 0;

    // FIX_ME: без C++11 пара `>>` в шаблонах читается как оператор сдвига — нужен пробел между `>`.
    // vector<vector<bool>> used(Z + 110, vector<bool>(N, false));
    vector<vector<bool> > used(Z + 110, vector<bool>(N, false));

    for (int i = 0; i < N; i++) {
        for (int j = Z + 109; j >= weights[i]; j--) {
            if (dp[j - weights[i]] != kInf && dp[j - weights[i]] + tax[i] < dp[j]) {
                dp[j] = dp[j - weights[i]] + tax[i];
                used[j] = used[j - weights[i]];
                used[j][i] = true;
            }
        }
    }

    int min_tax = kInf;
    int best_weight = 0;
    vector<bool> best_use(N, false);

    for (int j = Z + 1; j <= Z + 109; j++) {
        if (dp[j] < min_tax) {
            min_tax = dp[j];
            best_weight = j;
            best_use = used[j];
        }
    }

    cout << "Выбранные артефакты: ";
    for (int i = 0; i < N; i++) {
        if (best_use[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    // FIX_ME: в слове «Суммарный» стояла латинская «C» вместо кириллической «С».
    // cout << "Cуммарный вес артефактов: " << best_weight << endl;
    cout << "Суммарный вес артефактов: " << best_weight << endl;
    cout << "Общая ценность: " << min_tax << endl;

    return 0;
}
