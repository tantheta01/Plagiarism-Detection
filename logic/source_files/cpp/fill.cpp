/*
    This file is part of the mydraw.

    mydraw is a simple, interactive drawing program written using OpenGL. 
    
    This code base is meant to serve as a starter code for an assignment in a 
    Computer Graphics course.

    Copyright (c) 2018 by Parag Chaudhuri

    mydraw is free software; you can redistribute it and/or modify it under the 
    terms of the MIT License.

    Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/



#include<bits/stdc++.h>
#include "fill.hpp"
#include "canvas.hpp"
namespace mydraw{

	void floodfill_t::Fill(unsigned int xpos, unsigned int ypos,canvas_t* mycanvas){
		
		std::stack <std::pair<int,int>> S;
		float *store = mycanvas->get_store();
		S.push(std::make_pair(xpos,ypos));
		int W=mycanvas->get_width();
		int H=mycanvas->get_height();
		int index=4*ypos*W+4*xpos;
		color_t PrevColor=color_t(store[index],store[index+1],store[index+2],store[index+3]);
		int x,y;
		color_t newColor=mycanvas->get_context()->fill_color;
		while(!S.empty()){
			 std::pair<int,int> current = S.top();
			 S.pop();
			 x=current.first;
			 y=current.second;
			 if(x<0||x>W||y<0||y>H){
			 	continue;
			 }
			 index=4*y*W+4*x;
			 if(store[index]==newColor.r&&store[index+1]==newColor.g&&store[index+2]==newColor.b&&store[index+3]==newColor.a){
			 	continue;
			 }
			 if(store[index]!=PrevColor.r||store[index+1]!=PrevColor.g||store[index+2]!=PrevColor.b||store[index+3]!=PrevColor.a){
			 	continue;
			 }
			 store[index]=newColor.r;
			 store[index+1]=newColor.g;
			 store[index+2]=newColor.b;
			 store[index+3]=newColor.a;
			 S.push(std::make_pair(x+1,y));
			 S.push(std::make_pair(x,y-1));
			 S.push(std::make_pair(x-1,y));
			 S.push(std::make_pair(x,y+1));
		}
	}
}