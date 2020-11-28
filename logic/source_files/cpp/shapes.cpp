/*THIS FILE IS MEANT FOR CREATING GEOMETRIES FOR THE RENDERING*/
#pragma once
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
//#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

#define PI 3.1416


glm::vec4 ellipse_vertices[24];

glm::vec4 ellipse_colors[8] = {
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


void makeQuad_ellipse(int &vertex_position_index, int a1, int a2, int a3, int a4){
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a1]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a2]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a3]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a1]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a3]; vertex_position_index++;
    triangulated_ellipse_vertex_position[vertex_position_index] = ellipse_vertices[a4]; vertex_position_index++;
    // std::cout<<vertex_position_index<<std::endl;
}



void fill_vertices_ellipse(){
    int vertex_position_index = 0;

    for(int i=0;i<12;i++){
        makeQuad_ellipse(vertex_position_index, i, (i+1)%12, 12 + (i+1)%12, 12+i);
    }

    // glm::vec4 color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    for(int i=0;i<138;i++){
        triangulated_ellipse_vertex_color[i] = ellipse_colors[i%8];
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



/*For creating a half ellipse*/

glm::vec4 semiCyclVerts[12];


void fillSemiCylVerts(int r, int h){
	float angle = PI/6;
	for(int i=0;i<6;i++){
		float y = r*sin(i*angle);
		float z = r*cos(i*angle);
		semiCyclVerts[i] = glm::vec4(0,y,z,1);
		semiCyclVerts[i+6] = glm::vec4(h, y, z, 1);
	}


}


glm::vec4 triangulated_semicyl_vertices[84];
glm::vec4 triangulated_semicyl_colors[84];


void fillQuad_semicyl(int a, int b, int c, int d, int &start){
	triangulated_semicyl_vertices[start] = semiCyclVerts[a];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[b];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[c];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[a];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[c];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[d];start++;
}

void fill_triangle_semicyl(int a, int b, int c, int start){
	triangulated_semicyl_vertices[start] = semiCyclVerts[a];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[b];start++;
	triangulated_semicyl_vertices[start] = semiCyclVerts[c];start++;
	
}

void fill_vertices_semicyl(){
	int start = 0;
	fillQuad_semicyl(0,1,7,6,start);
	fillQuad_semicyl(1,2,8,7,start);
	fillQuad_semicyl(2,3,9,8,start);
	fillQuad_semicyl(3,4,10,9,start);
	fillQuad_semicyl(4,5,11,10,start);
	fillQuad_semicyl(5,0,6,11,start);
	fill_triangle_semicyl(0,1,2,start);
	fill_triangle_semicyl(0,2,3,start);
	fill_triangle_semicyl(0,3,4,start);
	fill_triangle_semicyl(0,4,5,start);

	for (int i = 0; i < 84; ++i)
	{
		triangulated_semicyl_colors[i] = glm::vec4(0,0,0,1);
	}

	// fill_triangle_semicyl(5,0,1,start);


}



/*This is the track coords*/
glm::vec4 semiCyclHor[12];

void fillSemiCylVerts_horiz(int r, int h){
	float angle = PI/6;
	for(int i=0;i<6;i++){
		float x = r*cos(i*angle);
		float z = r*sin(i*angle);
		semiCyclHor[i] = glm::vec4(x,0.,z,1);
		semiCyclHor[i+6] = glm::vec4(x, -1*h, z, 1);
	}
}


glm::vec4 triangulated_semicyl_vertices_horiz[84];



void fillQuad_semicyl_horiz(int a, int b, int c, int d, int &start){
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[a];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[b];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[c];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[a];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[c];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[d];start++;
}

void fill_triangle_semicyl_horiz(int a, int b, int c, int start){
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[a];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[b];start++;
	triangulated_semicyl_vertices_horiz[start] = semiCyclHor[c];start++;
	
}

void fill_vertices_semicyl_horiz(float col){
	int start = 0;
	fillQuad_semicyl_horiz(0,1,7,6,start);
	fillQuad_semicyl_horiz(1,2,8,7,start);
	fillQuad_semicyl_horiz(2,3,9,8,start);
	fillQuad_semicyl_horiz(3,4,10,9,start);
	fillQuad_semicyl_horiz(4,5,11,10,start);
	fillQuad_semicyl_horiz(5,0,6,11,start);
	fill_triangle_semicyl_horiz(0,1,2,start);
	fill_triangle_semicyl_horiz(0,2,3,start);
	fill_triangle_semicyl_horiz(0,3,4,start);
	fill_triangle_semicyl_horiz(0,4,5,start);

	for (int i = 0; i < 84; ++i)
	{
		triangulated_semicyl_colors[i] = glm::vec4(col, col, col, 1);
	}


	// fill_triangle_semicyl(5,0,1,start);


}


glm::vec4 rectCuboid[8];
glm::vec4 rectCuboidCoords[36];
glm::vec4 rectCuboidColors[36];

void fillQuad_cuboid(int a, int b, int c, int d, int &start){

	rectCuboidCoords[start] = rectCuboid[a];start++;
	rectCuboidCoords[start] = rectCuboid[b];start++;
	rectCuboidCoords[start] = rectCuboid[c];start++;
	rectCuboidCoords[start] = rectCuboid[a];start++;
	rectCuboidCoords[start] = rectCuboid[c];start++;
	rectCuboidCoords[start] = rectCuboid[d];start++;
}

void makeCuboid(float l, float b, float h){
	
	rectCuboidCoords[0]= glm::vec4(0, -1*h, 0, 1);
	rectCuboidCoords[1]=glm::vec4(0, 0, 0, 1);
	rectCuboidCoords[2]=glm::vec4(b, 0, 0, 1);
	rectCuboidCoords[3]=glm::vec4(b, -1*h, 0, 1);
	rectCuboidCoords[4]=glm::vec4(0, -1*h, l, 1);
	rectCuboidCoords[5]=glm::vec4(0, 0, l, 1);
	rectCuboidCoords[6]=glm::vec4(b, 0, l, 1);
	rectCuboidCoords[7]=glm::vec4(b, -1*h, l, 1);
			
	
	int start = 0;
	fillQuad_cuboid(0,1,2,3, start);
	fillQuad_cuboid(0,1,5,4, start);
	fillQuad_cuboid(1,2,6,5, start);
	fillQuad_cuboid(2,3,7,6, start);
	fillQuad_cuboid(3,0,4,7, start);
	fillQuad_cuboid(4,5,6,7, start);

	for (int i = 0; i < 36; ++i)
	{
		rectCuboidColors[i] = glm::vec4(0,0,0,1);
	}
}
