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

#include "gl_framework.hpp"

#include <iostream>
#include <string>
int firstX = -1, firstY = -1;
int secX = -1, secY=-1;

std::vector<double> Xs, Ys;
std::vector<double>Ks;

namespace csX75

{
  //! Initialize GL State
  void init_gl(mydraw::canvas_t* mycanvas)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    
    //Enable depth testing
    glDisable(GL_DEPTH_TEST);

    GLuint tex;
    glGenTextures( 1, &tex);
    
    glBindTexture( GL_TEXTURE_2D, tex );
    mycanvas->set_canvas_texture(tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mycanvas->get_width(), mycanvas->get_height(), 0, GL_RGBA, GL_FLOAT, mycanvas->get_store());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    // Load shaders and use the resulting shader program
    std::string vertex_shader_file("shaders/vshader.glsl");
    std::string fragment_shader_file("shaders/fshader.glsl");

    std::vector<GLuint> shader_list;
    shader_list.push_back(csX75::load_shader(GL_VERTEX_SHADER, vertex_shader_file));
    shader_list.push_back(csX75::load_shader(GL_FRAGMENT_SHADER, fragment_shader_file));

    GLuint shaderProgram = csX75::create_program(shader_list);
    glUseProgram( shaderProgram );
    mycanvas->set_canvas_sp(shaderProgram);

    glUniform1i(glGetUniformLocation(shaderProgram, "screen_texture"), 0);

    //! Vertex attributes for a quad that fills the entire screen in normalized device coordinates.
    float screen_quad_vertices[] = 
     { 
          // positions   // texCoords
          -1.0f,  1.0f,  0.0f, 1.0f,
          -1.0f, -1.0f,  0.0f, 0.0f,
           1.0f, -1.0f,  1.0f, 0.0f,

          -1.0f,  1.0f,  0.0f, 1.0f,
           1.0f, -1.0f,  1.0f, 0.0f,
           1.0f,  1.0f,  1.0f, 1.0f
      };

    unsigned int screen_quad_vao, screen_quad_vbo;  

    glGenVertexArrays(1, &screen_quad_vao);
    glGenBuffers(1, &screen_quad_vbo);
    glBindVertexArray(screen_quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, screen_quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen_quad_vertices), &screen_quad_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    mycanvas->set_canvas_vao(screen_quad_vao);
    
    
    
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    mydraw::canvas_t* mycanvas = reinterpret_cast<mydraw::canvas_t*>(glfwGetWindowUserPointer(window));

    //!Close the window if the ESC key was pressed
    //!Save to a .tga file if the 'S' key was pressed. Can you figure out the code that saves the drawing to a .tga file?
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
      mycanvas->save();
      std::cerr<<"Saving canvas."<<std::endl;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
      std::string Filename;
      std::cout<<"Enter Filename and press ENTER: ";
      std::cin>>Filename;
      if (Filename == ""){
        std::cout<<"Empty Filename given!!"<<std::endl;
      }
      else
      {
        mycanvas->load(Filename);
      }
    }
    else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS){
      if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::point){
        if(mycanvas->get_context()->choice == mydraw::selected_tool::point || mycanvas->get_context()->choice == mydraw::selected_tool::smooth){
          int curr_siz=mycanvas->get_context()->current_brush->get_size();
          if(curr_siz<10){
            mycanvas->get_context()->current_brush->set_size(curr_siz+2);
            mycanvas->get_context()->current_smooth_brush->set_size(curr_siz+2);
          }
          else{
            std::cout<<"Sizes greater than 5 not allowed"<<std::endl;
          }
        }
        else if(mycanvas->get_context()->choice== mydraw::selected_tool::eraser){
          int curr_siz=mycanvas->get_context()->current_eraser->get_size();
          if(curr_siz<10){
            mycanvas->get_context()->current_eraser->set_size(curr_siz+2);
          }
          else{
            std::cout<<"Sizes greater than 5 not allowed"<<std::endl;
          }
        
        }
        
      }

    }
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS){
      if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::point || mycanvas->get_context()->choice == mydraw::selected_tool::smooth ){
         if(mycanvas->get_context()->choice == mydraw::selected_tool::point){
          int curr_siz=mycanvas->get_context()->current_brush->get_size();
          if(curr_siz>2){
            mycanvas->get_context()->current_brush->set_size(curr_siz-2);
            mycanvas->get_context()->current_smooth_brush->set_size(curr_siz-2);
          }
          else{
            std::cout<<"Sizes less than 1 not allowed"<<std::endl;
          }
        }
        else if(mycanvas->get_context()->choice == mydraw::selected_tool::eraser){
          int curr_siz=mycanvas->get_context()->current_eraser->get_size();
          if(curr_siz>2){
            mycanvas->get_context()->current_eraser->set_size(curr_siz-2);
          }
          else{
            std::cout<<"Sizes less than 1 not allowed"<<std::endl;
          }
        
        }
        
      }
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS){
        float r,g,b,a;
        std::cout<<"Enter the color in RGBA format";
        std::cin>>r>>g>>b>>a;
        std::cout<<r<<" "<<g<<" "<<b<<" "<<a<<"\n";
        if(r>1||g>1||b>1||a>1||r<0||g<0||b<0||a<0){std::cout<<"invalid input, all channel values must lie between O to 1";}

        else{
          mycanvas->get_context()->brush_color= mydraw::color_t(r,g,b,a);
        }

        
        

    }

    else if(key == GLFW_KEY_D){

      float r,g,b,a;
      std::cout<<"Enter the color in RGBA format";
      std::cin>>r>>g>>b>>a;
      std::cout<<r<<" "<<g<<" "<<b<<" "<<a<<"\n";
      if(r>1||g>1||b>1||a>1||r<0||g<0||b<0||a<0){std::cout<<"invalid input, all channel values must lie between O to 1";}

      else      
        mycanvas->get_context()->eraser_color=mydraw::color_t(r,g,b,a);
    }

    else if(key == GLFW_KEY_R){
      mycanvas->make_store();
    }

    else if(key == GLFW_KEY_K){

      float r,g,b,a;
      std::cout<<"Enter the color in RGBA format";
      std::cin>>r>>g>>b>>a;
      std::cout<<r<<" "<<g<<" "<<b<<" "<<a<<"\n";
      if(r>1||g>1||b>1||a>1||r<0||g<0||b<0||a<0){std::cout<<"invalid input, all channel values must lie between O to 1";}

      else{
        mycanvas->get_context()->bg_color = mydraw::color_t(r,g,b,a);
      }

    }






    else if (key == GLFW_KEY_E && action == GLFW_PRESS) mycanvas->get_context()->choice = mydraw::selected_tool::eraser;
    else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      mycanvas->get_context()->choice = mydraw::selected_tool::point;
      // mycanvas->get_context()->choice = mydraw::selected_tool::smooth;  
      // delete mycanvas->get_context()->current_brush;
      // mycanvas->get_context()->current_brush = new point_brush_t;

    }
    else if (key == GLFW_KEY_B && action == GLFW_PRESS) { 
      // mycanvas->get_context()->current_pmode=mydraw::primitive_mode_t::point; 
      mycanvas->get_context()->choice = mydraw::selected_tool::smooth; 
      mycanvas->get_context()->current_pmode = mydraw::primitive_mode_t::point;
      // delete mycanvas->get_context()->current_brush;
      // mycanvas->get_context()->current_brush=new smooth_brush_t;
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS){

      if(mycanvas->get_context()->choice == mydraw::selected_tool::point || mycanvas->get_context()->choice == mydraw::selected_tool::smooth){
        mycanvas->get_context()->fill_color=mycanvas->get_context()->brush_color;

      }
      else if(mycanvas->get_context()->choice == mydraw::selected_tool::eraser){

        mycanvas->get_context()->fill_color = mycanvas->get_context()->eraser_color;
      }

      mycanvas->get_context()->choice = mydraw::selected_tool::fill;


    } 
      


    else if ((key == GLFW_KEY_1||key == GLFW_KEY_KP_1) && action == GLFW_PRESS)  {mycanvas->get_context()->current_pmode = mydraw::primitive_mode_t::point; std::cout<<"Primitive mode point actiated!\n";}
    else if ((key == GLFW_KEY_2||key == GLFW_KEY_KP_2)  && action == GLFW_PRESS) {mycanvas->get_context()->current_pmode = mydraw::primitive_mode_t::line; std::cout<<"Primitive mode line actiated!\n";}
    else if ((key == GLFW_KEY_3||key == GLFW_KEY_KP_3)  && action == GLFW_PRESS) {mycanvas->get_context()->current_pmode = mydraw::primitive_mode_t::line_strip; std::cout<<"Primitive mode line strip actiated!\n";}
    else if ((key == GLFW_KEY_4||key == GLFW_KEY_KP_4)  && action == GLFW_PRESS) {mycanvas->get_context()->current_pmode = mydraw::primitive_mode_t::triangle; std::cout<<"Primitive mode triangle actiated!\n";}
    else if ((key == GLFW_KEY_5||key == GLFW_KEY_KP_5)  && action == GLFW_PRESS) {mycanvas->get_context()->current_pmode = mydraw::primitive_mode_t::triangle_strip; std::cout<<"Primitive mode triangle_strip actiated!\n";}
    firstX=-1;
    firstY=-1;
    secX=-1;
    secY=-1;
  }  

 void mouseDragCallback(GLFWwindow* window, double xpos, double ypos)
    {

    mydraw::canvas_t* mycanvas = reinterpret_cast<mydraw::canvas_t*>(glfwGetWindowUserPointer(window));
    unsigned int h = mycanvas->get_height();
    unsigned int w = mycanvas->get_width();

    ypos=h-ypos;
    if(mycanvas->get_context()->choice == mydraw::selected_tool::point){
    if(0<=xpos && xpos<=w && 0<=ypos && ypos<=h)
    mycanvas->get_context()->current_brush->stroke((unsigned int)xpos, (unsigned int)ypos, mycanvas);
    }
    if(mycanvas->get_context()->choice == mydraw::selected_tool::eraser){
    if(0<=xpos && xpos<=w && 0<=ypos && ypos<=h)
    mycanvas->get_context()->current_eraser->stroke((unsigned int)xpos, (unsigned int)ypos, mycanvas);
    }

  }

  void smooth_callback(GLFWwindow* window, double xpos, double ypos)
  {
    mydraw::canvas_t* mycanvas = reinterpret_cast<mydraw::canvas_t*>(glfwGetWindowUserPointer(window));
    unsigned int h = mycanvas->get_height();
    // unsigned int w = mycanvas->get_width();

    ypos=h-ypos;
    Xs.push_back((unsigned int)xpos);
    Ys.push_back((unsigned int)ypos);
  }

  //!GLFW mouse callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    mydraw::canvas_t* mycanvas = reinterpret_cast<mydraw::canvas_t*>(glfwGetWindowUserPointer(window));
    

    if(mycanvas->get_context()->choice == mydraw::selected_tool::eraser)  {

      if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::point){

        switch(button)
        {
          //Note: This only plots a point when the mouse is clicked. Repeated points need repeated clicks which may be cumbersome.
          //A better solution is to implement the point brush using a click and drag method - figure out how to implement click and draw in GLFW.


          case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS)
            {
              ypos=mycanvas->get_height()-ypos;
              mycanvas->get_context()->current_eraser->stroke((unsigned int)xpos, (unsigned int)ypos, mycanvas);
              glfwSetCursorPosCallback(window, mouseDragCallback);
            }
            else{
              glfwSetCursorPosCallback(window, NULL );
            }
            break;
          default:
        
            std::cout<<"VALLLEDD\n";
            break;
        
       }

      }


      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::line){

        switch(button){


          case GLFW_MOUSE_BUTTON_LEFT:


            if(action == GLFW_PRESS){

              
              ypos=mycanvas->get_height()-ypos;
              //std::cout<<xpos<<" "<<ypos<<std::endl;
              //std::cout<<firstX; default value of firstX seems -1
              if(firstX == -1){
                
                firstX = (unsigned int)xpos;
                firstY = (unsigned int)ypos;
                return;
              }

              else{


                mycanvas->set_line(firstX, firstY, (int)xpos, (int)ypos, mycanvas->get_context()->current_eraser->get_size(),mycanvas->get_context()->eraser_color);
                 firstX = (unsigned int)xpos;
                 firstY = (unsigned int)ypos;

                firstX = -1;
                firstY=-1;
                return;
              }

            }
        }        

      }

      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::line_strip){


        switch(button){


          case GLFW_MOUSE_BUTTON_LEFT:


            if(action == GLFW_PRESS){

              
              ypos=mycanvas->get_height()-ypos;
              //std::cout<<xpos<<" "<<ypos<<std::endl;
              if(firstX == -1){
                //std::cout<<"HAHA";
                firstX = (unsigned int)xpos;
                firstY = (unsigned int)ypos;
                return;
              }

              else{

                mycanvas->set_line(firstX, firstY, (int)xpos, (int)ypos, mycanvas->get_context()->current_eraser->get_size(),mycanvas->get_context()->eraser_color);
                firstX = (unsigned int)xpos;
                firstY = (unsigned int)ypos;
                return;
              }

            }
        }
      }

      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::triangle){

        switch(button){

          case GLFW_MOUSE_BUTTON_LEFT:
            if(action == GLFW_PRESS){
              ypos=mycanvas->get_height()-ypos;
              if(firstX == -1){
                firstX=xpos;
                firstY = ypos;

              }
              else if(secX == -1){
                secX=xpos;
                secY = ypos;
              }
              else{
                mycanvas->set_triangle((unsigned int)xpos, (unsigned int)ypos, (unsigned int)firstX, (unsigned int)firstY, (unsigned int)secX, (unsigned int)secY,mycanvas->get_context()->eraser_color);
                firstX=-1;
                secX=-1;

              }

            }
        }
          
          // return;
      }

      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::triangle_strip){

        switch(button){

          case GLFW_MOUSE_BUTTON_LEFT:
            if(action == GLFW_PRESS){
              ypos=mycanvas->get_height()-ypos;
              if(firstX == -1){
                firstX=xpos;
                firstY = ypos;

              }
              else if(secX == -1){
                secX=xpos;
                secY = ypos;
              }
              else{
                mycanvas->set_triangle((unsigned int)xpos, (unsigned int)ypos, (unsigned int)firstX, (unsigned int)firstY, (unsigned int)secX, (unsigned int)secY,mycanvas->get_context()->eraser_color);
                firstX=secX;
                firstY=secY;
                secX=(unsigned int)xpos;
                secY = (unsigned int)ypos;

              }

            }
        }
          
          // return;
      }

        
    }
    else if(mycanvas->get_context()->choice == mydraw::selected_tool::fill)  {
        switch(button)
        {
          //Note: This only plots a point when the mouse is clicked. Repeated points need repeated clicks which may be cumbersome.
          //A better solution is to implement the point brush using a click and drag method - figure out how to implement click and draw in GLFW.
          case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS)
            {
              ypos=mycanvas->get_height()-ypos;
              mycanvas->get_context()->current_fill->Fill((unsigned int)xpos,(unsigned int) ypos,mycanvas);
              //std::cout<<xpos<<" "<<ypos<<"\n";
            }
            break;
          default:
        
            std::cout<<"VALLLEDD\n";
            break;
        
      }
    }

    else{


      if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::point){
        std::cout<<"HAHA"<<std::endl;

        if(mycanvas->get_context()->choice == mydraw::selected_tool::point)  {
          switch(button)
          {
            //Note: This only plots a point when the mouse is clicked. Repeated points need repeated clicks which may be cumbersome.
            //A better solution is to implement the point brush using a click and drag method - figure out how to implement click and draw in GLFW.
            case GLFW_MOUSE_BUTTON_LEFT:
              if (action == GLFW_PRESS)
              {
                ypos=mycanvas->get_height()-ypos;
                mycanvas->get_context()->current_brush->stroke((unsigned int)xpos, (unsigned int)ypos, mycanvas);
                //std::cout<<xpos<<" "<<ypos<<"\n";
                glfwSetCursorPosCallback(window, mouseDragCallback);
              }
              else{
                glfwSetCursorPosCallback(window, NULL );
              }
              break;
            default:
          
              std::cout<<"VALLLEDD\n";
              break;
          
          }
        }

        else if(mycanvas->get_context()->choice == mydraw::selected_tool::smooth){

          switch(button)  {

            case GLFW_MOUSE_BUTTON_LEFT:
              if(action == GLFW_PRESS){
                ypos = mycanvas->get_height() - ypos;

                glfwSetCursorPosCallback(window, smooth_callback);
                Xs.push_back(xpos);
                Ys.push_back(ypos);
              }
             
              else{
                std::vector<double> Xnew,Ynew;
                for(int i=0;i<int(Xs.size());i++){
                  if(i%30==0) {Xnew.push_back(Xs[i]);Ynew.push_back(Ys[i]);}
                }
                if(Xnew.size()<2){
                  Xs.clear();
                  Ys.clear();
                  Xnew.clear();
                  Ynew.clear();
                  return;
                }
                for(auto it=Xnew.begin()+1;it!=Xnew.end()-1;){
                  if(*it==*(it+1)||*(it)==*(it-1)){
                    Xnew.erase(it);
                    Ynew.erase(Ynew.begin()+(it-Xnew.begin()));
                  }
                  else{it++;}
                }
                int n = Xnew.size();
                std::cout<<n<<std::endl;
                if(n<2){
                  Xnew.clear();
                  Ynew.clear();
                  return;
                }
                Ks.push_back((Ynew[1]-Ynew[0])/(Xnew[1]-Xnew[0]));
               
                for(int i=1;i<n-1;i++){
                  Ks.push_back(0.5*(((Ynew[i+1]-Ynew[i])/(Xnew[i+1]-Xnew[i]))+((Ynew[i-1]-Ynew[i])/(Xnew[i-1]-Xnew[i]))));
                }
                Ks.push_back((Ynew[n-1]-Ynew[n-2])/(Xnew[n-1]-Xnew[n-2]));
                for(int i=0;i<n-1;i++)
                  mycanvas->get_context()->current_smooth_brush->stroke(Xnew[i], Ynew[i], Xnew[i+1], Ynew[i+1], Ks[i],Ks[i+1], mycanvas);
                Xs.clear();
                Ys.clear();
                Ks.clear();
                Xnew.clear();
                Ynew.clear();
                glfwSetCursorPosCallback(window, NULL);
              }
          }
        }
      }

      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::line){

        switch(button){


          case GLFW_MOUSE_BUTTON_LEFT:


            if(action == GLFW_PRESS){

              
              ypos=mycanvas->get_height()-ypos;
              //std::cout<<xpos<<" "<<ypos<<std::endl;
              //std::cout<<firstX; default value of firstX seems -1
              if(firstX == -1){
                
                firstX = (unsigned int)xpos;
                firstY = (unsigned int)ypos;
                return;
              }

              else{


                mycanvas->set_line(firstX, firstY, (int)xpos, (int)ypos, mycanvas->get_context()->current_brush->get_size(),mycanvas->get_context()->brush_color);
                 firstX = (unsigned int)xpos;
                 firstY = (unsigned int)ypos;

                firstX = -1;
                firstY=-1;
                return;
              }

            }
        }
      }

      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::line_strip){


        switch(button){


          case GLFW_MOUSE_BUTTON_LEFT:


            if(action == GLFW_PRESS){

              
              ypos=mycanvas->get_height()-ypos;
              //std::cout<<xpos<<" "<<ypos<<std::endl;
              if(firstX == -1){
                //std::cout<<"HAHA";
                firstX = (unsigned int)xpos;
                firstY = (unsigned int)ypos;
                return;
              }

              else{

                mycanvas->set_line(firstX, firstY, (int)xpos, (int)ypos, mycanvas->get_context()->current_brush->get_size(),mycanvas->get_context()->brush_color);
                firstX = (unsigned int)xpos;
                firstY = (unsigned int)ypos;
                return;
              }

            }
        }
      }

      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::triangle){

        switch(button){

          case GLFW_MOUSE_BUTTON_LEFT:
            if(action == GLFW_PRESS){
              ypos=mycanvas->get_height()-ypos;
              if(firstX == -1){
                firstX=xpos;
                firstY = ypos;

              }
              else if(secX == -1){
                secX=xpos;
                secY = ypos;
              }
              else{
                mycanvas->set_triangle((unsigned int)xpos, (unsigned int)ypos, (unsigned int)firstX, (unsigned int)firstY, (unsigned int)secX, (unsigned int)secY,mycanvas->get_context()->brush_color);
                firstX=-1;
                secX=-1;

              }

            }
        }
          
          // return;
      }


      else if(mycanvas->get_context()->current_pmode == mydraw::primitive_mode_t::triangle_strip){

        switch(button){

          case GLFW_MOUSE_BUTTON_LEFT:
            if(action == GLFW_PRESS){
              ypos=mycanvas->get_height()-ypos;
              if(firstX == -1){
                firstX=xpos;
                firstY = ypos;

              }
              else if(secX == -1){
                secX=xpos;
                secY = ypos;
              }
              else{
                mycanvas->set_triangle((unsigned int)xpos, (unsigned int)ypos, (unsigned int)firstX, (unsigned int)firstY, (unsigned int)secX, (unsigned int)secY,mycanvas->get_context()->brush_color);
                firstX=secX;
                firstY=secY;
                secX=(unsigned int)xpos;
                secY = (unsigned int)ypos;

              }

            }
        }
          
          // return;
      }


    }


    

    
  }
  
  void display_callback(mydraw::canvas_t* mycanvas)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram( mycanvas->get_canvas_sp() );

    glBindVertexArray(mycanvas->get_canvas_vao());

    glBindTexture(GL_TEXTURE_2D, mycanvas->get_canvas_texture());

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mycanvas->get_width(), mycanvas->get_height(), GL_RGBA, GL_FLOAT, mycanvas->get_store());

    

    glDrawArrays(GL_TRIANGLES, 0, 6);

  }

  int render_gl(int argc, char** argv, mydraw::canvas_t* mycanvas)
  {
    //! The pointer to the GLFW window
    GLFWwindow* window;

    //! Setting up the GLFW Error callback
    glfwSetErrorCallback(csX75::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
      return -1;

    //We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    //We don't want the old OpenGL 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    //! Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(mycanvas->get_width(), mycanvas->get_height(), "MyDraw Canvas", NULL, NULL);
    if (!window)
      {
        glfwTerminate();
        return -1;
      }
    
    //! Make the window's context current 
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    //Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
      {
        //Problem: glewInit failed, something is seriously wrong.
        std::cerr<<"GLEW Init Failed : %s"<<std::endl;
      }

    //Print and see what context got enabled
    std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
    std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
    std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
    std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl<<std::endl;

    //Keyboard Callback
    glfwSetKeyCallback(window, key_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetWindowUserPointer(window, (void *)mycanvas);
    //Initialize GL state
    init_gl(mycanvas);
    //initBuffersGL();

    // Loop until the user closes the window
    while (glfwWindowShouldClose(window) == 0)
      {
         
        // Render here
        display_callback(mycanvas);

        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
      }
    
    glfwTerminate();
    return 0;
  }


}

