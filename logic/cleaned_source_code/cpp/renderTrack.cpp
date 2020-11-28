// #include "human.hpp"#include "renderTrack.hpp"// #include "bike.hpp"// GLuint shaderProgram;// glm::mat4 rotation_matrix;// glm::mat4 projection_matrix;// glm::mat4 c_rotation_matrix;// glm::mat4 lookat_matrix;// glm::mat4 model_matrix;// glm::mat4 view_matrix;// glm::mat4 modelview_matrix;// GLuint uModelViewMatrix;void initBuffersGL(void)// Load shaders and use the resulting shader programstd::string vertex_shader_file("07_vshader.glsl");std::string fragment_shader_file("07_fshader.glsl");std::vector<GLuint> shaderList;shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));csX75::CreateProgramGL(shaderList);glUseProgram( shaderProgram );// getting the attributes from the shader programglGetAttribLocation( shaderProgram, "vPosition" );glGetAttribLocation( shaderProgram, "vColor" );glGetUniformLocation( shaderProgram, "uModelViewMatrix");makeTrack();std::cout<<"calledsdd"<<std::endl;createHuman();createBike();// Creating the hierarchy:// We are usin_g the original colorcube function to generate the vertices of the cuboid//  firstOuter;void renderGL(void)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);matrixStack.clear();//Creating the lookat and the up vectors for the cameraglm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));glm::vec4  glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;glm::vec4  glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;//Creating the lookat matrixglm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));//creating the projection matrixif(enable_perspective)glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);// glm::perspective(glm::radians(90.0),1.0,0.1,5.0);elseglm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);projection_matrix*lookat_matrix;matrixStack.push_back(view_matrix);firstOuter->render_tree();// node1->render_tree();// bike1->render_tree();int main(int argc, char** argv)//! The pointer to the GLFW windowGLFWwindow* window;//! Setting up the GLFW Error callbackglfwSetErrorCallback(csX75::error_callback);//! Initialize GLFWif (!glfwInit())return -1;//We want OpenGL 4.0glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//This is for MacOSX - can be omitted otherwiseglfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//We don't want the old OpenGLglfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//! Create a windowed mode window and its OpenGL contextglfwCreateWindow(720, 720, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);if (!window)glfwTerminate();return -1;//! Make the window's context currentglfwMakeContextCurrent(window);//Initialize GLEW//Turn this on to get Shader based OpenGLGL_TRUE;GLenum  glewInit();if (GLEW_OK != err)//Problem: glewInit failed, something is seriously wrong.std::cerr<<"GLEW Init Failed : %s"<<std::endl;//Print and see what context got enabledstd::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;//Keyboard CallbackglfwSetKeyCallback(window, csX75::key_callback);//Framebuffer resize callbackglfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);// Ensure we can capture the escape key being pressed belowglfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Initialize GL statecsX75::initGL();initBuffersGL();// Loop until the user closes the windowwhile (glfwWindowShouldClose(window) == 0)// firstOuter->inc_rx();// Render hererenderGL();// Swap front and back buffersglfwSwapBuffers(window);// Poll for and process eventsglfwPollEvents();glfwTerminate();return 0;