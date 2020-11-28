#include "bike.hpp"
const int num_vertices = 72;

  glm::vec4 mainpositions[16] = {
  //for bike body
  glm::vec4(-3.0, 0.4, 0.25, 1.0),
  glm::vec4(0.0, -1.0, 0.25, 1.0),
  glm::vec4(0.0, 0.0, 0.25, 1.0),
  glm::vec4(1.75, 0.5, 0.25, 1.0),
  glm::vec4(-3.0, 0.4, -0.25, 1.0),
  glm::vec4(0.0, -1.0, -0.25, 1.0),
  glm::vec4(0.0, 0.0, -0.25, 1.0),
  glm::vec4(1.75, 0.5, -0.25, 1.0),
};
glm:: vec4 handle[8] = {
  //for handle
  glm::vec4(0.0,0.0,0.25,1.0),
  glm::vec4(0.0,-1.5,0.25,1.0),
  glm::vec4(0.1,-1.5,0.25,1.0),
  glm::vec4(0.1,-0.0,0.25,1.0),
  glm::vec4(0.0,0.0,-0.25,1.0),
  glm::vec4(0.0,-1.5,-0.25,1.0),
  glm::vec4(0.1,-1.5,-0.25,1.0),
  glm::vec4(0.1,-0.0,-0.25,1.0)
};
glm::vec4 colors[8] = {
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
};
int tri_idx=0;
glm::vec4 v_main_positions[num_vertices];
glm::vec4 v_colors[num_vertices];
glm::vec4 v_handle[num_vertices];
void body(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors[a]; v_main_positions[tri_idx] = mainpositions[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_main_positions[tri_idx] = mainpositions[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_main_positions[tri_idx] = mainpositions[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_main_positions[tri_idx] = mainpositions[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_main_positions[tri_idx] = mainpositions[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_main_positions[tri_idx] = mainpositions[d]; tri_idx++;
 }
void quadhandle(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors[a]; v_handle[tri_idx] = handle[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_handle[tri_idx] = handle[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_handle[tri_idx] = handle[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_handle[tri_idx] = handle[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_handle[tri_idx] = handle[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_handle[tri_idx] = handle[d]; tri_idx++;
 }
 void makebike(void)
{ //for main body
    body( 2, 0, 1, 3 );
    body( 6, 4, 5, 7 );
    body( 0, 1, 4, 5 );
    body( 0, 2, 4, 6 );
    body( 2, 3, 6, 7 );
    body( 1, 3, 5, 7 );
    tri_idx=0;
    //for handle
    quadhandle(0,1,2,3);
    quadhandle( 4,5,6,7);
    quadhandle( 0, 1, 4,5);
    quadhandle( 2,3,6,7);
    quadhandle( 0,3,4,7);
    quadhandle( 1,2,5,6);
    tri_idx=0;
    //for wheels
    ellipseVertices(0.875,0.875,0.875,0.875,1.0);
    fill_vertices();
   

}
void createBike(){
makebike();
bike1 = new csX75::HNode(NULL,num_vertices,v_main_positions,v_colors,sizeof(v_main_positions),sizeof(v_colors));
bike2 = new csX75::HNode(node1,num_vertices,v_handle,v_colors,sizeof(v_handle),sizeof(v_colors));
bike2->change_parameters(1.50,0.75,0.0,0.0,0.0,22.5);
bike3 = new csX75::HNode(node2,144,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
bike3->change_parameters(0.0,-2.0,0.0,0.0,0.0,0.0);
bike4 = new csX75::HNode(node1,num_vertices,v_handle,v_colors,sizeof(v_handle),sizeof(v_colors));
bike4->change_parameters(0.0,-0.875,0.0,0.0,0.0,-82.5);
root_node = curr_node = node4;
bike5 = new csX75::HNode(node4,144,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
bike5->change_parameters(0.0,-2.0,0.0,0.0,0.0,0.0);
}
