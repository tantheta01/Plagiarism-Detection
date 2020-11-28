#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    long long int n;
    cin >> n;
    int arr[n];
    for (long long int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long long int left[n];
    left[0] = -1;

    for (long long int i = 1; i < n; i++)
    {
        long long int j = i - 1;
        while ((j >= 0) && (arr[j] < arr[i]))
        {
            j = left[j];
            // cout << "j: " << j << endl;
        }
        left[i] = j;
    }

    for (long long int i = 0; i < n; i++)
    {
        cout << left[i] << " ";
    }
    cout << endl;

    long long int right[n];
    right[n - 1] = -1;
    right_count[n - 1] = 1;

    for (long long int i = n - 2; i >= 0; i--)
    {
        long long int j = i + 1;
        int cnt = 1;

        while ((j <= n - 1) && (arr[j] < arr[i]))
        {
            j = right[j];
            cnt++;
            // if (arr[i] == 3)
            // {
            //     cout << "cnt at every point: " << cnt << endl;
            //     cout << "j at every point: " << j << endl;
            // }
        }
        right[i] = j;
        right_count[i] = cnt;
    }

    // cout << "right count" << endl;
    // for (long long int i = 0; i < n; i++)
    // {
    //     cout << right_count[i] << " ";
    // }
    // cout << endl;

    // long long int answer[n];
    // for (long long int i = 0; i < n; i++)
    // {
    //     answer[i] = left_count[i] * right_count[i];
    // }

    // cout << "answer count" << endl;
    // for (long long int i = 0; i < n; i++)
    // {
    //     cout << answer[i] << " ";
    // }
    // cout << endl;
}