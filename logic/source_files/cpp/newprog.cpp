#include<bits/stdc++.h>
using namespace std;

const int prime = 99991;

class Hash{
    public:
    int max_num;
    list<pair<int, int>> *str;
    int num_var;
    list<int> *filled;

    Hash(int n,int m){
        // n is the n in 2^n, m the number of cases
        max_num = m;
        num_var = n;
        str = new list<pair<int, int>>[prime];
        filled = new list<int>;
    }

    ~Hash(){
        //delete(str);
        //delete(filled);
    }

    void insert(int x,int index, int has){
        //index is the number of the string, <m, x is the key, i.e the number of 1s
        if(str[x].size()==0){
            filled[0].push_back(has);
        }    
        str[has].push_back(make_pair(x, index));
    }
};
/*
int countOnes(int n) 
{ 
    int count = 0; 
    while (n) { 
        count += n & 1; 
        n >>= 1; 
    } 
    return count; 
}

bool substring_check(string s1, string s2){
    //cout<<s1<<" "<<s2<<endl;
    int n1 = stoi(s1,0,2);
    int n2 = stoi(s2,0,2);
    int count1 = 0, count2 = 0; 
    while (n1) { 
        count1 += n1 & 1; 
        n1 >>= 1; 
    }   
    while (n2) { 
        count2 += n2 & 1; 
        n2 >>= 1; 
    } 
    return (count1==count2); 

} */

// int swap(int arr[], int n, int index){
//     int a[n];
//     for(int i=0;i<n;i++){
//         if(index % 2 ==1)a[n-i-1]=1;
//         else a[n-i-1]=0;
//         index >>= 1;
//     }

//     int exp=1,temp=0;
//     for(int i=0;i<n;i++){
//         temp += a[arr[n-i-1]]*exp;
//         exp <<= 1;
//     }
//     return temp;
// }

// bool equiv(string s1, string s2, int n){
//     int arr[1<<n];
//     for(int i=0;i<(1<<n);i++)arr[i]=0;
//     if(s1==s2)return true;
//     while(next_permutation(arr,arr+(1<<n))){
//         string temp;
//         temp.reserve(1<<n);
//         for(int i=0;i<(1<<n);i++){
//             temp[swap(arr,1<<n,i)] = s1[i];
//         }
//         if(temp==s2)return true;
//     }
//     return false;
// }



bool equiv(string s1, string s2, int n){
	int perm[n];
	for (int i = 0; i < n; ++i)
	{
		perm[i] = i;
	}
	do
	{
		bool isright=1;
		for(int i=0;i<s1.length();i++){
			if(s1[i] == '1'){
				int idx1 = i, idx2 = 0, cbit = 0;
				while(idx1){
					if(idx1&1){
						idx2 += (1<<perm[cbit]);
					}
					idx1 /= 2;
					cbit++;
				}
				if(s2[idx2] != '1'){ isright=0; break;}
			}
		}
		if(isright)return 1;
	} while (next_permutation(perm, perm+n));
	return 0; 
}


int main(){

    int n, num_cases,c,n1;
    cin>>n>>num_cases;
    string s[num_cases];
    Hash h(n,num_cases);
    for(int i=0;i<num_cases;i++){
        cin>>s[i];
        n1 = stoi(s[i],0,2);
        c = 0;
        int index = 0;
        long long has = 1;
        while (n1) { 
	        c += n1 & 1; 
	        int nbeets = 0;
	        int index2 = index;
	        while(index2){
	        	nbeets += (index2&1);
	        	index2 /= 2;
	        }
	        index++;
	        has *= nbeets;
	        has %= prime;
	        n1 /= 10; 
        } 

        h.insert(c,i,has);  
    }

    int count=0;
    //vector<vector<int>> v;
    //vector<int> temp;
    list<int> temp;
    for(auto it=h.filled[0].begin();it!=h.filled[0].end();it++){
        c = *it;
        if(h.str[c].size()==1){count++; /*cout<<c<<endl;*/}
        else{ //2 or more strings with the same number of 1s
            //for(auto it1 = h.str[c].begin();it1 != h.str[c].end();it1++)cout<<*it1;
            //cout<<endl;
            cout<<h.str[c].size()<<endl;
            for(auto it1 = h.str[c].begin();it1 != h.str[c].end();it1++){
                //cout<<*it1<<":checking element\n";
                if(it1->second != -1){
                count++;
                for(auto it2 = next(it1); it2 != h.str[c].end() && h.str[c].size()>1;it2++){
                    if(it2->second != -1 && it2->first == it1->first){
                    	cout<<s[it1->second]<<endl<<s[it2->second]<<endl;
                        if(equiv(s[it1->second],s[it2->second],n)){it2->second = -1; cout<<"Helle\n";}
                    }
                }
            }
            }
        }
    }

    cout<<count<<endl;
}