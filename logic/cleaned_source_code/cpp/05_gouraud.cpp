CSX75 Tutorial 5(a) Gouraud ShadingA program which draws a tesselated sphereand applies gouraud shading to it.-------------------------------------To run the code./05_shading <amount_of_tesselation>-------------------------------------as long as amount of tesselation is between(20 & 360)Use the arrow keys and PgUp,PgDn,keys to make the sphere move.Use the keys W, A, S, D to move Camera.At starting the scene is in Perspective Mode,pressing P toggles the Wireframe.Pressing G toggles different shading methods.Modified from An Introduction to OpenGL Programming,Ed Angel and Dave Shreiner, SIGGRAPH 2013Written by Aditya Prakash, 2015#include "05_gouraud.hpp"int 50;bool false;double 3.14159265;GLuint shaderProgram;GLuint vbo[2], vao[2];glm::mat4 rotation_matrix;glm::mat4 projection_matrix;glm::mat4 c_rotation_matrix;glm::mat4 lookat_matrix;glm::mat4 model_matrix;glm::mat4 view_matrix;glm::mat4 modelview_matrix;glm::mat3 normal_matrix;GLuint uModelViewMatrix;GLuint viewMatrix;GLuint normalMatrix;//-----------------------------------------------------------------const int  100000;int 0;glm::vec4 v_positions[num_vertices];glm::vec4 v_colors[num_vertices];glm::vec4 v_normals[num_vertices];// Variables for wireframeint 0;glm::vec4 w_positions[num_vertices];glm::vec4 w_colors[num_vertices];glm::vec4 w_normals[num_vertices];glm::vec4 color(0.6, 0.6, 0.6, 1.0);glm::vec4 black(0.2, 0.2, 0.2, 1.0);glm::vec4 white(1.0, 1.0, 1.0, 1.0);double  1;int  10;int  10;void sphere(double radius, int Lats, int Longs)float lats,longs;float (180/(float(Lats)*10))/2;float (180/(float(Longs)*10))/2;float l;for ( 0.0; lats <= PI; lats+=sectors)for( 0.0; longs <= 2.0*PI; longs+=slices)float  radius * sin(lats) * cos(longs);float  radius * sin(lats) * sin(longs);float  radius * cos(lats);glm::vec4 pt(x, y, z, 1.0);v_colors[tri_idx] = white; v_positions[tri_idx] = pt;v_normals[tri_idx] = pt; tri_idx++;w_colors[wire_idx] = black; w_positions[wire_idx] = pt;w_normals[wire_idx] = pt; wire_idx++;if(lats+sectors>PI)PI;elselats+sectors;radius * sin(l) * cos(longs);radius * sin(l) * sin(longs);radius * cos(l);glm::vec4(x, y, z, 1.0);v_colors[tri_idx] = white; v_positions[tri_idx] = pt;v_normals[tri_idx] = pt; tri_idx++;w_colors[wire_idx] = black; w_positions[wire_idx] = pt;w_normals[wire_idx] = pt; wire_idx++;// To Complete the wireframefor ( 0.0; lats <= PI; lats+=sectors)for( 0.0; longs <= 2.0*PI; longs+=slices)float  radius * sin(lats) * cos(longs);float  radius * sin(lats) * sin(longs);float  radius * cos(lats);glm::vec4 pt(x, y, z, 1.0);w_colors[wire_idx] = black; w_positions[wire_idx] = pt;w_normals[wire_idx] = pt; wire_idx++;//-----------------------------------------------------------------void initBuffersGL(void)// Load shaders and use the resulting shader programstd::string vertex_shader_file("05_vshader.glsl");std::string fragment_shader_file("05_fshader.glsl");std::vector<GLuint> shaderList;shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));csX75::CreateProgramGL(shaderList);glUseProgram( shaderProgram );// getting the attributes from the shader programGLuint  glGetAttribLocation( shaderProgram, "vPosition" );GLuint  glGetAttribLocation( shaderProgram, "vColor" );GLuint  glGetAttribLocation( shaderProgram, "vNormal" );glGetUniformLocation( shaderProgram, "uModelViewMatrix");glGetUniformLocation( shaderProgram, "normalMatrix");glGetUniformLocation( shaderProgram, "viewMatrix");//Ask GL for two Vertex Attribute Objects (vao) , one for the colorcube and one for the plane.glGenVertexArrays (2, vao);//Ask GL for two Vertex Buffer Object (vbo)glGenBuffers (2, vbo);//Set 0 as the current array to be used by binding itglBindVertexArray (vao[0]);//Set 0 as the current buffer to be used by binding itglBindBuffer (GL_ARRAY_BUFFER, vbo[0]);// Call the sphere functiontesselation;tesselation;sphere(Radius, Lat, Long);//Copy the points into the current bufferglBufferData (GL_ARRAY_BUFFER, sizeof (v_positions) + sizeof(v_colors) + sizeof(v_normals), NULL, GL_STATIC_DRAW);glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_colors)+sizeof(v_positions), sizeof(v_normals), v_normals );// set up vertex arrayglEnableVertexAttribArray( vPosition );glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );glEnableVertexAttribArray( vColor );glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_positions)) );glEnableVertexAttribArray( vNormal );glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_positions) + sizeof(v_colors)) );// For The Wireframe too ... --------//Set 1 as the current array to be used by binding itglBindVertexArray (vao[1]);//Set 1 as the current buffer to be used by binding itglBindBuffer (GL_ARRAY_BUFFER, vbo[1]);//Copy the points into the current bufferglBufferData (GL_ARRAY_BUFFER, sizeof (w_positions) + sizeof(w_colors) + sizeof(w_normals), NULL, GL_STATIC_DRAW);glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(w_positions), w_positions );glBufferSubData( GL_ARRAY_BUFFER, sizeof(w_positions), sizeof(w_colors), w_colors );glBufferSubData( GL_ARRAY_BUFFER, sizeof(w_colors)+sizeof(w_positions), sizeof(w_normals), w_normals );// set up vertex arrayglEnableVertexAttribArray( vPosition );glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );glEnableVertexAttribArray( vColor );glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(w_positions)) );glEnableVertexAttribArray( vNormal );glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(w_positions) + sizeof(w_colors)) );void renderGL(void)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));rotation_matrix;//Creating the lookat and the up vectors for the cameraglm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));glm::vec4  glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;glm::vec4  glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;//Creating the lookat matrixglm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));//creating the projection matrixglm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);projection_matrix*lookat_matrix;glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));if(wireframe)// Drawing a Wireframe for SPHEREview_matrix*model_matrix;glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));glBindVertexArray (vao[1]);glDrawArrays(GL_LINE_STRIP,0,num_vertices);// Draw the sphereview_matrix*model_matrix;glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));glBindVertexArray (vao[0]);glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);int main(int argc, char** argv)//! The pointer to the GLFW windowGLFWwindow* window;//! Setting up the GLFW Error callbackglfwSetErrorCallback(csX75::error_callback);//! Initialize GLFWif (!glfwInit())return -1;if(argc > 1)atoi(argv[1]);//We want OpenGL 4.0glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//This is for MacOSX - can be omitted otherwiseglfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//We don't want the old OpenGLglfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//! Create a windowed mode window and its OpenGL contextglfwCreateWindow(512, 512, "CS475/CS675 Tutorial 5: Shading a Sphere", NULL, NULL);if (!window)glfwTerminate();return -1;//! Make the window's context currentglfwMakeContextCurrent(window);//Initialize GLEW//Turn this on to get Shader based OpenGLGL_TRUE;GLenum  glewInit();if (GLEW_OK != err)//Problem: glewInit failed, something is seriously wrong.std::cerr<<"GLEW Init Failed : %s"<<std::endl;//Keyboard CallbackglfwSetKeyCallback(window, csX75::key_callback);//Framebuffer resize callbackglfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);// Ensure we can capture the escape key being pressed belowglfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Initialize GL statecsX75::initGL();initBuffersGL();// Loop until the user closes the windowwhile (glfwWindowShouldClose(window) == 0)// Render hererenderGL();// Swap front and back buffersglfwSwapBuffers(window);// Poll for and process eventsglfwPollEvents();glfwTerminate();return 0;//-------------------------------------------------------------------------