#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Разделение массива на две части
int part(vector<int>& arr, int low, int high) {
    int p = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= p) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {

        int p = part(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

// Слияние двух подмассивов
void merge(vector<int>& arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1);
    vector<int> right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0;

    int k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// mergeSort
void mergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main() {
    int N = 1000000;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, N);
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = distribution(gen);
    }

    // QuickSort
    auto start = chrono::high_resolution_clock::now();

    quickSort(arr, 0, N - 1);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "QuickSort time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // MergeSort
    start = chrono::high_resolution_clock::now();

    mergeSort(arr, 0, N - 1);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "MergeSort time: " << duration.count() << " ms." << endl;

    return 0;
}