#include <bits/stdc++.h>
using namespace std;

void factorize(int x, int *B, int n){

    for(int i=2;i<=sqrt(x);i++){
        if(x%i==0){
            int fac1 = i, fac2 = x/i;
            B[fac1] += B[fac1-1];
            if(fac1!=fac2)B[fac2] += B[fac2-1];
        }
        B[x]+=B[x-1];
        B[1]+=1;

    }
}




int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    int A[n], B[n+1];
    for(int i=0;i<n;i++){
        cin>>A[i];
        B[i+1]=0;

    }

    for (int i = 0; i < n; ++i)
    {
        factorize(A[i], B);
    }
    cout<<sum(B, n)<<endl;
    return 0;
}