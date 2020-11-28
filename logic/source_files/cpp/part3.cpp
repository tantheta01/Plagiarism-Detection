#include <bits/stdc++.h>
using namespace std;


set<string>AllSeen;

string fundamental[6];

string findString(int index, int power) {

	string current;
	current += (char)('a' + index);


	int cp=0;
	while(cp < power){
		string temp;

		for (int i = 0; i < current.length(); ++i)
		{
			temp += fundamental[(int)(current[i]-'a')];
		}
		++cp;
		current = temp;
	}


	return current;

}

void computeLPS(string pattern, int *lps){

	int n = pattern.length();

	int i=1;
	lps[0]=0;
	int len=0;
	while(i<n) { 

		if(pattern[i] == pattern[len]){
			len++;
			lps[i] = len;
			i++;
		}

		else if(len != 0){
			len = lps[len-1];
		}

		else{
			lps[i]=0;
			i++;
		}
	}

}

int KMPdo(string pattern, string mainstring, int *lps) {

	int n = mainstring.length();
	int m = pattern.length();


	int i=0, j=0;

	while(i<n) {

		if(mainstring[i] == pattern[j]){
			i++;
			j++;
		}

		if(j == m) {
			return i-1;
		}
		else if(i<n && pattern[j] != mainstring[i]) {
			if(j!=0)
				j = lps[j-1];
			else{
				i+=1;
			}
		}
	}

	return -1;

}






int partcGeneral(string S, int k) {

	string high = fundamental[0], low = "a";
	int power=1;
	while(high.length() < S.length()){

		

		int l;
		if(low.empty()){
			l=0;
		}
		else{
			l = low.length();
		}
		int m=high.length();

		for(int i=l; i<m ;i++){
			high += fundamental[(int)(high[i] - 'a')];

		}

		power += 1;

		low = high.substr(0, m);

	}



	int lps[S.length()];
	computeLPS(S, lps);


	

	string allFunds[k];

	allFunds[0] = high;
	bool filled[k];
	for(int i=1;i<k;i++){
		filled[i]=0;
	}
	filled[0]=1;
	

	string expansionNeeded = "a", theonebig = "", theExpansion = "";



	int ans = power;

	
	int l = 0;
	bool next = 1;

	while(next) {

		if(AllSeen.size() >= 100)break;

		next=0;
		for(int i=l;i<expansionNeeded.length();i++){

			int index = (int)(expansionNeeded[i] - 'a');

			if(!filled[index]){
				allFunds[index] = findString(index, power);
				filled[index]=1;
			}
			

			while(!theonebig.empty() && theonebig.length() >= 3 && theExpansion.length() - allFunds[(int)(theonebig[0]-'a')].length() >= S.length()){


				theExpansion.erase(0, allFunds[(int)(theonebig[0]-'a')].length());
				theonebig.erase(theonebig.begin());

			}

			theonebig += expansionNeeded[i];
			theExpansion += allFunds[index];

			if(AllSeen.empty() || AllSeen.find(theonebig) == AllSeen.end()){
				next = 1;
				AllSeen.insert(theonebig);
				int pos1 = KMPdo(S, theExpansion, lps);	
				if(pos1 != -1)return ans;
			}

			
		}

		int clen = expansionNeeded.length();
		for(int i = l; i<clen; i++){



			expansionNeeded += allFunds[(int)(expansionNeeded[i] - 'a')];
		}

		l = clen;

		ans += 1;




	}


	return -1;


}


int partd(string S, int k){

	string R = fundamental[0];
	string T = "a";
	while(R.length() < 2*S.length()){
		
		int l = T.length();
		T = R;
		for(int i=l;i<T.length();i++){
			R += fundamental[(int)(T[i]-'a')];
		}


	}
	int cchar = 0;
	int anss=0;
	for(int i=0;i<R.length();i++){
		if(cchar==S.length()){ anss=i; break;}
		if(S[cchar] == R[i]){
			cchar++;
		}
	}
	if(cchar == S.length()){
		return anss;
	}
	else
		return -1;

}


int main(int argc, char const *argv[])
{
	int k = 3;
	fundamental[0] = "ab";
	fundamental[1] = "bc";
	fundamental[2] = "c";
	string S = "";
	for(int i=0;i<1000;i++){
		S += (char)('a' + (i%3));
	}
	cout<<partcGeneral(S, k);
	return 0;
}






