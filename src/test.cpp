#include <array>
#include <iostream>

template <size_t N> void print_array(std::array<int, N> *arr)
{
    for (int i : *arr)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

template <size_t N> int product(std::array<int, N> *arr)
{
    int res = 1;
    for (int i = 0; i < N; i++)
    {
        if (2 * i < N)
            // if (arr[i] != 0)
            res *= arr->at(2 * i);
    }
    return res;
}

template <size_t N> int sum_between_zeros(std::array<int, N> *arr)
{
    int res = 0;
    unsigned first, last;

    for (int i = 0; i < N; i++)
    {
        if (arr->at(i) == 0)
        {
            first = i;
            break;
        }
    }

    for (int i = N - 1; i >= 0; i--)
    {
        if (arr->at(i) == 0)
        {
            last = i;
            break;
        }
    }

    for (int i = first; i < last; i++)
    {
        res += arr->at(i);
    }
    return res;
}

template <size_t N> void rearrange(std::array<int, N> *arr)
{
    int j = 0;
    int temp = 0;

    for (int i = 0; i < N; i++)
    {
        if (arr->at(i) >= 0)
        {
            temp = arr->at(j);
            arr->at(j) = arr->at(i);
            arr->at(i) = temp;
            j++;
        }
    }
}

int main(int argc, char *argv[])
{
    const unsigned LEN = 10;
    int *a = new int[LEN];

    std::array<int, LEN> b{1, -1, 2, -2, 3, -3, 4, -4, 5, -5};

    // for (int i = 1; i < LEN; i++) {
    //   a[i - 1] = i;
    // }

    print_array(&b);
    std::cout << product(&b) << "\n";
    std::cout << sum_between_zeros(&b) << "\n";
    rearrange(&b);
    // print_array(&c);
    print_array(&b);
    return 0;
}
