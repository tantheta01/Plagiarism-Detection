#include <bits/stdc++.h>
using namespace std;

struct triplets
{
	int index;
	// int cind;
	long first;
	long second;

};

struct compvec
{
	bool operator()(triplets const &t1, triplets const &t2) const{
		if(t1.first < t2.first)return 1;
		else if(t1.first > t2.first){
			return 0;
		}
		else{
			return t1.second < t2.second;
		}
	}
};

struct compset
{
	bool operator()(triplets const &t1, triplets const &t2){
		return t1.second < t2.second;
	}
};

struct invcom
{
	bool operator()(triplets const &t1, triplets const &t2){
		return t1.second > t2.second;
	}	
};


int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	triplets A[n], B[n];
	for (int i = 0; i < n; ++i)
	{
		long x;
		cin>>x;
		A[i].index = i+1;
		A[i].first = x;
	}
	for (int i = 0; i < n; ++i)
	{
		cin>>A[i].second;
	}

	for (int i = 0; i < n; ++i)
	{
		B[i].index = i+1;
		cin>>B[i].first;
		

	}

	for (int i = 0; i < n; ++i)
	{
		cin>>B[i].second;
	}

	sort(A, A+n, compvec());

	sort(B, B+n, compvec());


	
	int aind = 0, bind=0;
	multiset<triplets, compset> A1, B1;
	bool isimposs=0;
	bool nisunique=0;
	vector<pair<int, int>>perm;

	while(aind < n || bind < n){
		if (A1.empty())
		{
			long val = A[aind].first;
			while(aind<n && A[aind].first == val){
				A1.insert(A[aind]);
				if(aind > 0 && A[aind].first == A[aind-1].first && A[aind].second == A[aind-1].second){
					nisunique=1;
				}
				aind++;
			}
		}
		if (B1.empty())
		{
			long val = B[bind].first;
			while(bind<n && B[bind].first == val){
				if(bind > 0 && B[bind].first==B[bind-1].first && B[bind].second == B[bind-1].second){
					nisunique=1;
				}
				B1.insert(B[bind]);
				bind++;
			}
			
		}
		if(A1.size() >= 2 && B1.size() >= 2){
			nisunique=1;
		}

		if(A1.size() <= B1.size()){


			while(!A1.empty()){

				

				auto p = B1.lower_bound(*(A1.begin()));
			
				if(p == B1.begin() && p->second > A1.begin()->second){
					isimposs=1;
					break;
				}

				if(p==B1.end() || p->second > A1.begin()->second){
					p--;
				}
				// cout<<A1.begin()->first << " "<<A1.begin()->second<<"\n"<<p->first<<" "<<p->second<<"\n";
				perm.push_back(make_pair(A1.begin()->index, p->index));

				A1.erase(A1.begin());
				B1.erase(p);
			}
			



		}

		else{

			while(!B1.empty()){

				auto p = A1.lower_bound(*(B1.begin()));
				if(p == A1.end()){
					isimposs=1;
					break;
				}
				

				perm.push_back(make_pair(p->index, B1.begin()->index));
				B1.erase(B1.begin());
				A1.erase(p);

			}
		}
		if(isimposs){
			cout<<"impossible\n";
			return 0;
			// break;
		}
	}
	if(nisunique){
		
		for (int i = 0; i < n; ++i)
		{
			cout<<perm[i].first<<" ";
		}
		cout<<"\n";
		for (int i = 0; i < n; ++i)
		{
			cout<<perm[i].second<<" ";
		}
		cout<<"\n";
		cout<<"not unique\n";
		return 0;
	}

	multiset<triplets, invcom> A1_, B1_;
	aind=n-1, bind=n-1;
	vector<pair<int, int>> invPerm;

	while(aind >= 0 || bind >= 0){

		if (A1_.empty())
		{
			long val = A[aind].first;
			while(A[aind].first == val){
				A1_.insert(A[aind]);
				aind--;
				
			}
		}
		if (B1_.empty())
		{
			long val = B[bind].first;
			while(B[bind].first == val){
				B1_.insert(B[bind]);
				bind--;
			}
			
		}

		if(A1_.size() >= 2 && B1_.size() >= 2){
			nisunique=1;
		}

		if(A1_.size() <= B1_.size()){
			while(!A1_.empty()){

				auto p = B1_.lower_bound(*(A1_.begin()));
				// if (p==B1_.end())
				// {
				// 	return 0;
				// }
				invPerm.push_back(make_pair(A1_.begin()->index, p->index));
				A1_.erase(A1_.begin());
				B1_.erase(p);

			}
		}

		else{
			while(!B1_.empty()){

				auto p = A1_.lower_bound(*(B1_.begin()));
				if(p == A1.end()){
					// if(p==A1.begin()){
					// 	return 0;
					// }
					p--;
				}
				invPerm.push_back(make_pair(p->index, B1_.begin()->index));
				A1_.erase(p);
				B1_.erase(B1_.begin());

			}
		}





	}

	// for(int i=0;i<n;i++){
	// 	if(perm[i].first != invPerm[n-1-i].first || perm[i].second != invPerm[n-1-i].second){
	// 		// cout<<"not unique\n";
	// 		nisunique=1;

	// 	}
	// }
	
	// for (int i = 0; i < n; ++i)
	// {
	// 	cout<<perm[i].first<<" ";
	// }
	// cout<<"\n";
	// for (int i = 0; i < n; ++i)
	// {
	// 	cout<<perm[i].second<<" ";
	// }
	// cout<<"\n";

	// if(!nisunique){
	// 	cout<<"unique\n";
	// }
	// else cout<<"not unique\n";



	return 0;
}