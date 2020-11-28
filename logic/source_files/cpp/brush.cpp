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

#include "brush.hpp"
#include "canvas.hpp"
#include <iostream>
#include <cmath>

namespace mydraw 
{
	void point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
	{ 	
		if (get_size()==1)
			canvas.set_pixel(pt,canvas.get_context()->brush_color);
	}
	void point_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
	{
		unsigned int x,y;
	 	unsigned int siz = get_size();
	 	// std::cout<<"The size is \n"<<siz<<std::endl;
		for(x=xpos-siz;x<=xpos+siz;x++){
		   	for(y=ypos-siz;y<=ypos+siz;y++){
	   			if((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos)<siz*siz){
	   				canvas->set_pixel(x,y,canvas->get_context()->brush_color);
	   			}
	   		}
	   	}
	}

	void point_brush_t::stroke (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, double k1, double k2, canvas_t *canvas){

		std::cout<<"Uh ohh u called the wrong function lmaao"<<std::endl;
	}


	  
	void eraser_point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
	{
		if (get_size()==1)
			canvas.erase_pixel(pt);
	}


	void eraser_point_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
	{
		unsigned int x,y;
	 	unsigned int siz = get_size();

	   
		for(x=xpos-siz;x<=xpos+siz;x++){
		   	for(y=ypos-siz;y<=ypos+siz;y++){
	   			if((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos)<siz*siz){
	   				canvas->erase_pixel(x,y);
	   			}
	   		}
	   	}
	}


	void eraser_point_brush_t::stroke (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, double  k1, double k2, canvas_t *canvas){

		std::cout<<"Uh ohh u called the wrong function lmaao"<<std::endl;
	}

	void smooth_brush_t::stroke(unsigned int xpos, unsigned int ypos, canvas_t* canvas){

		//We solve a set of Linear equations to get the coefficients of the cubic polynomial
		//The names alpha1 alpha2 etc are given so I understand better, or I wasn't able to contemplate xi's as the constants
		

		canvas->set_pixel(xpos, ypos, canvas->get_context()->brush_color);
		
	}

	void smooth_brush_t::stroke(const point_t &p, canvas_t &canvas){
		canvas.set_pixel(p, canvas.get_context()->brush_color);
	}

	void smooth_brush_t::stroke(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, double k1, double k2, canvas_t *canvas) {
	
		double a=k1*(int)(x2-x1)-(int)(y2-y1);
		double b=-k2*(int)(x2-x1)+(int)(y2-y1);
		

		unsigned int temp;
		if(x1>x2){temp=x1;x1=x2;x2=temp;temp=y1;y1=y2;y2=temp;temp=k1;k1=k2;k2=temp;}
		double yprevpos=0;

		for(unsigned int xpos = x1; xpos<x2; xpos++){
			
			double t=(double)(xpos-x1)/(double)(x2-x1);
			
			double ypos = (1-t)*y1 + t*y2 + t*(1-t)*((1-t)*a +t*b);
		
			unsigned int x,y;
	 		unsigned int siz = get_size();
	 	
			for(x=xpos-siz;x<=xpos+siz;x++){
		   	for(y=ypos-siz;y<=ypos+siz;y++){
	   			if((x-xpos)*(x-xpos)+(y-ypos)*(y-ypos)<siz*siz){
	   				if(y<720){canvas->set_pixel(x,y,canvas->get_context()->brush_color); std::cout<<"LALA"<<std::endl;}
	   			}
	   		

	   		}

	   		if(yprevpos > 1 && abs(ypos - yprevpos > 2)){
	   			// std::cout<<"JJJ"<<std::endl;
	   			for(y=std::min(yprevpos, ypos)+1; y<std::max(yprevpos, ypos)-1; y++){
	   				if(y<720){

	   					canvas->set_pixel(x,y,canvas->get_context()->brush_color);				
	   					// std::cout<<y<<std::endl;
	   					// if(yprevpos > ypos){
	   					// 	if(y < (yprevpos + ypos)/2){
	   					// 		canvas->set_pixel(x,y,canvas->get_context()->brush_color);				
	   					// 	}

	   					// 	else
	   					// 		canvas->set_pixel(x-1,y,canvas->get_context()->brush_color);			
	   						
	   					// }
	   					// else{
	   					// 	if(y < (yprevpos + ypos)/2){
	   					// 		canvas->set_pixel(x,y,canvas->get_context()->brush_color);				
	   					// 	}

	   					// 	else
	   					// 		canvas->set_pixel(x-1,y,canvas->get_context()->brush_color);			
	   					// }
	   					
	   				}
	   			}
	   		}
	   		
	   	}
	   	// std::cout<<"HAHAeee"<<std::endl;
	   	yprevpos=ypos;
			
		}

	}
}
