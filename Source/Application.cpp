//
//  Application.cpp
//
//  Created by JINWOO LEE on 27/04/20.
//

#include "Application.hpp"
GLFWwindow* window;
unsigned int width,height;
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
    
    //set sampling size
     glfwWindowHint(GLFW_SAMPLES, 4);
    //set version, has to equal to shader's version
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compat.
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
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    //capture cursor
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //set initially to middle of the viewport
    glfwSetCursorPos(window,width/2,height/2);
    
    //free flow camera (can move any where without the character or an object
    Camera camera(width,height);
    
    //<-----Renderers---->
    CubeRenderer cubeRenderer;
    
    ModelRenderer platformRenderer("obj/landing.obj", "platform");

    stbi_set_flip_vertically_on_load(false);
    PropellerRenderer mainPropeller("grey.jpg",glm::vec3(0,1,0), 10.0f,false);
    PropellerRenderer subPropeller("grey.jpg",glm::vec3(0,0,1),3.0f,true);
    stbi_set_flip_vertically_on_load(false);
    ModelRenderer guy("cyborg/cyborg.obj", "nanosuit");
    HelicopterBodyRenderer helicopter("helicopter/helicopter.obj");
    
    LineRenderer xcoor("red.jpg",0);
    LineRenderer ycoor("green.jpg",1);
    LineRenderer zcoor("blue.jpg",2);

    LineRenderer gridx("red.jpg",0);
    LineRenderer gridz("blue.jpg",2);
    
    SphereRenderer spherex("blue.jpg",   glm::vec3(1,0,0),5.f);
    SphereRenderer spherey("green.jpg", glm::vec3(0,1,0),5.f);
    SphereRenderer spherez("red.jpg",  glm::vec3(0,0,1),5.f);
    

    SkyboxRenderer skyRenderer;
    glEnable(GL_DEPTH_TEST);
//    camera.lookAt(glm::vec3(0.0f,0.0f,0.0f));
     do{
         
        
         glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
         glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
         camera.update();
         
         platformRenderer.render(camera);

         cubeRenderer.render(camera);
         xcoor.render(camera);
         ycoor.render(camera);
         zcoor.render(camera);
         gridx.render(camera);
         gridz.render(camera);
         spherex.render(camera);
         spherey.render(camera);
         spherez.render(camera);
         //hierchical modeling Helicopter body's location -> basis for main propeller -> basis for subpropeller at the tail etc.
         mainPropeller.setLocation(helicopter.transferLocation());
         mainPropeller.render(camera);
         subPropeller.setLocation(glm::translate(helicopter.transferLocation(),glm::vec3(0.2f,5,-12.0f)));
         subPropeller.render(camera);
         
         //"guy" was just an object i've loaded to test if complex objects would be able to load through my code. now sitting inside the helicopter.. can be modified to be sitting but would require some work (can be done in blender using bones)
         guy.setLocation(glm::translate(helicopter.transferLocation(),glm::vec3(0.8f,2.f,4.0f)));
         guy.render(camera);
         helicopter.render(camera);
         
         
         //skybox
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





