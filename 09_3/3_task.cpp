/*
https://chatgpt.com/c/6a009546-4890-83eb-b425-8b736e1a962e
Поиск всех маршрутов из города K1 в город K2
    с ровно L пересадками.

    Граф задается матрицей смежности.
    m[i][j] = 1 — перелет существует.
    m[i][j] = 0 — перелета нет.

    Используется DFS.
    Строим все возможные пути длины L + 1 перелетов.

    Если найден путь до K2,
    сохраняем его в список маршрутов.

    После поиска маршруты сортируются
    в лексикографическом порядке.

    Если маршрутов нет — выводится -1.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int K1, K2, L;

vector<vector<int> > graph;
vector<vector<int> > routes;

void dfs(int current, vector<int>& path)
{
    if (path.size() == L + 2)
    {
        if (current == K2)
        {
            routes.push_back(path);
        }
        return;
    }

    for (int next = 1; next <= n; next++)
    {
        if (graph[current][next] == 1)
        {
            path.push_back(next);

            dfs(next, path);

            path.pop_back();
        }
    }
}

int main()
{
    ifstream fin("FileName1.txt");
    ofstream fout("FileName2.txt");

    fin >> n;

    graph.resize(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fin >> graph[i][j];
        }
    }

    fin >> K1 >> K2 >> L;

    vector<int> path;
    path.push_back(K1);

    dfs(K1, path);

    sort(routes.begin(), routes.end());

    if (routes.empty())
    {
        fout << -1;
    }
    else
    {
        fout << routes.size() << endl;

        for (int i = 0; i < routes.size(); i++)
        {
            for (int j = 0; j < routes[i].size(); j++)
            {
                fout << routes[i][j] << " ";
            }

            fout << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}