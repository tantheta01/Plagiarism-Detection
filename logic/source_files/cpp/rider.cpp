#include "ellipse_making.cpp"
#include "07_hierarchical_modelling.hpp"

void makeNodes(){


  ellipseVertices(0.8, 0.4, 0.7, 0.3, 1.0);
  fill_vertices();
  
  node1 = new csX75::HNode(NULL,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));

  ellipseVertices(0.7, 0.3, 0.7, 0.3, 0.3);
  fill_vertices();

  node2 = new csX75::HNode(node1,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node2->change_parameters(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.7, 0.3, 1.0, 0.7, 1.0);
  fill_vertices();

  node3 = new csX75::HNode(node2,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node3->change_parameters(0.0, 0.3, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(1.0, 0.7, 1.0, 0.7, 0.3);
  fill_vertices();

  node4 = new csX75::HNode(node3,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node4->change_parameters(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.3, 0.3, 0.3, 0.3, 0.2);
  fill_vertices();

  node5 = new csX75::HNode(node4,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node5->change_parameters(0.0, 0.3, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.3, 0.3, 0.4, 0.4, 0.6);
  fill_vertices();

  node6 = new csX75::HNode(node5,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node6->change_parameters(0.0, 0.2, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.2, 0.2, 0.2, 0.2, 1.0);
  fill_vertices();

  node7 = new csX75::HNode(node4,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node7->change_parameters(-1.0, -0.75, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.2, 0.2, 0.2, 0.2, 1.0);
  fill_vertices();

  node8 = new csX75::HNode(node4,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node8->change_parameters(1.0, -0.75, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.1, 0.1, 0.1, 0.1, 0.1);
  fill_vertices();

  node9 = new csX75::HNode(node7,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node9->change_parameters(0.0, -0.1, 0.0, 0.0, 0.0, 0.0);

  
  ellipseVertices(0.1, 0.1, 0.1, 0.1, 0.1);
  fill_vertices();

  node10 = new csX75::HNode(node8,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node10->change_parameters(0.0, -0.1, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.175, 0.175, 0.150, 0.150, 1.0);
  fill_vertices();

  node11 = new csX75::HNode(node9,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node11->change_parameters(0.0, -1.0, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.175, 0.175, 0.150, 0.150, 1.0);
  fill_vertices();

  node12 = new csX75::HNode(node10,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node12->change_parameters(0.0, -1.0, 0.0, 0.0, 0.0, 0.0);


  ellipseVertices(0.35, 0.35, 0.4, 0.4, 0.1);
  fill_vertices();

  node13 = new csX75::HNode(node1,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node13->change_parameters(-0.2, -0.1, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.35, 0.35, 0.4, 0.4, 0.1);
  fill_vertices();

  node14 = new csX75::HNode(node1,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node14->change_parameters(0.2, -0.1, 0.0, 0.0, 0.0, 0.0);


  ellipseVertices(0.25, 0.2, 0.35, 0.35, 1.0);
  fill_vertices();

  node15 = new csX75::HNode(node13,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node15->change_parameters(0, -1.0, 0.0, 0.0, 0.0, 0.0);
  
  ellipseVertices(0.25, 0.2, 0.35, 0.35, 1.0);
  fill_vertices();

  node16 = new csX75::HNode(node14,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node16->change_parameters(0, -1.0, 0.0, 0.0, 0.0, 0.0);

  ellipseVertices(0.25, 0.27, 0.25, 0.27, 0.1);
  fill_vertices();

  node17 = new csX75::HNode(node15,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node17->change_parameters(0, -0.1, 0.1, 0.02, 0.0, 0.0);

  ellipseVertices(0.25, 0.27, 0.25, 0.27, 0.1);
  fill_vertices();

  node18 = new csX75::HNode(node16,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node18->change_parameters(0, -0.1, 0.1, 0.02, 0.0, 0.0);


  ellipseVertices(0.25, 0.2, 0.25, 0.2, 1.0);
  fill_vertices();

  node19 = new csX75::HNode(node17,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node19->change_parameters(0, -1.0, -0.02, 0.0, 0.0, 0.0);
  
  ellipseVertices(0.25, 0.2, 0.25, 0.2, 1.0);
  fill_vertices();

  node20 = new csX75::HNode(node18,cylinder_vertices,triangulated_ellipse_vertex_position,triangulated_ellipse_vertex_color,sizeof(triangulated_ellipse_vertex_position),sizeof(triangulated_ellipse_vertex_color));
  node20->change_parameters(0, -1.0, -0.02, 0.0, 0.0, 0.0);


}