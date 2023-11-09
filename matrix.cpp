#include <cstdint>
#include <iostream>
#include <utility>

typedef unsigned un;

int **createMatrix(un n, un m)
{
    int **x = new int *[n];

    for (un i = 0; i < n; i++)
        x[i] = new int[m];

    for (un i = 0; i < n; i++)
        for (un j = 0; j < m; j++)
            x[i][j] = 0;

    return x;
}

void deleteMatrix(int **A, un n)
{
    for (un i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;
}

void printMatrix(int **A, un n, un m)
{
    std::cout << "\n";
    for (un i = 0; i < n; i++)
    {
        for (un j = 0; j < m; j++)
            std::cout << A[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void fillRandom(int **A, un n, un m)
{
    srand(time(0));

    for (un i = 0; i < n; i++)
        for (un j = 0; j < m; j++)
            A[i][j] = 10 + rand() % 89;
}

std::pair<un, un> maxElem(int **A, un n, un m)
{
    int max = INT32_MIN;
    std::pair<un, un> index{0, 0};

    for (un i = 0; i < n; i++)
        for (un j = 0; j < m; j++)
            if (max < A[i][j])
            {
                max = A[i][j];
                index.first = i;
                index.second = j;
            }

    return index;
}

std::pair<un, un> minElem(int **A, un n, un m)
{
    int min = INT32_MAX;
    std::pair<un, un> index{0, 0};

    for (un i = 0; i < n; i++)
        for (un j = 0; j < m; j++)
            if (min > A[i][j])
            {
                min = A[i][j];
                index.first = i;
                index.second = j;
            }

    return index;
}

int main(int argc, char *argv[])
{
    const un n = 4;
    const un m = 4;

    int **A = createMatrix(n, m);

    fillRandom(A, n, m);
    printMatrix(A, n, m);
    auto min = minElem(A, n, m);
    auto max = maxElem(A, n, m);
    std::cout << min.first << " " << min.second << "\n";
    std::cout << max.first << " " << max.second << "\n";
    return 0;
}
