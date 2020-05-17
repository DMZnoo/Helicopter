//
//  Camera.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 27/04/20.
//

#include "Camera.hpp"
extern GLFWwindow* window;

Camera::Camera(int width, int height)
{
    Position = glm::vec3(0,0,0);
    i_viewMatrix = glm::mat4(1.0f);
    i_projMatrix = glm::mat4(1.0f);
    objectPosition = glm::vec3(0.f);
    RotatedAngle = 0.f;
}

void Camera::update()
{
    float FoV = 45.0f;
    // Projection matrix : 45∞ Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    i_projMatrix = glm::perspective(
                        glm::radians(FoV), //the amount of "zoom"
                        static_cast<float>(width/height), //Aspect Ratio.
                        0.1f, //near clipping plane
                        100.0f
    ); //far clipping plane
    
    
    if(!LOCK_ON_OBJECT)
    {
        
        Position = controller.updatePos();
        Direction = controller.updateKeyboardInput();
        i_viewMatrix = glm::mat4(1.0f);
        i_viewMatrix = glm::lookAt(
                 Position,           // Camera's current position
            Position+Direction, // and looks here
                 controller.getUpVector() // Head is up (set to 0,-1,0 to look upside-down)
            );
    } else
    {
        
        i_viewMatrix = glm::mat4(1.0f);
        float offsetX = 10.f * sin(glm::radians(RotatedAngle));
        float offsetZ = 10.f * cos(glm::radians(RotatedAngle));
        Position = glm::vec3(
             (objectPosition[0]/2 - offsetX),
             objectPosition[1]/2,
             (objectPosition[2]/2 - offsetZ)
        );



        controller.setLocation(Position);
            Direction = glm::vec3(
                  (objectPosition[0]/2 - offsetX),
                  -(objectPosition[1]/2),
                  (objectPosition[2]/2 - offsetZ)
             );
        
            
            i_viewMatrix = glm::rotate(i_viewMatrix,glm::radians(-RotatedAngle), glm::vec3(0,1,0));
            i_viewMatrix = glm::translate(i_viewMatrix,glm::vec3(
                 Direction[0],
                 Direction[1],
                 Direction[2]
            ));
            i_viewMatrix = glm::rotate(i_viewMatrix,glm::radians(180.f), glm::vec3(0,1,0));
        

                


               
        
    }
    
    
}




const glm::mat4& Camera::getViewMatrix()
{
    return i_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix()
{
    return i_projMatrix;
}

void Camera::setViewMatrix(glm::mat4 viewMatrix)
{
    i_viewMatrix = viewMatrix;
}

void Camera::cameraPosUpdate(glm::vec3 pos, float dir) { 
    objectPosition = pos;
    RotatedAngle = dir;
}




