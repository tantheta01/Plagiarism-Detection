#include <bits/stdc++.h>
using namespace std;

string fundamental[6];




void PartThree(string ToFind, int k) {

	int n=ToFind.length();

	vector<string> AllInverses[n];

	int maxFChar=0;

	for(int i=0;i<k;i++){
		maxFChar = max(maxFChar, fundamental[i].length());

	}

	for(int i=0;i<n;i++) {

		if(i+1 <= maxFChar) { 
			for(int j=0;j<k;j++){

				if(fundamental[j].length() > i && fundamental[j].substr(fundamental[j].size() - i - 1, i+1) == ToFind.substr(0, i+1)){

					string S;
					S += (char)('a' + j);

					AllInverses[i].push_back(S);

				}

			}
		}


		for(int j=0;j<k;j++) {
			if((i+1) > )
		}

	}

}




int actualPart2(int n, int Posn, vector<int>matrix, int k, int digit){

	if(n==0)return dig;

	long totlen=0;
	for(int i=0;i<S[digit].length();i++){
		totlen += Part1(n-1, matrix, k, (int)(S[digit][i]-'a'), 1e18);
		if(totlen>=Posn){
			return actualPart2(n-1, totlen-Part1(n-1, matrix, k, (int)(S[digit][i]-'a'), 1e18), k, S[digit][i]-'a');
		}
	}




}













int Part2(long long Posn, vector<int>matrix, int k){

	int hi=600;
	int low=1;
	while(hi>low){
		int mid=(hi+low)/2;
		long long n=Part1(mid, matrix, k, 0, Posn);
		if(n<Posn){
			low=mid+1;

		}
		else if(n==Posn){
			hi=mid;
			break;
		}
		else{
			hi=mid;
		}
	}

}



long long Part1(int n, int matrix[][6], int k, int digit, long long maxLen) {

	vector<int> initialVec(k);
	initialVec[digit]=1;

	int currentDic[k][k], powerDic[k][k];
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			currentDic[i][j] = 1;
			powerDic[i][j] = matrix[i][j];
		}
	}



	while(n){

		if(n%2){
			
			for(int i=0;i<k;i++){
				for (int j = 0; j < k; ++j)
				{
					newDict[i].push_back(currentDic[i][j]);
					currentDic[i][j]=0;
					newPower[i].push_back(powerDic[i][j]);
					powerDic[i][j] = 0;

				}
			}
			for(int i=0;i<k;i++){
				for(int j=0;j<k;j++){
					for(int l=0;l<k;l++){
						currentDic[i][j] += newDict[i][l]*powerDic[l][j];
					}
				}
			}

		}



		for (int i = 0; i < k; ++i)
		{
			for (int j = 0; j < k; ++j)
			{
				for (int l = 0; l < k; ++l)
				{
					powerDic[i][j] += newPower[i][k]*newPower[k][j];
				}
			}
		}

		n/=2;

	}

	long long ans=0;
	for (int i = 0; i < k; ++i)
	{
		ans += currentDic[i][digit];
	}

	return ans;
}