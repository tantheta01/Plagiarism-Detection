#include<bits/stdc++.h>
//#include "suddu.h"
#include<chrono>
using namespace std;

class quad_tree{
    int dimension;
    int value;
    quad_tree* topLeft;
    quad_tree* topRight;
    quad_tree* bottomLeft;
    quad_tree* bottomRight;
    public:
    quad_tree(int n){

        topLeft=topRight=bottomLeft=bottomRight = NULL;
        value = 0;
        dimension = n;
       
    }

    ~quad_tree(){
        if(topRight!=NULL){    
        // topRight->~quad_tree();
        // topLeft->~quad_tree();
        // bottomLeft->~quad_tree();
        // bottomRight->~quad_tree();    
        delete(topLeft);
        delete(topRight);
        delete(bottomRight);
        delete(bottomLeft);
        topLeft=topRight=bottomLeft=bottomRight = NULL;
        }
    }

    quad_tree(quad_tree const &Q){
        
        this->dimension = Q.dimension;
        this->value = Q.value;
        if(Q.topRight != NULL){    
        topRight = new quad_tree(*(Q.topRight));
        topLeft = new quad_tree(*(Q.topLeft));
        bottomRight = new quad_tree(*(Q.bottomRight));
        bottomLeft = new quad_tree(*(Q.bottomLeft));
        }
        else{
            topLeft=topRight=bottomLeft=bottomRight = NULL;
        }
    }

    void set(int x1, int y1, int x2, int y2, int b){

          if(x1 ==0 && y1 == 0 && x2 == (1<<dimension)-1 && y2 == (1<<dimension)-1){
            this->value=b;
            delete(topLeft);
            delete(topRight);
            delete(bottomRight);
            delete(bottomLeft);
            topLeft=topRight=bottomLeft=bottomRight = NULL;
            return;
        }
        if(b==this->value)return;
        if(topRight == NULL){
            topLeft = new quad_tree(dimension-1);
            topLeft->value = this->value;
            topRight = new quad_tree(dimension-1);
            topRight->value = this->value;
            bottomLeft = new quad_tree(dimension-1);
            bottomLeft->value = this->value;
            bottomRight = new quad_tree(dimension-1);
            bottomRight->value = this->value;
            this->value = -1;
        }
      
        int l = 1<<(dimension-1);
        if(x1>=l){
            //all in the right side
            if(y1>=l){
                //all are in top right
                topRight->set(x1-l,y1-l,x2-l,y2-l,b);
                return;
            }
            else{
                if(y2<l){
                    bottomRight->set(x1-l,y1,x2-l,y2,b);
                    return;
                }
                else{
                    topRight->set(x1-l,0,x2-l,y2,b);
                    bottomRight->set(x1-l,y1,x2-l,l-1,b);
                    return; 
                }
            }
        }
        else{
            if(x2<l){
                if(y1>=l){
                    topLeft->set(x1,y1-l,x2,y2-l,b);
                    return;
                }
                else{
                    if(y2<l){
                        bottomLeft->set(x1,y1,x2,y2,b);
                        return;
                    }
                    else{
                        topLeft->set(x1,0,x2,y2-l,b);
                        bottomLeft->set(x1,y1,x2,l-1,b);
                        return;
                    }
                }
            }
            else{
                if(y1>=l){
                    topLeft->set(x1,y1-l,l-1,y2-l,b);
                    topRight->set(0,y1-l,x2-l,y2-l,b);
                    return;
                }
                else{
                    if(y2<l){
                        bottomLeft->set(x1,y1,l-1,y2,b);
                        bottomRight->set(0,y1,x2-l,y2,b);
                        return;
                    }
                    else{
                        bottomLeft->set(x1,y1,l-1,l-1,b);
                        bottomRight->set(0,y1,x2-l,l-1,b);
                        topLeft->set(x1,0,l-1,y2-l,b);
                        topRight->set(0,0,x2-l,y2-l,b);
                        return;
                    }
                }
            }
        }
    
    }

    int get(int x1, int y1){
        if(topRight==NULL){
            return this->value;
        }
        int l = 1<<(dimension-1);
        if(x1<l){
            if(y1<l){
                return bottomLeft->get(x1,y1);
            }
            else return topLeft->get(x1,y1-l);
        }
        else{
            if(y1<l){
                return bottomRight->get(x1-l,y1);
            }
            else return topRight->get(x1-l,y1-l);
        }
    }

    int size() const{
        return dimension;
    }

    void overlap(quad_tree const &Q){
        if(Q.topLeft == NULL){
            if(Q.value==1){
                delete(topRight);
                delete(topLeft);
                delete(bottomLeft);
                delete(bottomRight);
                topLeft=topRight=bottomLeft=bottomRight = NULL;
                this->value = 1;
                return;
            }
        }
        else if(topRight == NULL){
            if(value==0){
                topRight = new quad_tree(*(Q.topRight));
                topLeft = new quad_tree(*(Q.topLeft));
                bottomLeft = new quad_tree(*(Q.bottomLeft));
                bottomRight = new quad_tree(*(Q.bottomRight));
                return;
            }
        }
        else{
            topRight->overlap(*(Q.topRight));
            bottomRight->overlap(*(Q.bottomRight));
            topLeft->overlap(*(Q.topLeft));
            bottomLeft->overlap(*(Q.bottomLeft));
        }
    }

    void intersect(quad_tree &Q){

            if(Q.topLeft == NULL){
            if(Q.value==0){
                delete(topRight);
                delete(topLeft);
                delete(bottomLeft);
                delete(bottomRight);
                topLeft=topRight=bottomLeft=bottomRight = NULL;
                this->value = 0;
                return;
            }
            }
            else if(topRight == NULL){
            if(value==1){
                topRight = new quad_tree(*(Q.topRight));
                topLeft = new quad_tree(*(Q.topLeft));
                bottomLeft = new quad_tree(*(Q.bottomLeft));
                bottomRight = new quad_tree(*(Q.bottomRight));
                return;
            }
            }
            else{
            topRight->intersect(*(Q.topRight));
            bottomRight->intersect(*(Q.bottomRight));
            topLeft->intersect(*(Q.topLeft));
            bottomLeft->intersect(*(Q.bottomLeft));
            }
        value = (value & Q.value);
        if(dimension>0){
            topRight->intersect(*(Q.topRight));
            bottomRight->intersect(*(Q.bottomRight));
            topLeft->intersect(*(Q.topLeft));
            bottomLeft->intersect(*(Q.bottomLeft));
        } 
    }

    void complement(){
        value = !value;
        if(topLeft!=NULL){
            topLeft->complement();
            topRight->complement();
            bottomLeft->complement();
            bottomRight->complement();
        }
    }

    void resize_child(int k){
        if(topRight==NULL){
            dimension+=k;
        }
        else{
            dimension+=k;
            topRight->resize_child(k);
            topLeft->resize_child(k);
            bottomRight->resize_child(k);
            bottomLeft->resize_child(k);
        }
    }

    unsigned long long int numOne(int k){
    unsigned long long int result;
    if(dimension>k){
        
        if(topLeft!=NULL){
            result =topLeft->numOne(k);
            result =topRight->numOne(k);
            result =bottomLeft->numOne(k);
            result =bottomRight->numOne(k);
        }
        dimension-=k;
        return 0;
    }
    else if(dimension==k)
    {
        if(topRight!=NULL){
        result = topLeft->numOne(k) + topRight->numOne(k)+bottomLeft->numOne(k) + bottomRight->numOne(k);
        
        if(result>=(1<<((2*dimension)-1))){
            value = 1;
        }
        else{ value = 0;
        }
        delete(topLeft);delete(topRight);delete(bottomLeft);delete(bottomRight);
        topLeft=topRight=bottomLeft=bottomRight = NULL;
        }
        dimension-=k;
        return 0;
    }

    else if(dimension<k && dimension>=0){
        if(topRight==NULL)return value*(1<<(2*dimension));
        else{
            result = topLeft->numOne(k) + topRight->numOne(k)+bottomLeft->numOne(k) + bottomRight->numOne(k);
                delete(topLeft);delete(topRight);delete(bottomLeft);delete(bottomRight);
                topLeft=topRight=bottomLeft=bottomRight = NULL;
            return result;
        }
    }
    return 0;
}

    void resize(int m){
        if(m>dimension){
            if(topRight==NULL){
                dimension = m;
            }
            else{
                topRight->resize_child(m-dimension);
                topLeft->resize_child(m-dimension);
                bottomRight->resize_child(m-dimension);
                bottomLeft->resize_child(m-dimension);
                dimension = m;
            }
            
        }
        else if(m<dimension){
            if(topRight==NULL){
                dimension = m;}
            else{
                unsigned long long int k=numOne(dimension-m);
                dimension = m;
            }
        }
    }

    void extract(int x1, int y1, int m){
        return;
    }; 
   
};


int main() {
    int n;
    cin >> n;
    vector<quad_tree> Q (2,quad_tree(n));
    int t;
    cin >> t;
    double setduration = 0, getduration = 0, orduration = 0, andduration = 0, complementduration = 0, resizeduration = 0, extractduration = 0;
    while(t--) {
        char c;
        cin >> c;
        switch(c) {
            case 'S':
            {   
                int id;
                int x1,y1,x2,y2;
                bool b;
                cin >> id >> x1 >> y1 >> x2 >> y2 >> b;
                auto t1 = chrono::high_resolution_clock::now();
                Q[id].set(x1,y1,x2,y2,b);
                auto t2 = chrono::high_resolution_clock::now();
                setduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
                break;
            }
            case 'G':
            {
                int x,y,id;
                cin >> id >> x >> y;
                auto t1 = chrono::high_resolution_clock::now();
                cout << Q[id].get(x,y) << endl;
                auto t2 = chrono::high_resolution_clock::now();
                getduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
                break;
            }
            case 'O':
            {
                int id;
                cin >> id;
                auto t1 = chrono::high_resolution_clock::now();
                Q[id].overlap(Q[(id+1)%2]);
                auto t2 = chrono::high_resolution_clock::now();
                orduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
                break;
            }
            case 'I':
            {
                int id;
                cin >> id;
                auto t1 = chrono::high_resolution_clock::now();
                Q[id].intersect(Q[(id+1)%2]);
                auto t2 = chrono::high_resolution_clock::now();
                andduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
                break;
            }
            // case 'C':
            // {
            //     int id;
            //     cin >> id;
            //     auto t1 = chrono::high_resolution_clock::now();
            //     Q[id].complement();
            //     auto t2 = chrono::high_resolution_clock::now();
            //     complementduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
            //     break;
            // }
            // case 'R':
            // {
            //     int m;
            //     cin >> m;
            //     auto t1 = chrono::high_resolution_clock::now();
            //     Q[0].resize(m);
            //     Q[1].resize(m);
            //     auto t2 = chrono::high_resolution_clock::now();
            //     resizeduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
            //     break;
            // }
            // case 'E':
            // {
            //     int x,y,m;
            //     cin >> x >> y >> m;
            //     auto t1 = chrono::high_resolution_clock::now();
            //     Q[0].extract(x,y,m);
            //     Q[1].extract(x,y,m);
            //     auto t2 = chrono::high_resolution_clock::now();
            //     extractduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
            //     break;
            // }
        }
    }
    cout << "Completion" << endl;
    cout << setduration << endl;
    cout << getduration << endl;
    cout << orduration << endl;
    cout << andduration << endl;
    cout << complementduration << endl;
    cout << resizeduration << endl;
    cout << extractduration << endl;

    // int n=20;
    // vector<quad_tree> Q (2,quad_tree(n));
	// Q[0].set(0,0,7,6,1);
	// cout<<Q[0].size()<<endl;
	// Q[0].complement();
	// cout<<Q[0].size()<<endl;
	// Q[0].set(0,7,7,7,0);
	// cout<<Q[0].size()<<endl;
    // cout<<Q[0].get(0,7)<<endl;
	// Q[1].set(0,1,2,1,1);
	// cout<<Q[1].size()<<endl;
	// Q[1].set(0,2,3,2,1);
	// Q[1].resize(1);
	// cout<<Q[1].size()<<endl;

}