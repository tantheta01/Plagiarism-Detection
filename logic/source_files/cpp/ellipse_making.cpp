#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#define PI 3.1416


const int  cylinder_vertices = 138;
// const int square_vertices = 24;


glm::vec4 ellipse_vertices[24];

glm::vec4 colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};



void ellipseVertices(float lower_major_axis, float lower_minor_axis, float upper_major_axis, float upper_minor_axis, float height){

    for(int i=0;i<12;i++){
        float x = lower_major_axis * cos(PI*i/6);
        float z = lower_minor_axis * sin(PI*i/6);
        ellipse_vertices[i] = glm::vec4(x, 0, z, 1.0);
    }


    for(int i=0;i<12;i++){
        float x = upper_major_axis * cos(PI*i/6);
        float z = upper_minor_axis * sin(PI*i/6);
        ellipse_vertices[12+i] = glm::vec4(x, height, z, 1.0);
    }

}

glm::vec4 triangulated_ellipse_vertex_position[138];
glm::vec4 triangulated_ellipse_vertex_color[138];


void makeQuad(int &vertex_position_index, int a1, int a2, int a3, int a4){
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a1]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a2]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a3]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a1]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a3]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a4]; vertex_position_index++;
    // std::cout<<vertex_position_index<<std::endl;
}



void fill_vertices(){
    int vertex_position_index = 0;

    for(int i=0;i<12;i++){
        makeQuad(vertex_position_index, i, (i+1)%12, 12 + (i+1)%12, 12+i);
    }

    // glm::vec4 color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    for(int i=0;i<138;i++){
        triangulated_ellipse_vertex_color[i] = colors[i%8];
    }
    int ver1=0, ver2, ver3;
    for(int i=1;i<11;i++){
        ver2 = i+1, ver3 = i;
        triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[ver1]; vertex_position_index++;
        triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[ver2]; vertex_position_index++;
        triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[ver3]; vertex_position_index++;
    }
    std::cout<<"Hi\n";

    ver2 = 1, ver3 = 11;

    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[ver1]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[ver2]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[ver3]; vertex_position_index++;

    for(int i=1;i<11;i++){

        ver2 = i, ver3 = i+1;
        triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[12+ver1]; vertex_position_index++;
        triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[12+ver2]; vertex_position_index++;
        triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[12+ver3]; vertex_position_index++;
    }

    ver2 = 11, ver3 = 1;

    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[12+ver1]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[12+ver2]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[12+ver3]; vertex_position_index++;
    std::cout<<vertex_position_index<<std::endl;



}


//making functions for big hurdles