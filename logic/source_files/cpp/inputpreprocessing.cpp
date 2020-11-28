#include <bits/stdc++.h>
using namespace std;



void part2(){

	string S = fundamental[i];
	power = 1;
	while(S.empty() || S.length() <= 1000 && S.length() < index){
		string R = "";

		for(int i=0;i<S.length();i++){
			R += fundamental[(int)(S[i]-'a')];
		}
		S = R;
	}
	
}



int main(int argc, char const *argv[])
{
	int k;
	cin>>k;
	string S;
	getline(cin, S);
	for(int i=0;i<k;i++){
		getline(cin, S);
		fundamental[i]=S;

	}

	vector<int>Matrix[k];
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			Matrix.push_back(0);
		}
	}

	for(int i=0;i<k;i++){
		for(int j=0;j<fundamental[i].length();j++){

		}
	}
	return 0;
}