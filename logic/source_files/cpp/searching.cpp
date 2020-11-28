#include <iostream>
#include <vector>
#include "searching.h"
using namespace std;

bool search_custom(vector<int> array, int num,int startidx, int endidx)
{
  // input guaranteed to be in sorted order
  bool flag = 0;
  int low=max(0, startidx), high=min(endidx, array.size()-1);
  while(low<=high){
  	int mid=(low+high)/2;
  	if(array[mid]<num) low=mid+1;
  	else if(array[mid]>num) high=mid-1;
  	else return 1;
  
  }
  return 0;
}
