#include<bits/stdc++.h>
#include<chrono>
using namespace std;
long long mod__ = 1e9+7;

int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
typedef long long ll;
#define pb push_back
const ll INF = 1e18;

	int pro(int n, int aray[])
	{
		vector<int> v;
		int visit[n] = {0}, c = 0;
		for(int i=0;i<n;i++)
		{
			if(visit[i])
				continue;
			c = 1;
			int curr = aray[i];
			while(curr != i)
			{
				c++;
				curr = aray[curr];
			}
			v.pb(c);
		}
		int ans = 1;
		for(auto x: v)
			ans = ans/__gcd(ans, x)*x;
		return ans;
	}




class permutation
{
	int size_;
	int *graph;
public:
	permutation(int n, int *array){
		int *perm = new int[n];
		for(int i=0;i<n;i++){
			perm[i]=array[i];
		}
		graph = perm;
		size_ = n;
	}

	permutation(const permutation &p){
		delete graph;
		int *graphP = p.to_array();
		int *newGraph = new int[p.size()];
		for(int i=0;i<p.size();i++){
			newGraph[i] = graphP[i];
		}
		graph = newGraph;
		size_ = p.size();
	}
	const permutation& operator=(const permutation &p){
		delete graph;
		int *graphP = p.to_array();
		int *newGraph = new int[p.size()];
		for(int i=0;i<p.size();i++){
			newGraph[i] = graphP[i];
		}
		graph = newGraph;
		size_ = p.size();
		return *this;
	}
	int size()const{
		return size_;

	}
	int* to_array()const{
		int *newGraph = new int[size_];
		for(int i=0;i<size_;i++){
			newGraph[i]=graph[i];
		}
		return newGraph;
	}


	permutation const operator-()const{
		int *newGraph = new int[size_];
		for(int i=0;i<size_;i++){
			newGraph[graph[i]]=i;
		}
		return permutation(size_,newGraph);
	}
	permutation const operator*(const permutation &p)const{
		int *nG = p.to_array();
		int *fG = new int[size_+1];
		for(int i=0;i<size_;i++){
			fG[i] = graph[nG[i]];
		}
		delete nG;
		return permutation(size_, fG);
	}
	permutation const operator^(long long x){

		bool B[size_];
		int *newGraph = new int[size_];
		for(int i=0;i<size_;i++)
			B[i]=0;

		for(int j=0;j<size_;j++){
			if(B[j]==0){
				int cind = j;
				vector<int>V(size_);
				int cou = 0;
				while(B[cind] == 0){
					B[cind]=1;
					V[cou]=cind;
					cind = graph[cind];
					cou++;
				}
				for(int i=0;i<cou;i++){
					int ind2 = (i+x)%cou;
					// cout<<V[ind2]<<endl;
					newGraph[V[i]]=V[ind2];
				}

			}
		}
		return permutation(size_, newGraph);
	}

	permutation const square_root()const{

		bool B[size_];
		int *newGraph = new int[size_+1];
		// vector<int>Esize, Estart;
		int existingS[size_+1];
		memset(existingS, -1, sizeof(existingS));


		for(int i=0;i<size_;i++)
			B[i]=0;

		for(int j=0;j<size_;j++){
			if(B[j]==0){
				int cind = j;
				vector<int>V(size_);
				int cou = 0;
				while(B[cind] == 0){
					B[cind]=1;
					/*cout<<"The CIND IS "<<cind<<endl;	*/
					V[cou] = cind;
					cind = graph[cind];
					cou++;
				}
				/*cout<<"COCOCOC\n"<<cou<<endl;*/
				if(cou%2)
				for(int l=0;l<cou;l++){
					int ind2 = (l+(cou+1)/2)%cou;
					newGraph[V[l]]=V[ind2];
				}
				else{
					// cout<<"Jingle bell jingle bell\n";
					if(existingS[cou]!=-1){
						// cout<<"Buggu kfdm\n";
						int ind1=j;
						int ind2 = existingS[cou];
						int l=0;
						while(l<cou){
							newGraph[ind1]=ind2;
							ind1=graph[ind1];
							newGraph[ind2] = ind1;
							ind2=graph[ind2];
							l++;
						}
						existingS[cou]=-1;
					}
					else{
						existingS[cou]=j;
					}
				}

			}


		}
		bool iden=0;
		for(int i=1;i<=size_;i++){
			if(existingS[i]!=-1){
				iden=1;
				break;
			}
		}
		if(iden){
			for(int i=0;i<size_;i++){
				newGraph[i]=i;
			}
			
		}
		return permutation(size_, newGraph);

	}


	long long log(const permutation &q){

		bool isiden=1;
		for(int i=0;i<size_;i++){
			if(graph[i]!=i)
				{isiden=0;
					break;}

		}
		if(isiden)return 0;
		int *Qgraph = q.to_array();
			

		bool isp[size_];
		for (int i = 0; i < size_; ++i)
		{
			isp[i]=0;
		}
		int numcyc[size_];

		int poscyc[size_];


		int cycs=0;
		int cycsize[size_];
		for(int i=0;i<size_;i++){
			if(isp[i]==0){
				int curr=i;
				int poss=1;

				while(isp[curr] == 0){
					isp[curr]=1;
					numcyc[curr] = cycs;
					poscyc[curr]=poss;
					poss++;
					curr = Qgraph[curr];
				}
				cycsize[cycs]=poss-1;
				cycs+=1;
			}
		}
		bool done[size_];
		memset(done, 0, sizeof(done));
		


		vector<int>cc(cycs, -1);

		for(int i=0;i<size_;i++){
			if(done[i]==0){
				
				int curr=i;
				int prevel=-1;
				while(done[curr]==0){
					done[curr]=1;

					
					if(numcyc[curr]!=numcyc[i]){ /*cout<<cycs<<" "<<numcyc[curr]<<" "<<numcyc[i];*/ return -1;}



					if((prevel!=-1) && (cc[numcyc[i]]!=-1)){



						int diff = (poscyc[curr]-poscyc[prevel]+cycsize[numcyc[curr]])%cycsize[numcyc[curr]];
						if(diff!=cc[numcyc[curr]])
							{/* cout<<"HHHA111\n";*/ return -1;}
						


					}


					else if(prevel!=-1){


						cc[numcyc[i]]=(poscyc[curr]-poscyc[prevel]+cycsize[numcyc[curr]])%cycsize[numcyc[curr]];

					}

					prevel=curr;
					curr = graph[curr];
						
					
				}


				
				if((poscyc[curr] - poscyc[prevel] + cycsize[numcyc[curr]])%cycsize[numcyc[curr]] != cc[numcyc[curr]] && cc[numcyc[curr]]!=-1)
					{/*cout<<"HERE\n"<<curr<<" "<<i<<" "<<prevel<<"\n";*/ return -1;}
				if(cc[numcyc[curr]]==-1)
					cc[numcyc[curr]]=0;
			}
		}
		// return 0;

		long long base = 1ll;
		long long rem = 0ll;
		

		for(int i=0;i<cycs;i++){
			
			
			bool ppos=0;
			for(int j=0;j<cycsize[i];j++){
				
				if(((base*j)%cycsize[i]) == ((cc[i]-rem%cycsize[i] + cycsize[i])%cycsize[i])){
					rem = base*j + rem;
					
					

					ppos=1;
					break;
				}
				
			}
			if(!ppos){/*cout<<rem<<" "<<"HHHA\n"<<rem;*/ return -1; }
			for(int j=0;j<25;j++){
				long long b1=base, b2=1;
				while((cycsize[i]%primes[j] == 0) && (b1%primes[j]==0)){
					cycsize[i]/=primes[j];
					b1/=primes[j];
				}
			}
			base=base*cycsize[i];
			
		}

		return rem%mod__;



	}



	bool is_power(const permutation &q){

		bool isiden=1;
		int *Qgraph = q.to_array();
		for(int i=0;i<size_;i++){
			if(Qgraph[i]!=i)
				{isiden=0;
					break;}

		}
		if(isiden)return 1;
		
			

		bool isp[size_];
		for (int i = 0; i < size_; ++i)
		{
			isp[i]=0;
		}
		int numcyc[size_];

		int poscyc[size_];


		int cycs=0;
		int cycsize[size_];
		for(int i=0;i<size_;i++){
			if(isp[i]==0){
				int curr=i;
				int poss=1;

				while(isp[curr] == 0){
					isp[curr]=1;
					numcyc[curr] = cycs;
					poscyc[curr]=poss;
					poss++;
					curr = graph[curr];
				}
				cycsize[cycs]=poss-1;
				cycs+=1;
			}
		}
		bool done[size_];
		memset(done, 0, sizeof(done));
		


		vector<int>cc(cycs, -1);

		for(int i=0;i<size_;i++){
			if(done[i]==0){
				
				int curr=i;
				int prevel=-1;
				while(done[curr]==0){
					done[curr]=1;

					
					if(numcyc[curr]!=numcyc[i]){ /*cout<<cycs<<" "<<numcyc[curr]<<" "<<numcyc[i];*/ return -1;}



					if((prevel!=-1) && (cc[numcyc[i]]!=-1)){



						int diff = (poscyc[curr]-poscyc[prevel]+cycsize[numcyc[curr]])%cycsize[numcyc[curr]];
						if(diff!=cc[numcyc[curr]])
							{ /*cout<<"HHHA111\n";*/ return 0;}
						


					}


					else if(prevel!=-1){


						cc[numcyc[i]]=(poscyc[curr]-poscyc[prevel]+cycsize[numcyc[curr]])%cycsize[numcyc[curr]];

					}

					prevel=curr;
					curr = Qgraph[curr];
						
					
				}


				
				if((poscyc[curr] - poscyc[prevel] + cycsize[numcyc[curr]])%cycsize[numcyc[curr]] != cc[numcyc[curr]] && cc[numcyc[curr]]!=-1)
					{/*cout<<"HERE\n"<<curr<<" "<<i<<" "<<prevel<<"\n";*/ return 0;}
				if(cc[numcyc[curr]]==-1)
					cc[numcyc[curr]]=0;
			}
		}
		// return 0;

		long long base = 1ll;
		long long rem = 0ll;
		

		for(int i=0;i<cycs;i++){
			
			
			bool ppos=0;
			for(int j=0;j<cycsize[i];j++){
				
				if(((base*j)%cycsize[i]) == ((cc[i]-rem%cycsize[i] + cycsize[i])%cycsize[i])){
					rem = base*j + rem;
					
					

					ppos=1;
					break;
				}
				
			}
			if(!ppos){/*cout<<rem<<" "<<"HHHA\n"<<rem;*/ return 0; }
			for(int j=0;j<25;j++){
				long long b1=base, b2=1;
				while((cycsize[i]%primes[j] == 0) && (b1%primes[j]==0)){
					cycsize[i]/=primes[j];
					b1/=primes[j];
				}
			}
			base=base*cycsize[i];
			
		}
		return 1;



	}

	~permutation(){
		delete graph;
	}
	
};


// int main(int argc, char const *argv[])
// {
// 	int A[] = {1,2,3,0,5,6,7,4};
// 	permutation p(8, A);
// 	permutation q=p.square_root();
	
// 	permutation X = q^2;
// 	int *r = X.to_array();
// 	for(int i=0;i<=7;i++)cout<<r[i]<<endl;
// 	return 0;
// }

int main()
{
	srand(time(0));
	int n = 100;
	int aray[n];
	for(ll i=0;i<n;i++)
		aray[i] = i;
	int t = 100000;
	int c = 0, high = 0, same = 0;
	int total = 0;
	while(t--)
	{
		ll raise = rand()%(INF);
		random_shuffle(aray, aray+n);
		permutation p = permutation(n, aray);
		int lcm = pro(n, aray);
		auto start = std::chrono::high_resolution_clock::now();
		permutation q = p^2;
		p = q.square_root();
		p = p^2;
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		total += duration.count();
		int *arr = q.to_array(), *a = p.to_array();
		for(int i=0;i<n;i++)
		{
			if(a[i] != arr[i])
			{
				c++;
				break;
			}
		}
	}
	cout<<"Number of wrong answers: "<<c<<"\n";
	cout<<"Execution time (in microseconds): "<<total<<"\n";
	return 0;
}
