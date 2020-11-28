#include <iostream>
#include <vector>
#include "searching.h"
using namespace std;

int main()
{
  int n, num;
  vector<int> array(n);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> array[i];
  }
  cin >> num;
  if (search_custom(array, num) == 1)
    cout << "Found" << endl;
  else
    cout << "Not Found" << endl;
}
