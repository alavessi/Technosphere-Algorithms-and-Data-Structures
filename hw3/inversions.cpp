#include <iostream>
#include <vector>

long long inversions = 0;

void merge(std::vector<int>& a, int low, int mid, int high, int* aux)
{
    for (int i = low; i <= high; i++)
    {
        aux[i] = a[i];
    }
    int i = low, j = mid + 1, k = low;
    while (k <= high)
    {
        if (i <= mid && j <= high)
        {
            if (aux[j] < aux[i])
            {
                a[k++] = aux[j++];
                inversions += mid + 1 - i;
            }
            else
            {
                a[k++]=aux[i++];
            }
        }
        else
        {
            if (i > mid)
            {
                a[k++] = aux[j++];
            }
            else
            {
                a[k++] = aux[i++];
            }
        }
    }
}

void mergeSort(std::vector<int>& a, int low, int high, int* aux)
{
    if (high > low)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid, aux);
        mergeSort(a, mid + 1, high, aux);
        merge(a, low, mid, high, aux);
    }
}

void sort_merge(std::vector<int>& a, int n)
{
    int* aux = new int[n];
    mergeSort(a, 0, n - 1, aux);
    delete [] aux;
}

int main()
{
    unsigned n;
    std::cin >> n;
    std::vector<int> a(n);
    for (unsigned i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    sort_merge(a, n);
    std::cout << inversions;
    return 0;
}
