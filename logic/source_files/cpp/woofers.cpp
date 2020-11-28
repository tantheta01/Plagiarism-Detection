#include <bits/stdc++.h>
using namespace std;


void Part2(int n, vector<int>V[], int k){
	
	long long hi=600; low=1;


	while(hi>low){
		int mid = (hi+low)/2;
		long long ans1 = 
		if()
	}
	
}


void Part1(int n, vector<int>V[], int k, int dig, long long mLen){

	vector<int>FinMul(k);
	FinMul[dig]=1;
	while(n){
		n/=2;
		if(n%2){
			vector<int>G(k);
			for(int i=0;i<k;i++){	
				for(int j=0;j<k;j++){
					G[i]+=FinMul[j]*V[i][j];
				}
			}
			FinMul=G;
		}

		long long ss=0;
		for (int i = 0; i < k; ++i)
		{
			ss += FinMul[i];
		}
		if(ss>mLen){
			break;
		}

		vector<int>V_(k)[k];
		for(int i=0;i<k;i++){
			for(int j=0;j<k;j++){
				for(int l=0;l<k;l++){
					V_[i][j] += V[i][l]*V[j][l];
				}
			}
		}
		V = V_;
		
	}
	if(n)return 0;

	long long ss=0;
	for (int i = 0; i < k; ++i)
	{
		sum += FinMul[i];
	}
	return sum;

}

