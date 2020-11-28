#include <iostream>
using namespace  std;



int main(int argc, char const *argv[])
{
	long long a=1, b=1;
	int power=0;
	while(a < 1e18){
		long long temp=a;
		a += b;
		b=temp;
		power+=1;
	}
	cout<<power<<endl;
	return 0;
}