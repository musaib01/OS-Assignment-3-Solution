#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    while (left.size() > 0 && right.size() > 0)
    {
        if (left[0] < right[0])
        {
            result.push_back(left[0]);
            left.erase(left.begin());
        }
        else
        {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    while (left.size() > 0)
    {
        result.push_back(left[0]);
        left.erase(left.begin());
    }

    while (right.size() > 0)
    {
        result.push_back(right[0]);
        right.erase(right.begin());
    }

    return result;
}

void mergeSort(vector<int>& arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        vector<int> left(arr.begin() + start, arr.begin() + mid + 1);
        vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);

        thread t1(mergeSort, ref(left), 0, left.size() - 1);
        thread t2(mergeSort, ref(right), 0, right.size() - 1);

        t1.join();
        t2.join();

        arr = merge(left, right);
    }
}

int main()
{
    cout << "Enter Total Number Of Array Elements: ";
    int size;
    cin >> size;

    cout << "Enter Array Elements: ";
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    // Performing merge sort algorithm in a separate thread
    thread t(mergeSort, ref(arr), 0, arr.size() - 1);
    t.join();

    cout << "The Sorted Array: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
