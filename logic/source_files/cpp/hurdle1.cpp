/*Hurdle 1 is like a biiig speed breaker(bigger than the human)*/
#define PI 3.1416

glm::vec4 semicylverts[12];

void get_coords(float r, float h){

	for(i=0;i<6;i++){
		float angle = PI*i/6;
		semicylverts[i] = glm::vec4(0, r*sin(angle), r*cos(angle), 1);
		semicylverts[6+i] = glm::vec4(h, r*sin(angle), r*cos(angle), 1);
	}


}



glm::vec4 VertsHurdle[54];

void quad(int x1, int x2, int x3, int x4, int &start){
	VertsHurdle[start] = semicylverts[x1];start++;
	VertsHurdle[start] = semicylverts[x2];start++;
	VertsHurdle[start] = semicylverts[x3];start++;

	VertsHurdle[start] = semicylverts[x2];start++;
	VertsHurdle[start] = semicylverts[x2];start++;
	VertsHurdle[start] = semicylverts[x4];start++;
	// VertsHurdle[start] = semicylverts[x2];start++;


}

void tri(int x1, int x2, int x3, int &start){
	VertsHurdle[start] = semicylverts[x1];start++;
	VertsHurdle[start] = semicylverts[x2];start++;
	VertsHurdle[start] = semicylverts[x3];start++;
	

}

void fillCoords(){
	int start=0;
	for(int i=0;i<6;i++){
		quad(i, (i+1)%6, i+6, (i+1)%6+6,start);
	}
	tri1(0, 1, 2);
	tri1(0, 2, 3);
	tri1(0, 3, 4);


}

