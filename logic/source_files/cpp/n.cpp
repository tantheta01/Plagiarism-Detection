#include <bits/stdc++.h>
using namespace std;


double A[1001][1001];
int main(int argc, char const *argv[])
{
	int t;
	cin>>t;

	for (int i = 0; i < 1001; ++i)
	{
		A[i][0]=1.0;
		for(int j=1;j<=i;j++){
			A[i][j] = A[i-1][j-1] + A[i-1][j];
		}
	}


	while(t--){
		int n;
		cin>>n;
		int k;
		cin>>k;
		double prices[n], desc[k];
		for(int i=0;i<n;i++)
			cin>>prices[i];

		for(int i=0;i<k;i++){
			cin>>desc[i];
			desc[i]/=100;
		}
		sort(prices, prices+n, greater<double>());
		sort(desc, desc+k, greater<double>());
		double totans=0;
		for(int i=0;i<n;i++){
			double exp = 0.00;
			for(int j = max(0, k-n+i); j<=min(k-1, i); j++ ){
				exp += 	(A[i][j]/A[n][k])*A[n-1-i][k-1-j]*desc[j];
			}
			totans += prices[i]*exp;
		}
		printf("%.3lf\n",totans);

	}
	return 0;
}