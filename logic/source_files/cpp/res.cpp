#include <bits/stdc++.h>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

struct tripl{
	int f,s,idx;

	tripl(){
		f=0;s=0;idx=0;
	}

	tripl(int fv, int sv, int idxv){
		this->f = fv;
		this->s = sv;
		this->idx = idxv;
	}

	bool operator<(tripl& t2){
		if(this->f < t2.f) return true;
		else return false;
	}

};

struct desc{
	bool operator()(tripl& T1, tripl& T2){
		if(T1.s > T2.s) return true;
		else return false;
	}
};

struct asc{
	bool operator()(tripl& T1, tripl& T2){
		if(T1.s<T2.s) return true;
		else return false;
	}
};

int b_search_larg(int st_idx, int fin_idx, vector<tripl> S, int val){
	int mid_idx = (st_idx + fin_idx)/2;
	//cout << st_idx << mid_idx << fin_idx << endl; 
	if(st_idx==fin_idx || S[mid_idx].s==val) return mid_idx;
	else if(S[mid_idx].s>val) {return b_search_larg(mid_idx+1, fin_idx, S, val);}
	else return b_search_larg(st_idx, mid_idx, S, val);
}

int b_search_small(int st_idx, int fin_idx, vector<tripl> S, int val){
	int mid_idx = (st_idx + fin_idx)/2;
	if(st_idx==fin_idx || S[mid_idx].s==val) return mid_idx;
	else if(S[mid_idx].s<val) return b_search_larg(mid_idx+1, fin_idx, S, val);
	else return b_search_larg(st_idx, mid_idx, S, val);
}

bool ques1(int it1, int it2, vector<tripl> S1, vector<tripl> S2){
	//cout << it1 << " " << it2 << endl;

	int st1=it1, st2=it2;
	//cout << "called!" << endl;
	//for(int i=0; i<S1.size(); i++) cout << S1[i].f << " " << S1[i].s << " " << S1[i].idx << "    " << S2[i].f << " " << S2[i].s << " " << S2[i].idx << endl;
	
	int l1=0,l2=0;
	
	//Find Cardinalities of A,C
	while(it1!=S1.size()){
		it1++; l1++;
		if(S1[st1].f != S1[it1].f) break;
	}
	while(it2!=S2.size()){
		it2++; l2++;
		if(S2[st2].f != S2[it2].f) break;
	}

	//cout << l1 << " " << l2 << " " << S1[st1].idx << " " << S2[st2].idx << endl;

	if(l1<=l2){
	//	cout << "l1 <= l2" << endl;
		sort(S2.begin()+st2, S2.begin()+it2, desc());
	//	for(int i=0; i<S1.size(); i++) cout << S1[i].f << " " << S1[i].s << " " << S1[i].idx << "    " << S2[i].f << " " << S2[i].s << " " << S2[i].idx << endl;
	
		int j=st2;
		
		for(int i=st1; i!=it1; i++){
			if(S1[i].s >= S2[j].s) j++;
			else if(S2[it2-1].s > S1[i].s) return false;
			else{
				int ch = b_search_larg(j,it2-1,S2,S1[i].s);
	//			cout << ch << endl;
				tripl tmp = S2[ch];
				S2[ch] = S2[j];
				S2[j] = tmp;
				sort(S2.begin()+j+1, S2.begin()+it2, desc());
	//			cout << endl;
	//			for(int i=0; i<S1.size(); i++) cout << S1[i].f << " " << S1[i].s << " " << S1[i].idx << "    " << S2[i].f << " " << S2[i].s << " " << S2[i].idx << endl;
	//			cout << endl;
				j++;
			}
		}
	}
	else{
	//	cout << "l1 > l2" << endl;
		sort(S1.begin()+st1, S1.begin()+it1, asc());
	//	for(int i=0; i<S1.size(); i++) cout << S1[i].f << " " << S1[i].s << " " << S1[i].idx << "    " << S2[i].f << " " << S2[i].s << " " << S2[i].idx << endl;
		
		int i=st1;
		
		for(int j=st2; j!=it2; j++){
			if(S1[i].s >= S2[j].s) i++;
			else if(S1[it1-1].s < S2[j].s) return false;
			else{
				int ch = b_search_small(i,it1-1,S1,S2[j].s);
				tripl tmp = S1[ch];
				S1[ch] = S1[i];
				S1[i] = tmp;
				sort(S1.begin()+i+1, S1.begin()+it1, asc());
	//			cout << endl;
	//			for(int i=0; i<S1.size(); i++) cout << S1[i].f << " " << S1[i].s << " " << S1[i].idx << "    " << S2[i].f << " " << S2[i].s << " " << S2[i].idx << endl;
	//			cout << endl;
				i++;
			}
		}
	}

	if(it1==S1.size() && it2==S2.size()){
		for(int i=0; i<S1.size(); i++) cout << S1[i].idx << " ";
		cout << endl;
		for(int i=0; i<S2.size(); i++) cout << S2[i].idx << " ";
		cout << endl;
		return true;
	}		
	else if(l1<=l2) return ques1(it1, it1, S1, S2);
	else if(l1>l2) return ques1(it2, it2, S1, S2);
}


int main(){
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

	int n; cin >> n;
	vector<tripl> S1(n);
	vector<tripl> S2(n);

	vector<int> a(n);vector<int> b(n);vector<int> c(n);vector<int> d(n);

	for(int i=0; i<n; i++){
		cin >> a[i];
	}

	for(int i=0; i<n; i++){
		cin >> b[i];
	}

	for(int i=0; i<n; i++){
		cin >> c[i];
	}

	for(int i=0; i<n; i++){
		cin >> d[i];
	}

	for(int i=0; i<n; i++){
		tripl tmp(a[i], b[i], i+1);
		S1[i] = tmp;
	}
	for(int i=0; i<n; i++){
		tripl tmp(c[i], d[i], i+1);
		S2[i] = tmp;
	}

	//IO DONE! LOGIC FROM HERE!
	sort(S1.begin(), S1.end());
	sort(S2.begin(), S2.end());

	if(ques1(0, 0, S1, S2) == false) cout << "Impossible" << endl;

	return 0;
}