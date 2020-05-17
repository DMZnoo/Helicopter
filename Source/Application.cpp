//
//  Application.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 27/04/20.
//

#include "Application.hpp"
GLFWwindow* window;
unsigned int width,height;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool init = true;
Application::Application()
{
    width = 1024;
    height = 768;
    
}
Application::Application(unsigned int windowWidth, unsigned int windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
}

Application::~Application() { 
    glfwDestroyWindow(window);
        // Close OpenGL window and terminate GLFW
    glfwTerminate();
}


void Application::run() {
   // Initialise GLFW
     if( !glfwInit() )
     {
         fprintf( stderr, "Failed to initialize GLFW\n" );
         getchar();
         
     }
    
     glfwWindowHint(GLFW_SAMPLES, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
     // Open a window and create its OpenGL context
     window = glfwCreateWindow( width, height, "Assignment 2", NULL, NULL);
     if( window == NULL ){
         fprintf( stderr, "Failed to open GLFW window.\n" );
         getchar();
         glfwTerminate();
         
     }
     glfwMakeContextCurrent(window);
 
     // Initialize GLEW
     glewExperimental = true; // Needed for core profile
     if (glewInit() != GLEW_OK) {
         fprintf(stderr, "Failed to initialize GLEW\n");
         getchar();
         glfwTerminate();
         
     }
    static double xpos,ypos;
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window,width/2,height/2);
    glfwGetCursorPos(window, &xpos, &ypos);
    Camera camera(width,height);
//    CubeRenderer cubeRenderer;
    PlatformRenderer platformRenderer("obj/landing.obj", "platform");

    stbi_set_flip_vertically_on_load(false);
    PropellerRenderer mainPropeller("grey.jpg",glm::vec3(0,1,0), 10.0f,false);
    PropellerRenderer subPropeller("grey.jpg",glm::vec3(0,0,1),3.0f,true);
//    PlatformRenderer guy("cyborg/cyborg.obj", "nanosuit");
    HelicopterBodyRenderer helicopter("helicopter/helicopter.obj");
//    std::cout << "DONE" << std::endl;
    LineRenderer xcoor("red.jpg",0);
    LineRenderer ycoor("green.jpg",1);
    LineRenderer zcoor("blue.jpg",2);

    LineRenderer gridx("red.jpg",0);
    LineRenderer gridz("blue.jpg",2);
    
    

    SkyboxRenderer skyRenderer;
    glEnable(GL_DEPTH_TEST);
//    camera.lookAt(glm::vec3(0.0f,0.0f,0.0f));
     do{
         
        
         glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
         glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
         camera.update();
         helicopter.render(camera);  
         platformRenderer.render(camera);
//
//
//         guy.render(camera);
         xcoor.render(camera);
         ycoor.render(camera);
         zcoor.render(camera);
         gridx.render(camera);
         gridz.render(camera);
         
         mainPropeller.setLocation(helicopter.transferLocation());
         mainPropeller.render(camera);
         subPropeller.setLocation(glm::translate(helicopter.transferLocation(),glm::vec3(0.2f,5,-12.0f)));
         subPropeller.render(camera);

         
         
         skyRenderer.render(camera);
         // Swap buffers
         glfwSwapBuffers(window);
         glfwPollEvents();
 
     } // Check if the ESC key was pressed or the window was closed
     while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );
 
     // Close OpenGL window and terminate GLFW
     glfwTerminate();


       
}





