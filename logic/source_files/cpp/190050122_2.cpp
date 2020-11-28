#include <bits/stdc++.h>
using namespace std;


string Fast;
vector<int>V;

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






void partcGeneral(string S, int k) {

	if(Fast.empty()){
		Fast = fundamental[0];
		string t = "a";
		// vector<int>V;
		V.push_back(0);
		V.push_back(fundamental[0].length()-1);
		while(Fast.length() < 20000){
			int j = t.length();
			t = Fast;
			for (int i = j; i < t.length(); ++i)
			{
				Fast += fundamental[(int)(t[i] - 'a')];
			}
			V.push_back(Fast.length()-1);
		}

	}
	int lps[S.length()];
	computeLPS(S, lps);
	int posn = KMPdo(S, Fast, lps);
	if(posn == -1){
		cout<<-1<<"\n";
		return;
	}

	else{
		int whence = -1;
		for(int i=0;i<V.size();i++){
			if(V[i] >= posn){
				whence = i;
				break;
			}
		}
		cout<<whence<<" "<<posn - S.length() + 1<<endl;
	}

}


void partd(string S, int k){

	string R = fundamental[0];
	vector<int>V;
	V.push_back(0);
	V.push_back(fundamental[0].length());
	string T = "a";
	while(R.length() < 3*S.length()){
		
		int l = T.length();
		T = R;
		for(int i=l;i<T.length();i++){
			R += fundamental[(int)(T[i]-'a')];
		}
		V.push_back(R.length());

	}
	int cchar = 0;
	int anss=0;
	// cout<<R<<endl;
	for(int i=0;i<R.length();i++){
		// cout<<cchar<<endl;
		if(cchar==S.length()){ anss=i; break;}
		// cout<<S[cchar]<<R[i]<<endl;
		if(S[cchar] == R[i]){
			cchar++;
		}
	}
	if(cchar == S.length()){
		for(int i=0;i<V.size();i++){
			if(V[i] >= anss){
				cout<<i<<" ";
				break;
			}
		}
		cout<<anss<<endl;
	}
	else
		cout<<"-1"<<endl;

}



unsigned long long part1(int n, int digit, unsigned long long int matrix[][6], int k){

	int initial[k];
	for (int i = 0; i < k; ++i)
	{
		initial[i]=0;
	}
	initial[digit]=1;

	unsigned long long thePower[k][k], theAnswer[k][k];

	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			thePower[i][j] = matrix[i][j];
			theAnswer[i][j]=0;
		}
		theAnswer[i][i]=1;
	}

	while(n){

		if(n%2){
			unsigned long long newAns[k][k];
			for (int i = 0; i < k; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					newAns[i][j] = 0;
					for (int l = 0; l < k; ++l)
					{
						newAns[i][j] += theAnswer[i][l]*thePower[l][j];
					}
				}
			}
			/*theAnswer = newAns;*/

			for(int i=0;i<k;i++){
				for (int j = 0; j < k; ++j)
				{
					theAnswer[i][j] = newAns[i][j];
				}
			}
		}

		unsigned long long newPower[k][k];

		for(int i=0;i<k;i++){
			for(int j=0;j<k;j++){
				newPower[i][j]=0;
				for(int l=0;l<k;l++){
					newPower[i][j] += thePower[i][l]*thePower[l][j];
				}
			}
		}
		for (int i = 0; i < k; ++i)
		{
			for (int j = 0; j < k; ++j)
			{
				thePower[i][j] = newPower[i][j];
			}
		}

		n/=2;
	}
	unsigned long long netAns=0;
	for(int i=0;i<k;i++){
		netAns += theAnswer[i][digit];
	}
	return netAns;


}

char getLastChar(char c, unsigned long long n, int k){
	// n+=1;
	// cout<<n<<" "<<c<<endl;
	// cout<<"HAHAHAHA"<<endl;
	
	vector<char>X;
	// cout<<"HAHAAHA"<<endl;
	/*cout<<"Ajee\n";*/
	int posn[k];
	for(int i=0;i<k;i++)
		posn[i]=-1;

	X.push_back(c);
	posn[(int)(c-'a')]=0;
	int pp=0;
	if(n>k){
		/*cout<<"Heyy this is cool\n"<<n<<endl;*/
		while(n){
			pp++;
			n--;
			char x = fundamental[(int)(c-'a')][fundamental[(int)(c-'a')].length()-1];
			// cout<<x<<endl<<endl<<n<<endl;
			/*cout<<x<<endl;*/
			if(posn[(int)(x-'a')]!=-1){
				int cycs = pp - posn[(int)(x-'a')];
				int Y = n%cycs;
				return X[posn[(int)(x-'a')] + Y];
			}
			posn[(int)(x-'a')] = pp;
			X.push_back(x);
			c = x;
		}
	}

	else{
		int N = n;
		for(int i=0;i<N;i++){
			c = fundamental[(int)(c-'a')][fundamental[(int)(c-'a')].length()-1];
		}
		return c;	
	}
	

}


char part2Util(unsigned long long n, int k, unsigned long long int theAnswer[][6][6], char c, unsigned long long i_){

	// cout<<n<<" "<<i_<<" "<<c<<"\n";
	// n+=1;
	// cout<<"LOLOL"<<endl;
	if(n <= 1){
		// cout<<"N is 1\n";
		// cout<<i_<<" "<<fundamental[(int)(c - 'a')]<<endl;
		return fundamental[(int)(c - 'a')][i_-1];
	}

	unsigned long long nlen=0;

	for(int i=0;i<fundamental[(int)(c - 'a')].length();i++){

		int digit = (int)(fundamental[(int)(c - 'a')][i] - 'a');
		// cout<<digit<<endl;
		// cout<<"DIGI "<<digit<<endl;
		unsigned long long x = 0;
		for(int i1=0;i1<k;i1++){
			x += theAnswer[n-1][i1][digit];
			// cout<<x<<endl;
		}
		// cout<<x<<endl;
		// cout<<i<<" "<<nlen<<" "<<x<<" "<<n<<" "<<c<<endl;

		if(i_ < nlen+x ) { 
			// cout<<"HERE\n";
			return part2Util(n-1, k, theAnswer, fundamental[(int)(c - 'a')][i], i_ - nlen);
		}
		else if(i_ == nlen + x){
			return /*'z';*/ getLastChar(fundamental[(int)(c - 'a')][i], n-1, k);
		}
		else{
			nlen += x;
		}
	}
	

	return 'z';	


}







char part2(unsigned long long i_, unsigned long long matrix[][6], int k){

	if(i_ < fundamental[0].length()){
		return fundamental[0][i_-1];
	}

	unsigned long long theAnswer[90][6][6];


	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++)
			theAnswer[1][i][j] = matrix[i][j];
	}

	int power = 1;

	unsigned long long nlen = 0;
	for (int i = 0; i < k; ++i)
	{
		nlen += matrix[i][0];
	}
	// cout<<nlen<<endl;	

	while(true){

		
		

		// unsigned long long theMatrix[k][k];
		// bool bb = 0;
		for(int i=0;i<k;i++){
			for(int j=0;j<k;j++){
				theAnswer[power+1][i][j] = 0;
				for(int l=0;l<k;l++){
					// if(i == 0 && (i_ - theMatrix[i][j])/matrix[i][l] >= theAnswer[l][j]){
					// 	cout<<"WOW"<<endl;
					// 	bb = 1;
					// 	break;
					// }
					

					theAnswer[power+1][i][j] += matrix[l][j]*theAnswer[power][i][l];

				}
				// if(bb)break;
			}
			// if(bb)break;
		}

		unsigned long long nlen = 0;
		for (int i = 0; i < k; ++i)
		{
			nlen += theAnswer[power+1][i][0];
		}
		
		if(nlen > i_)break;
		// if(bb)break;

		// for(int i=0;i<k;i++){
		// 	for(int j=0;j<k;j++){
		// 		theAnswer[i][j] = theMatrix[i][j];
		// 	}
		// }
		power += 1;
		
		
	}
	// cout<<"The Answer "<<theAnswer[0][0][0]<<" "<<theAnswer[1][0][0]<<" "<<theAnswer[1][1][0]<<endl;

	// cout<<power<<" pppp\n";
	return /*'a';*/ part2Util(power+1, k, theAnswer, 'a', i_);
}




int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
	int k;
	cin>>k;
	string S;
	getline(cin, S);

	for (int i = 0; i < k; ++i)
	{
		getline(cin, fundamental[i]);
	}
	unsigned long long matrix[k][6];

	for(int i=0;i<k;i++){
		for (int j = 0; j < k; ++j)
		{
			matrix[i][j] = 0;
		}
	}
	for(int i=0;i<k;i++){
		for(int j=0;j<fundamental[i].length();j++){
			matrix[(int)(fundamental[i][j]-'a')][i] +=1;
		}

	}

	// for(int i=0;i<k;i++){
	// 	for (int j = 0; j < k; ++j)
	// 	{
	// 		cout<<matrix[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<endl;
	// cout<<fundamental[0]<<" "<<fundamental[1]<<" "<<fundamental[2]<<endl;

	int t;
	cin>>t;
	while(t--){
		int cas;
		cin>>cas;

		if(cas == 0){
			unsigned long long n;
			cin>>n;
			cout<<part1(n, 0, matrix, k)<<endl;
			string S;
			getline(cin, S);
		}

		else if(cas == 1){
			unsigned long long i_;
			cin>>i_;
			cout<<part2(i_+1, matrix, k)<<endl;
			/*cout<<"HAA\n\n\n";*/
			string S;
			getline(cin, S);
		}
		else if(cas == 2){
			// AllSeen.clear();
			string S;

			getline(cin, S);
			S.erase(0,1);
			// cout<<S<<endl;
			partcGeneral(S, k);
		}

		else{
			string S;
			getline(cin, S);
			S.erase(0,1);
			// cout<<S<<endl<<endl;
			partd(S ,k);

		}
	}

	return 0;
}







