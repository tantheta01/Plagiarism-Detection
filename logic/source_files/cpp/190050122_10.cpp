#include <bits/stdc++.h>
using namespace std;


void hash22(int n, int m, string S[]){


	int size = (1<<n);
	
	vector<pair<int, int>> V[100003];
	for(int i=0;i<m;i++){

		int ebit[n];
		for(int j=0;j<n;j++)ebit[j] = 1;

		long long hash = 1;
		int count = 0;
		int totOr = 0;
		for(int j=0;j<size;j++){
			if(S[i][j] == '1'){
				count++;
				totOr |= j;
				int nb = 1;
				int anss = j;
				int bit = 0;
				while(anss){
					nb += anss%2;
					ebit[bit] += anss%2;
					anss /= 2;
					bit++;
				}
				hash *= nb;
				hash%=(100003);
			}

		}
		hash%=(100003);
		for(int j=0;j<n;j++){
			hash *= ebit[j];
			hash %= 100003;
		}
		int nset = 0;
		while(totOr){
			nset += totOr%2;
			totOr/=2;
		}
		hash *= nset;
		hash%=100003;

		V[hash].push_back(make_pair(i, count));
	}



	int ndistinct = 0;
	for(int i=0;i<1e5+3;i++){
		if(!V[i].empty()){
			if(V[i].size() == 1){
				ndistinct+=1;
			}
			else{
				int x = V[i].size();
				bool isused[x];
				for(int i=0;i<x;i++){
					isused[i]=0;
				}
				int cind = 0;
				while(x > 1){
					int actind = -1;
					for(int j = cind; j<V[i].size(); j++){
						if(!isused[j])
						{
							cind = j;
							isused[j]=1;
							x-=1;
							break;
						}
					}
					int perm[n];
					vector<int>nvec;
					for(int g = 0;g < size; g++){
						if(S[V[i][cind].first][g] == '1'){
							nvec.push_back(g);
						}
					}
					for(int k=cind + 1; k < V[i].size(); k++){
						for(int l = 0;l<n;l++){
							perm[l] = l;
						}
						if(V[i][cind].second != V[i][k].second)continue;
						if(S[V[i][cind].first][0] != S[V[i][k].first][0] || S[V[i][cind].first][size-1] != S[V[i][k].first][size-1]){
							continue;
						}

						do{
							
							bool ahg = 1;

							for(int g = 0; g < nvec.size(); g++){
								int gg = nvec[g];
								int gg2 = 0;
								int start = 0;
								while(gg){
									if(gg&1){
										gg2 += (1<<(perm[start]));
									}
									gg /= 2;
									start++;
								}
								if(S[V[i][k].first][gg2] == '0'){
									ahg=0;
									break;
								}
							}

							if(ahg){
								isused[k] = 1;
								x-=1;
								break;
							}


						}while(next_permutation(perm, perm+n));

					}
					cind++;
					ndistinct++;

				}

				if (x)
				{
					ndistinct+=1;
				}





			}
		}
	}
	cout<<ndistinct<<"\n";

}











int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
	int n;
	int m;
	cin>>n>>m;
	string S[m];
	for (int i = 0; i < m; ++i)
	{
		cin>>S[i];
	}
	hash22(n, m, S);
	
	return 0;
}