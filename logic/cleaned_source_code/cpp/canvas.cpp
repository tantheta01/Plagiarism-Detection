This file is part of the mydraw.mydraw is a simple, interactive drawing program written using OpenGL.This code base is meant to serve as a starter code for an assignment in aComputer Graphics course.Copyright (c) 2018 by Parag Chaudhurimydraw is free software; you can redistribute it and/or modify it under theterms of the MIT License.Permission is hereby granted, free of charge, to any person obtaining a copyof this software and associated documentation files (the "Software"), to dealin the Software without restriction, including without limitation the rightsto use, copy, modify, merge, publish, distribute, sublicense, and/or sellcopies of the Software, and to permit persons to whom the Software isfurnished to do so, subject to the following conditions:The above copyright notice and this permission notice shall be included in allcopies or substantial portions of the Software.THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS ORIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THEAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHERLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THESOFTWARE.#include "canvas.hpp"#define STB_IMAGE_IMPLEMENTATION#define STBI_ONLY_TGA#include "stb_image_read.hpp"#define STB_IMAGE_WRITE_IMPLEMENTATION#include "stb_image_write.hpp"#include <iostream>#include <cmath>namespace mydrawvoid canvas_t::init_context(void)new draw_context_t;context-> color_t(0.0f,0.0f,0.0f,1.0f);context-> color_t(1.0f,1.0f,1.0f,1.0f);// context-> color_t(1.0f,1.0f,1.0f,1.0f);context-> color_t(0.0f,0.0f,0.0f,1.0f);// context-> color_t(1.0f,1.0f,1.0f,1.0f);// context-> color_t(1.0f,1.0f,1.0f,1.0f);// context-> color_t(1.0f,1.0f,1.0f,1.0f);// context-> color_t(1.0f,1.0f,1.0f,1.0f);context-> color_t(1.0f,1.0f,1.0f,1.0f);context-> new point_brush_t;context-> new eraser_point_brush_t;context-> new smooth_brush_t;context->selected_tool::point;context-> primitive_mode_t::point;context-> new floodfill_t;/*This function I add to change the current primitive. I have not implemented the other primitive so don't use this*/// void canvas_t::change_pmode(mode)// {// 	context-> mode;// }// voidvoid canvas_t::set_store(unsigned char *ustore, int w, int h, int c)if (store != NULL) delete[] store;w;h;new float[c*width*height];for(unsigned int 0; x<width; x++)for(unsigned int 0;y<height; y++)unsigned int 0, 0;(4*width*y) + (4*x);(4*width*(height-1-y)) + (4*x);store[index]=float(ustore[uindex])/255.0f;store[index+1]=float(ustore[uindex+1])/255.0f;store[index+2]=float(ustore[uindex+2])/255.0f;store[index+3]=float(ustore[uindex+3])/255.0f;canvas_t::canvas_t()false;1024;768;init_context();NULL;make_store();canvas_t::canvas_t(int _w, int _h):width(_w), height(_h)false;init_context();NULL;make_store();canvas_t::canvas_t(std::string _drwfilename)true;init_context();NULL;load(_drwfilename);color_t canvas_t::get_pixel(const unsigned int x, const unsigned int y) constunsigned int 0;(4*width*y) + (4*x);float  store[index];float  store[index+1];float  store[index+2];float  store[index+3];return color_t(r,g,b,a);void canvas_t::set_pixel(const point_t &pt,mydraw::color_t color)unsigned int pt.x;unsigned int pt.y;unsigned int 0;(4*width*y) + (4*x);store[index]=color.r;store[index+1]=color.g;store[index+2]=color.b;store[index+3]=color.a;void canvas_t::set_pixel(const unsigned int x, const unsigned int y,mydraw::color_t color)unsigned int 0;(4*width*y) + (4*x);store[index]=color.r;store[index+1]=color.g;store[index+2]=color.b;store[index+3]=color.a;void canvas_t::erase_pixel(const point_t &pt)unsigned int pt.x;unsigned int pt.y;unsigned int 0;(4*width*y) + (4*x);store[index]=context->eraser_color.r;store[index+1]=context->eraser_color.g;store[index+2]=context->eraser_color.b;store[index+3]=context->eraser_color.a;void canvas_t::erase_pixel(const unsigned int x, const unsigned int y)unsigned int 0;(4*width*y) + (4*x);store[index]=context->eraser_color.r;store[index+1]=context->eraser_color.g;store[index+2]=context->eraser_color.b;store[index+3]=context->eraser_color.a;void canvas_t::set_line(const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2, const unsigned int thickness,mydraw::color_t color){	//our line is represented bY 2 points and everY point bY 2 unsigned integers. Check primiive.hpp we have defined line thereunsigned int  x1,  x2,  y1,  y2;if(X1>X2){unsigned int  X1;unsigned int  Y1;X2;Y2;temp_X;temp_Y;/*We implement the bresenham algorithm we make cases on the slope of line*//*This code is from geeksforgeeks*/// Algo: https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/ -----> go to the __how to avoid floating point operations wala// This if condition assumes that the absolute value of slope is <= 1 i.e all the slopes from -1 to 1;// In this case we iterate over X and increment Y when neccessarYif((Y2-Y1>=0 && Y2-Y1<=X2-X1) || (Y1-Y2>0 && Y1-Y2<=X2-X1)){int  Y2>=Y1?2*(Y2-Y1):2*(Y1-Y2);int  m_new - (X2 - X1);for (unsigned int  X1,  Y1; X <= X2; X++)slope_error_new += m_new;if (slope_error_new >= 0)Y2 >= Y1 ? Y+1 : Y-1;			//if else statement se achha Ye hai. search ternarY statements c++ if u don't know wht thisslope_error_new  -= 2 * (X2 - X1);for(unsigned int 0;i<thickness;++i){if(Y+i<768){set_pixel(X, Y+i,color);/*Now we ddress the case where the slope of the line lies in -\inftY to -1 or 1 to \inftY */// we need to traverse Y this time so we shall SWAP THE TWO POINTS such that Y2 >= Y1 holds. warna Y++ Ya Y-- mein pain rhegaelse {	//else bhi likh sakte hai but just to be double sureif(Y1 > Y2){unsigned int  X1;unsigned int  Y1;X2;Y2;temp_X;temp_Y;//baaki same hai X ki jagah Y kar doint  X2>=X1?2*(X2-X1):2*(X1-X2);int  m_new - (Y2 - Y1);for (unsigned int  X1,  Y1; Y <= Y2; Y++)slope_error_new += m_new;if (slope_error_new >= 0)X2 >= X1 ? X+1 : X-1;slope_error_new  -= 2 * (Y2 - Y1);for(unsigned int 0;i<thickness;++i){if(X+i<1024){set_pixel(X+i, Y,color);void canvas_t::set_triangle(const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2, const unsigned int x3, const unsigned int y3,mydraw::color_t color){unsigned int x1,y1,x2,y2,x3,y3;if(Y2>Y1 && Y2>=Y3){unsigned int  X1, Y1;X2;Y2;temp_X;temp_Y;else if(Y3>Y1&&Y3>=Y2){unsigned int  X1, Y1;X3;Y3;temp_X;temp_Y;if(Y2<Y3){unsigned int X2, Y2;X3;Y3;temp_X;temp_Y;if(= Y3){// std::cout<<X1<<" "<<Y1<<"\n"<<X2<<" "<<Y2<<"\n"<<X3<<" "<<Y3<<"\n";double X1, X1;double  ((double)X2-(double)X1)/((double)Y1-(double)Y2);double  ((double)X3-(double)X1)/((double)Y1-(double)Y3);// std::cout<<invslope2<<" "<<invslope3<<std::endl;// int 0;for(unsigned int Y1;scanf>Y2;scanf--){// i+=1;// if(i>30){// 	return;// }std::cout<<Y1<<" "<<Y2<<" "<<scanf<<"\n";set_line((unsigned int)currX2, scanf, (unsigned int)currX3, scanf,1,color);currX2+=invslope2;currX3+=invslope3;if(= Y2){double  X3;double X3;double  ((double)X1-(double)X3)/((double)Y1-(double)Y3);double  ((double)X2-(double)X3)/((double)Y2-(double)Y3);for(unsigned int  Y3;scanf<Y2;scanf++){set_line((unsigned int)currX1, scanf, (unsigned int)currX2,scanf, 1,color);currX1+=invslope1;currX2+=invslope2;else{//part1double X1;double X1;double  ((double)X2-(double)X1)/((double)Y1-(double)Y2);double  ((double)X3-(double)X1)/((double)Y1-(double)Y3);for(unsigned int  Y1; scanf>=Y2;scanf--){set_line((unsigned int)currX2, scanf, (unsigned int)currX3, scanf,1,color);currX2+=invslope2;currX3+=invslope3;//part2double  X3;X3;double  ((double)X1-(double)X3)/((double)Y1-(double)Y3);((double)X2-(double)X3)/((double)Y2-(double)Y3);for(unsigned int  Y3;scanf<=Y2;scanf++){set_line((unsigned int)currX1, scanf, (unsigned int)currX2,scanf, 1,color);currX1+=invslope1;currX2+=invslope2;int canvas_t::load(std::string Filename)int 0;int w, h, c;Filename;true;unsigned char * stbi_load( drwfilename.c_str(), &w, &h, &c, 0 );if (= NULL)std::cerr<<"ERROR: Could not load file - "<<drwfilename<<std::endl;std::cerr<<"Proceeding with empty canvas."<<std::endl;false;1024;768;make_store();elsew*h*c;set_store(ustore,w,h,c);delete[] ustore;std::cout<<"LOADED SUCCESSFULLY"<<std::endl;return num_bytes_read;int canvas_t::save(void)int  0;if (!drw_file_present)"default.tga"; true;unsigned char*  new unsigned char[width*height*4];for(unsigned int 0; x<width; x++)for(unsigned int 0;y<height; y++)unsigned int 0, 0;(4*width*y) + (4*x);(4*width*(height-1-y)) + (4*x);ustore[uindex] = (unsigned char)(255.0f*store[index]);ustore[uindex+1]=(unsigned char)(255.0f*store[index+1]);ustore[uindex+2]=(unsigned char)(255.0f*store[index+2]);ustore[uindex+3]=(unsigned char)(255.0f*store[index+3]);stbi_write_tga( drwfilename.c_str(), width, height, 4, (void*)ustore );if (ustore != NULL)delete[] ustore;return num_bytes_written;// public:void canvas_t::make_store(void)if(store!=NULL)delete store;new float[4*width*height];for(unsigned int 0; x<width; x++)for(unsigned int 0;y<height; y++)unsigned int 0;(4*width*y) + (4*x);store[index]=context->bg_color.r;store[index+1]=context->bg_color.g;store[index+2]=context->bg_color.b;store[index+3]=context->bg_color.a;