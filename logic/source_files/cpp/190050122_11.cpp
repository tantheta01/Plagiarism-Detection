#include <bits/stdc++.h>
using namespace std;



int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int n, m, u, v;
    cin>>n>>m>>u>>v;
    int oddDist1[n];
    int evenDist1[n];
    for(int i=0;i<n;i++){
        oddDist1[i]=-1;
        evenDist1[i]=-1;
    }
    evenDist1[u]=0;
    list<int> adJnodes[n];
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        adJnodes[a].push_back(b);
        adJnodes[b].push_back(a);

    }
    queue<pair<int, int>> ourStack;
    ourStack.push(make_pair(0, u));
    //timestamp shall store the lenght of path
    int timeStamp=0;


    //doing our BFS
    while(!ourStack.empty()){
        pair<int, int> vert = ourStack.front();
        ourStack.pop();
        timeStamp=vert.first+1;
        for(auto it = adJnodes[vert.second].begin();it!=adJnodes[vert.second].end();it++){

            int v2 = *it;
            if(timeStamp%2 == 0){
                if(evenDist1[v2]==-1){
                    evenDist1[v2] = timeStamp;
                    ourStack.push(make_pair(timeStamp, v2));
                }

            }
            if(timeStamp%2 == 1){
                if (oddDist1[v2]==-1)
                {
                    oddDist1[v2]=timeStamp;
                    ourStack.push(make_pair(timeStamp, v2));
                }
            }
            if(evenDist1[v]!=-1)break;

        }
        if(evenDist1[v]!=-1)break;
    }
    if(evenDist1[v]==-1){
        cout<<"impossible"<<endl;
        return 0;
    }
    else{

        
        cout<<"possible\n";
        cout<<evenDist1[v]/2<<"\n";
        while(!ourStack.empty())ourStack.pop();
        int oddDist2[n], evenDist2[n];
        for(int i=0;i<n;i++){
            oddDist2[i]=-1;
            evenDist2[i]=-1;
        }
        evenDist2[v]=0;
        timeStamp=0;
        ourStack.push(make_pair(0,v));
        while(!ourStack.empty()){
            pair<int, int> vert = ourStack.front();
            ourStack.pop();
            timeStamp=vert.first+1;
            for(auto it = adJnodes[vert.second].begin();it!=adJnodes[vert.second].end();it++){

                int v2 = *it;
                if(timeStamp%2 == 0){
                    if(evenDist2[v2]==-1){
                        evenDist2[v2] = timeStamp;
                        ourStack.push(make_pair(timeStamp, v2));
                    }

                }
                if(timeStamp%2 == 1){
                    if (oddDist2[v2]==-1)
                    {
                        oddDist2[v2]=timeStamp;
                        ourStack.push(make_pair(timeStamp, v2));
                    }
                }
                if(evenDist2[u]!=-1)break;

            }
            if(evenDist2[u]!=-1)break;
        }
        // for(int i=0;i<n;i++){
        //     cout<<i<<" "<<evenDist2[i]<<endl;
        // }
        if(evenDist2[u]%4 == 0){
            for(int i=0;i<n;i++){
            //     cout<<evenDist2[i]<<endl;
                if(evenDist1[i] == evenDist2[i] && 2*evenDist1[i] == evenDist1[v]){
                    cout<<i<<" ";
                }
            }
            cout<<"\n";
        }

        else{
            for(int i=0;i<n;i++){
                if(oddDist2[i] == oddDist1[i] && 2*oddDist1[i] == evenDist1[v]){
                    cout<<i<<" ";
                }
            }
            cout<<"\n";
        }

    }
    return 0;
}