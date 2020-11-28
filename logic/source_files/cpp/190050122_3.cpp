#include<bits/stdc++.h>

class quad_node
{
	

public:

	bool value;
	int size, begx, begy;
	quad_node *up;
	quad_node *down;
	quad_node *left;
	quad_node *right;


	quad_node(int s, int bx, int by){
		value=0;
		this->size = s;
		this->begx = bx;
		this->begy = by;
		up=NULL;
		down=NULL;
		left=NULL;
		right=NULL;
	}



	~quad_node(){
		if (up != NULL)
		{
			delete up;
			delete down;
			delete left;
			delete right;
		}
	}

	quad_node(quad_node *nhead){
		this->value = nhead->value;
		int bx, by;
		// bx = ;--
		// by = ;
		this->size = nhead->size;
		this->begx = nhead->begx;
		this->begy = nhead->begy;
		if(up!=NULL){
			up = new quad_node(nhead->up);
			down = new quad_node(nhead->down);
			left = new quad_node(nhead->left);
			right = new quad_node(nhead->right);
		}

	}

	void set(int x1, int y1, int x2, int y2, bool val){
		int endx = this->begx + (1<<this->size);
		int endy = this->begy + (1<<this->size);
		if(x1 <= this->begx && x2 >= endx-1 &&  y1 <= this->begy && y2 >= endy-1){
			this->value = val;
			delete up;
			delete down;
			delete left;
			delete right;
		}
		else if(this->begx > x2 || endx <= x1 || this->begy > y2 || endy <= y1){
			return;
		}
		else
		{
			quad_node *u1 = new quad_node(this->size-1, this->begx, this->begy);
			quad_node *d1 = new quad_node(this->size-1, this->begx + (1<<(this->size-1)), this->begy);
			quad_node *l1 = new quad_node(this->size-1, this->begx, this->begy + (1<<(this->size-1)));
			quad_node *r1 = new quad_node(this->size-1, this->begx + (1<<(this->size-1)), this->begy + (1<<(this->size-1)));
			u1->set(x1, y1, x2, y2, val);
			d1->set(x1, y1, x2, y2, val);
			l1->set(x1, y1, x2, y2, val);
			r1->set(x1, y1, x2, y2, val);
			up = u1;
			down = d1;
			right = r1;
			left = l1;

		}
	}

	bool get(int x1, int y1){
		if(this->up == NULL){
			return this->value;

		}
		else{
			if(x1 < this->begx + (1<<(size-1)) && y1 < this->begy + (1<<(this->size-1)))return up->get(x1, y1);
			else if(x1 < this->begx + (1<<(size-1))){
				return left->get(x1, y1);
			}
			else if(y1 < this->begy + (1<<(this->size-1))){
				return down->get(x1, y1);
			}
			else{
				return right->get(x1, y1);
			}

		}
	}

	void overlap(quad_node *Q){
		if(this->up == NULL && Q->up == NULL){
			this->value = this->value | Q->value;
		}
		else if(this->up == NULL){

			if(this->value==0){
				quad_node *u1 = new quad_node(this->size-1, this->begx, this->begy);
				quad_node *d1 = new quad_node(this->size-1, this->begx + (1<<(this->size-1)), this->begy);
				quad_node *l1 = new quad_node(this->size-1, this->begx, this->begy + (1<<(this->size-1)));
				quad_node *r1 = new quad_node(this->size-1, this->begx + (1<<(this->size-1)), this->begy + (1<<(this->size-1)));
				u1->overlap(Q->up);
				d1->overlap(Q->down);
				l1->overlap(Q->left);
				r1->overlap(Q->right);
				this->up = u1, this->down = d1, this->right = r1, this->left = l1;
			}
			else return;
			
		}
		else if(Q->up == NULL){
			if(Q->value == 1){
				this->value=1;
				delete this->up;
				delete this->down;
				delete this->left;
				delete this->right;
				return;
			}
			else{
				return;
			}

		}

		else{
			this->up->overlap(Q->up);
			this->down->overlap(Q->down);
			this->left->overlap(Q->left);
			this->right->overlap(Q->right);
		}

	}

	void intersection(quad_node *Q)
	{
		if(this->up == NULL && Q->up == NULL){
			this->value = this->value & Q->value;
			return;
		}
		else if(this->up == NULL){

			if(this->value==1){
				quad_node *u1 = new quad_node(this->size-1, this->begx, this->begy);
				quad_node *d1 = new quad_node(this->size-1, this->begx + (1<<(this->size-1)), this->begy);
				quad_node *l1 = new quad_node(this->size-1, this->begx, this->begy + (1<<(this->size-1)));
				quad_node *r1 = new quad_node(this->size-1, this->begx + (1<<(this->size-1)), this->begy + (1<<(this->size-1)));
				u1->overlap(Q->up);
				d1->overlap(Q->down);
				l1->overlap(Q->left);
				r1->overlap(Q->right);
				this->up = u1, this->down = d1, this->right = r1, this->left = l1;
			}
			else return;
			
		}
		else if(Q->up == NULL){
			if(Q->value == 0){
				this->value=0;
				delete this->up;
				delete this->down;
				delete this->left;
				delete this->right;
				return;
			}
			else{
				return;
			}

		}

		else{
			this->up->overlap(Q->up);
			this->down->overlap(Q->down);
			this->left->overlap(Q->left);
			this->right->overlap(Q->right);
		}		
	}

	void complement(){
		if (this->up == NULL)
		{
			this->value = this->value^1;
		}
		else{
			this->down->complement();
			this->up->complement();
			this->left->complement();
			this->right->complement();
		}
	}

	void incsize(int inc){
		this->size = this->size+inc;
		this->up->incsize(inc);
		this->down->incsize(inc);
		this->left->incsize(inc);
		this->right->incsize(inc);
	}

	int decsize(int dec){
		if(size > dec){
			if(this->up == NULL){
				this->size -= dec;
				return;
			}
			else{
				this->up->decsize(dec);
				this->down->decsize(dec);
				this->left->decsize(dec);
				this->right->decsize(dec);
				if (up->value== down->value && up->value == left->value && up->value == right->value)	
				{
					this->value = this->up->value;
					delete up;
					delete down;
					delete left;
					delete right;
				}
				this->size -= dec;
				return;
			}

		}

		else if(size == dec){
			if(this->up == NULL){
				size=0;
			}
			else{
				size=0;
				long long ans = up->decsize(dec) + down->decsize(dec) + left->decsize(dec) + right->decsize(dec);
				if(ans < (1<<(size-1))){
					this->value=0;
					delete up;
					delete down;
					delete left;
					delete right;

				}
				else{
					this->value=1;
					delete up;
					delete down;
					delete left;
					delete right;					
				}
			}
		}
		else{
			if(this->up==NULL){
				return (1<<this->size);
			}
			else{
				return up->decsize(dec) + down->decsize(dec) + right->decsize(dec) + left->decsize(dec);
			}
		}

	}


	quad_node *resize(int x1, int y1, int m){
		if(this->up == NULL){
			
		}
	}






	
};


class quad_tree
{
	quad_node *head;
	int size;
public:

	quad_tree(int n){
		head = new quad_node(n, 0, 0);
		size=n;
	}

	int getsize()
	{
		return this->size;
	}

	quad_node *getroot(){
		return head;
	}


	quad_tree(const quad_tree &Q){
		delete head;
		this->size = Q.getsize();
		quad_tree *nhead = Q.getroot();




	}

	void set(int x1, int y1, int x2, int y2, int b){

	}

	~quad_tree();
	
};


