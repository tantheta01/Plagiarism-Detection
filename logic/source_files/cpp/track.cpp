#include "track.hpp"


void makeTrack(){
	fillSemiCylVerts_horiz(15, 0.1);
	fill_vertices_semicyl_horiz(0);

	firstOuter = new csX75::HNode(NULL,84,triangulated_semicyl_vertices_horiz,triangulated_semicyl_colors,sizeof(triangulated_semicyl_vertices_horiz),sizeof(triangulated_semicyl_vertices_horiz));


	fillSemiCylVerts_horiz(10, 0.1);
	fill_vertices_semicyl_horiz(1);

	firstInner = new csX75::HNode(firstOuter,84,triangulated_semicyl_vertices_horiz,triangulated_semicyl_colors,sizeof(triangulated_semicyl_vertices_horiz),sizeof(triangulated_semicyl_vertices_horiz));


	fillSemiCylVerts_horiz(15, 0.1);
	fill_vertices_semicyl_horiz(0);

	secondOuter = new csX75::HNode(firstOuter,84,triangulated_semicyl_vertices_horiz,triangulated_semicyl_colors,sizeof(triangulated_semicyl_vertices_horiz),sizeof(triangulated_semicyl_vertices_horiz));
	secondOuter->change_parameters(0,0,-30,0,PI, 0);


	fillSemiCylVerts_horiz(10, 0.1);
	fill_vertices_semicyl_horiz(1);

	secondInner = new csX75::HNode(secondOuter,84,triangulated_semicyl_vertices_horiz,triangulated_semicyl_colors,sizeof(triangulated_semicyl_vertices_horiz),sizeof(triangulated_semicyl_vertices_horiz));


	makeCuboid(30, 5, 0.1);

	straightFirst = new csX75::HNode(firstOuter,36,rectCuboidCoords,rectCuboidColors,sizeof(rectCuboidCoords),sizeof(rectCuboidColors));
	straightFirst->change_parameters(-30, 0, 0, 0, 0, 0);


	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	bigSpeedBreaker1 = new csX75::HNode(straightFirst,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));

	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	bigSpeedBreaker2 = new csX75::HNode(bigSpeedBreaker1,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	bigSpeedBreaker2->change_parameters(0,0,6,PI,0,0);


	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	bigSpeedBreaker3 = new csX75::HNode(bigSpeedBreaker2,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	bigSpeedBreaker3->change_parameters(0,0,6,PI,0,0);
	

	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	bigSpeedBreaker4 = new csX75::HNode(bigSpeedBreaker3,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	bigSpeedBreaker4->change_parameters(0,0,6,PI,0,0);
	


	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	bigSpeedBreaker5 = new csX75::HNode(bigSpeedBreaker4,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	bigSpeedBreaker5->change_parameters(0,0,6,PI,0,0);
	
	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	bigSpeedBreaker6 = new csX75::HNode(bigSpeedBreaker5,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	bigSpeedBreaker6->change_parameters(0,0,6,PI,0,0);

	fillSemiCylVerts(5,0.2);
	fill_vertices_semicyl();


	smallSpeedBreaker1 = new csX75::HNode(straightFirst,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));

	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	smallSpeedBreaker2 = new csX75::HNode(smallSpeedBreaker1,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	smallSpeedBreaker2->change_parameters(0,0,6,PI,0,0);


	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	smallSpeedBreaker3 = new csX75::HNode(smallSpeedBreaker2,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	smallSpeedBreaker3->change_parameters(0,0,6,PI,0,0);
	

	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	smallSpeedBreaker4 = new csX75::HNode(smallSpeedBreaker3,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	smallSpeedBreaker4->change_parameters(0,0,6,PI,0,0);
	


	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	smallSpeedBreaker5 = new csX75::HNode(smallSpeedBreaker4,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	smallSpeedBreaker5->change_parameters(0,0,6,PI,0,0);
	
	fillSemiCylVerts(5,3);
	fill_vertices_semicyl();

	smallSpeedBreaker6 = new csX75::HNode(smallSpeedBreaker5,84,triangulated_semicyl_vertices,triangulated_semicyl_colors,sizeof(triangulated_semicyl_colors),sizeof(triangulated_semicyl_colors));
	smallSpeedBreaker6->change_parameters(0,0,6,PI,0,0);




	


}