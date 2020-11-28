#include <bits/stdc++.h>
using namespace std;
#include<chrono>


class quad_node
{
public:
	int size;
	bool value;
	quad_node *topLeft, *topRight, *bottomLeft, *bottomRight;
	quad_node(int s){
		size=s;
		value=0;
		topRight = nullptr;
		topLeft = nullptr;
		bottomLeft = nullptr;
		bottomRight = nullptr;

	}
	quad_node(int s, int val){
		this->size = s;
		this->value = val;
		this->topRight = nullptr;
		this->topLeft = nullptr;
		this->bottomLeft = nullptr;
		this->bottomRight = nullptr;
		
	}


	~quad_node(){
			if (this)
			{
				delete this->topLeft;
				delete this->topRight;
				delete this->bottomLeft;
				delete this->bottomRight;	
				this->topRight = nullptr;
				this->topLeft = nullptr;
				this->bottomLeft = nullptr;
				this->bottomRight = nullptr;
				size=0;
				value=0;
	
			}
			return;
		
	}

	quad_node(quad_node *q){
		topLeft = nullptr;
		topRight = nullptr;
		bottomLeft = nullptr;
		bottomRight = nullptr;
		if(q->topLeft != nullptr){
			topLeft = new quad_node(q->topLeft);
			topRight = new quad_node(q->topRight);
			bottomLeft = new quad_node(q->bottomLeft);
			bottomRight = new quad_node(q->bottomRight);
		}
		size = q->size;
		value = q->value;
		
		return;
		
	}
	quad_node(quad_node const &q){
		if (topRight!=nullptr)
		{
			try{
				delete topRight;
				delete topLeft;
				delete bottomRight;
				delete bottomLeft;	
			}
			catch(...){}
			topRight = topLeft = bottomLeft = bottomRight = nullptr;
		}
		size = q.size;
		value = q.value;
		topRight = new quad_node(*(q.topRight));
		topLeft = new quad_node(*(q.topLeft));
		bottomRight = new quad_node(*(q.bottomRight));
		bottomLeft = new quad_node(*(q.bottomLeft));

	}

	void set(int x1, int y1, int x2, int y2, int b){
		if (size == 0)
		{
			value = b;
			return;
		}
		if(x1 == 0 && x2 == (1ll<<size) && y1 == 0 && y2 == (1ll<<size)){
			delete topLeft;
			delete topRight;
			delete bottomLeft;
			delete bottomRight;
			topRight = topLeft = bottomLeft = bottomRight = nullptr;
			value = b;
			return;
		}
		if (x1 == x2 || y1 == y2)
		{
			return;
		}

		else{
			if(topLeft == nullptr){
				/*if(topRight!=nullptr || bottomLeft != nullptr || bottomRight != nullptr)cout<<"oyeee"<<endl<<endl<<endl<<endl;*/
				if(size == 0){
					value=b;
					return;
				}
				delete topRight;
				delete topLeft;
				delete bottomRight;
				delete bottomLeft;
				topRight = new quad_node(size-1, value);
				topLeft = new quad_node(size-1, value);
				bottomRight = new quad_node(size-1, value);
				bottomLeft = new quad_node(size-1, value);
			}


			if(x1 < (1<<(size-1))){
				if (y1 < (1<<(size-1)))
				{
					topLeft->set(x1, y1, min((1<<(size-1)), x2), min((1<<(size-1)), y2), b);
				}
				if (y2 > (1<<(size-1)))
				{
					bottomLeft->set(x1, max(0, y1 - (1<<(size-1))), min((1<<(size-1)), x2), y2-(1<<(size-1)), b);	
				}
			}
			if(x2 > (1<<(size-1))){

				if (y1 < (1<<(size-1)))
				{
					topRight->set(max(0, x1 - (1<<(size-1))), y1, x2-(1<<(size-1)), min((1<<(size-1)), y2), b);
				}
				if (y2 > (1<<(size-1)))
				{
					bottomRight->set(max(0, x1-(1<<(size-1))), max(0, y1-(1<<(size-1))), x2-(1<<(size-1)), y2-(1<<(size-1)), b);
				}
			}
		}

		if (topLeft->topLeft == nullptr && topRight->topLeft == nullptr && bottomRight->topLeft == nullptr && bottomLeft->topLeft == nullptr && topLeft->value == topRight->value && topRight->value == bottomLeft->value && bottomLeft->value == bottomRight->value)
		{
			value = topRight->value;
			delete topRight;
			delete topLeft;
			delete bottomRight;
			delete bottomLeft;
			topRight = topLeft = bottomLeft = bottomRight = nullptr;
		}

	}

	int get(int x1, int y1){
		if (size==0)
		{
			return value;
		}

		if (topLeft == nullptr)
		{
			return value;
		}
		
		if(x1 < (1<<(size - 1))){
			if(y1 < (1<<(size - 1))){
				return topLeft->get(x1, y1);
			}
			else{
				// cout<<"hh33"<<endl;
				return bottomLeft->get(x1, y1 - (1<<(size - 1)));	
			}
		}
		else{
			if(y1 < (1<<(size - 1))){
				// cout<<"hh44"<<endl;
				return topRight->get(x1 - (1<<(size - 1)), y1);
			}
			else{
				// cout<<"hh55"<<endl;
				return bottomRight->get(x1 - (1<<(size - 1)), y1 - (1<<(size - 1)));	
			}	
		}

	}



	void overlap(quad_node *q){

		if(topLeft==nullptr){
			if (value == 1)
			{
				return;
			}
			else{
				if(q->topLeft == nullptr){
					value = q->value;
					return;
				}
				else{
					// cout<<"hahahaha"<<endl;
					topLeft = new quad_node(q->topLeft);
					topRight = new quad_node(q->topRight);
					bottomLeft = new quad_node(q->bottomLeft);
					bottomRight = new quad_node(q->bottomRight);
					return;
				}
			}
		}
		if (q->topRight == nullptr)
		{
			// if(a){
			// 	cout<<"here is "<<endl;
			// }



			if (q->value == 1)
			{
				
					// cout<<"id::2"<<endl;
					delete topRight;
					delete topLeft;
					delete bottomRight;
					delete bottomLeft;	

					topRight = nullptr;
					topLeft = nullptr;
					bottomRight = nullptr;
					bottomLeft = nullptr;
				
				
					value = 1;
					return;
			}
			else{
				// cout<<"id::3"<<endl;
				return;
			}
		}
		
		else{
			// cout<<"id::6"<<endl;

			topLeft->overlap(q->topLeft);
			topRight->overlap(q->topRight);
			bottomLeft -> overlap(q->bottomLeft);
			bottomRight->overlap(q->bottomRight);

			if (topLeft->topLeft == nullptr && topRight->topLeft == nullptr && bottomRight->topLeft == nullptr && bottomLeft->topLeft == nullptr && topLeft->value == topRight->value && topRight->value == bottomLeft->value && bottomLeft->value == bottomRight->value)
			{
				// cout<<"id::7"<<endl;
				value = topRight->value;
				delete topRight;
				delete topLeft;
				delete bottomRight;
				delete bottomLeft;
				topRight = nullptr;
				topLeft = nullptr;
				bottomRight = nullptr;
				bottomLeft = nullptr;
				return;
			}
			return;


		}
		// if(a){
		// 	cout<<"no return"<<endl;
		// }
	}

	void intersect(quad_node *q){
		// cout<<"This ass killed meeeeeeeeee"<<endl<<size<<endl;
		if(size == 0){
			value = value & q->value;
			// if(topRight!=nullptr)/*cout<<"Oye bhosdike sunnnnnnnnnnnnnnnnnnnnnnnnnnnnn"<<endl;*/
			return;
		}
		if (q->topRight == nullptr)
		{
			if (q->value == 0)
			{
				if(topRight!=nullptr){

					delete topRight;
					delete topLeft;
					delete bottomRight;
					delete bottomLeft;	
				}
				topRight = nullptr;
				topLeft = nullptr;
				bottomRight = nullptr;
				bottomLeft = nullptr;
				value = 0;
				return;
			}
			else{
				return;
			}
		}
		if (topLeft == nullptr)
		{
			if (value == 0)
			{
				return;
			}
			else{
				topLeft = new quad_node(q->topLeft);
				topRight = new quad_node(q->topRight);
				bottomLeft = new quad_node(q->bottomLeft);
				bottomRight = new quad_node(q->bottomRight);
				return ;
			}
		}
		else{
			topLeft->intersect(q->topLeft);
			topRight->intersect(q->topRight);
			bottomLeft -> intersect(q->bottomLeft);
			bottomRight->intersect(q->bottomRight);

			if (topLeft->topLeft == nullptr && topRight->topLeft == nullptr && bottomRight->topLeft == nullptr && bottomLeft->topLeft == nullptr && topLeft->value == topRight->value && topRight->value == bottomLeft->value && bottomLeft->value == bottomRight->value)
			{
				value = topRight->value;
				delete topRight;
				delete topLeft;
				delete bottomRight;
				delete bottomLeft;
				topRight = nullptr;
				topLeft = nullptr;
				bottomRight = nullptr;
				bottomLeft = nullptr;
			}


		}
	}
	void complement(){
		if (topLeft == nullptr)
		{
			value = !value;
			return;
		}
		topLeft->complement();
		topRight->complement();
		bottomRight->complement();
		bottomLeft->complement();
	}

	void incsize(int k){
		size+=k;
		if (topRight!=nullptr)
		{
			topRight->incsize(k);
			topLeft->incsize(k);
			bottomRight->incsize(k);
			bottomLeft->incsize(k);
		}
	}
	long long decsize(int k){
		if (size > k)
		{
			size-=k;

			if (topRight==nullptr)
			{
				return 0ll;
			}
			else{
				topRight->decsize(k);
				topLeft->decsize(k);
				bottomRight->decsize(k);
				bottomLeft->decsize(k);
				return 0ll;
			}
		}

		else if(size < k){
			if (topRight == nullptr)
			{
				long long a1 = (1ll<<(2*size));
				return value*a1;
			}
			else{
				long long Ans = topRight->decsize(k) + topLeft->decsize(k) + bottomRight->decsize(k) + bottomLeft->decsize(k);
				return Ans;
			}
		}
		else{
			if (topRight == nullptr)
			{
				return 0ll;
			}

			long long Ans = topRight->decsize(k) + topLeft->decsize(k) + bottomRight->decsize(k) + bottomLeft->decsize(k);
			delete topRight;
			delete bottomRight;
			delete topLeft;
			delete bottomLeft;
			topRight = nullptr;
			topLeft = nullptr;
			bottomRight = nullptr;
			bottomLeft = nullptr;
			
			if (Ans >= (1ll<<(2*size -1)))
			{
				value=1;

			}
			else value=0;

		}
		return 0ll;
	}


	quad_node* extract(int x1, int y1, int m){
		if(m == 0){
			// cout<<"id::6"<<endl;
			quad_node *q = new quad_node(0, this->get(x1, y1));
			return q;
		}
		
		if (topRight == nullptr)
		{
			quad_node *q = new quad_node(m, value);
			return q;

		}
		
		// if()return new quad_node(0, value);

		else{
			// cout<<"M is "<<m<<endl;
			long long x2 = x1+(1<<m);
			long long y2 = y1+(1<<m);
			long long halfLine = (1<<(size-1));
			if (x2 <= halfLine && y2 <= halfLine)
			{
				// cout<<"id::1"<<endl;
				quad_node *q = topLeft->extract(x1, y1, m);
				// if (q->topLeft != nullptr && q->topRight == nullptr)
				// {
				// 	// cout<<"Theek hai ye problem hai yaaar maereko merkw qwhhfaaoef\n\n\n"<<endl;
				// }
				return q;
			}

			else if(x2 <= halfLine && y1 >= halfLine){
				// cout<<"id::2"<<endl;
				quad_node *q = bottomLeft->extract(x1, y1-halfLine, m);
				
				return q;
			}
			else if (x1 >= halfLine && y2 <= halfLine)
			{
				
				quad_node *q= topRight->extract(x1-halfLine, y1, m);
				return q;
			}
			else if (x1 >= halfLine && y1 >= halfLine)
			{

				quad_node *q = bottomRight->extract(x1-halfLine, y1-halfLine, m);
				return q;
			}

			quad_node* Q = new quad_node(m);
			Q->topLeft = this->extract(x1, y1, m-1);
			Q->topRight = this->extract((x1+x2)/2, y1, m-1);
			Q->bottomLeft = this->extract(x1, (y1+y2)/2, m-1);
			Q->bottomRight = this->extract((x1+x2)/2, (y1+y2)/2, m-1);
			if (Q->topLeft->topLeft == nullptr && Q->topRight->topLeft == nullptr && Q->bottomRight->topLeft == nullptr && Q->bottomLeft->topLeft == nullptr && Q->topLeft->value == Q->topRight->value && Q->topRight->value == Q->bottomLeft->value && Q->bottomLeft->value == Q->bottomRight->value){
				Q->value = Q->topRight->value;
				delete Q->topLeft;
				delete Q->topRight;
				delete Q->bottomLeft;
				delete Q->bottomRight;
				Q->topRight = nullptr;
				Q->topLeft = nullptr;
				Q->bottomRight = nullptr;
				Q->bottomLeft = nullptr;

			}
			
			return Q;
		}
	}

	
	
};



class quad_tree
{
public:
	int height;
	quad_node *head;
	quad_tree(){
		height=0;
		head=nullptr;
	}
	quad_tree(int n){
		height = n;
		head=nullptr;
		head = new quad_node(n);
	}
	quad_tree(int n, int b){
		
		height = n;
		head = new quad_node(n, b);

	}

	~quad_tree(){
		height = 0;
		delete head;
		head = nullptr;
	}
	quad_tree(quad_tree const &q){
		head = nullptr;
		delete head;
		quad_node *D = new quad_node(q.head);
		head = D;
		height = q.height;
		
	}

	void set(int x1, int y1, int x2, int y2, int b){
		// if(head == nullptr)return;
		head->set(x1, y1, x2+1, y2+1, b);
	}
	int get(int x1, int y1){
		return head->get(x1, y1);
	}
	void overlap(quad_tree const &q){
		head->overlap(q.head);
	}
	void intersect(quad_tree const &q){
		head->intersect(q.head);

	}
	void complement(){
		head->complement();

	}
	void resize(int m){
		if(m == height)return;
		if(m > height)head->incsize(m-height);
		else{
			head->decsize(height-m);
		}
		height=m;
	}
	void extract(int x1, int y1, int m){
		height = m;
		
		quad_node *q = head->extract(x1, y1, m);
		
		delete head;
		head = q;
	}
	
};


