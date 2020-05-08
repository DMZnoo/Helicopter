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
    position = glm::vec3(0,0,3);
    xAngle = glm::pi<float>();
    yAngle = 0.0f;
    initialFOV = 45.0f;
    speed = 5.0f;
    mouseSpeed = 0.005f;
    windowWidth = width;
    windowHeight = height;
    i_viewMatrix = glm::mat4(1.0f);
    i_projMatrix = glm::mat4(1.0f);
    xpos = windowWidth/2;
    ypos = windowHeight/2;
//    m_direction = glm::vec3(0.0f,0.0f,0.0f);
    xAngle += mouseSpeed * float(windowWidth/2);
    yAngle  += mouseSpeed * float( windowHeight/2);

}

void Camera::update()
{
    // glfwGetTime is called only once, the first time this function is called
        static double lastTime = glfwGetTime();
    
        // Compute time difference between current and last frame
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
    
        glfwGetCursorPos(window, &xpos, &ypos);
    
        // Reset mouse position for next frame
        glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
    
        // Compute new orientation
        xAngle += mouseSpeed * float(windowWidth/2 - xpos );
        yAngle   += mouseSpeed * float( windowHeight/2 - ypos );
    
    
        // Direction : Spherical coordinates to Cartesian coordinates conversion
        m_direction = glm::vec3 (
            cos(yAngle) * sin(xAngle),
            sin(yAngle),
            cos(yAngle) * cos(xAngle)
        );
    

        
        // Right vector
        glm::vec3 right = glm::vec3(
            sin(xAngle - glm::pi<float>()/2.0f),
            0,
            cos(xAngle - glm::pi<float>()/2.0f)
        );
        
        // Up vector
        glm::vec3 up = glm::cross( right, m_direction );
//    glm::vec3 up = glm::vec3(0.0f,1.0f,2.0f);
        // Move forward
        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
            position += m_direction * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
            position -= m_direction * deltaTime * speed;
        }
        // Move left
        if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
            position -= right * deltaTime * speed;
        }
        // Move right
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
            position += right * deltaTime * speed;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            position += glm::vec3(0,1,0) * deltaTime * speed;
        }
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position += glm::vec3(0,-1,0) * deltaTime * speed;
        }
        if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            ACTIVATE_GRID = true;
        }
        if(glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
        {
            ACTIVATE_GRID = false;
        }
        float FoV = initialFOV;
    
        // Projection matrix : 45∞ Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        i_projMatrix = glm::perspective(
                                        glm::radians(FoV), //the amount of "zoom"
                                        static_cast<float>(windowWidth/windowHeight), //Aspect Ratio.
                                        0.1f, //near clipping plane
                                        100.0f); //far clipping plane
        // Camera matrix
        i_viewMatrix       = glm::lookAt(
                                    position,           // Camera's current position
                                    position+m_direction, // and looks here
                                    up                  // Head is up (set to 0,-1,0 to look upside-down)
                               );
    
        // For the next frame, the "last time" will be "now"
        lastTime = currentTime;
    
}

void Camera::lookAt(glm::vec3 view)
{

//        glfwGetCursorPos(window, &xpos, &ypos);
//    xpos = windowWidth/2;
//    ypos = windowHeight/2;
        // Reset mouse position for next frame
        glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
//        // Compute new orientation
//        xAngle += mouseSpeed * float(windowWidth/2);
//        yAngle  += mouseSpeed * float( windowHeight/2);

    i_projMatrix = glm::perspective(
                                    glm::radians(45.0f), //the amount of "zoom"
                                    static_cast<float>(windowWidth/windowHeight), //Aspect Ratio.
                                    0.1f, //near clipping plane
                                    100.0f); //far clipping plane
    
//    std::cout << glm::to_string(m_direction) << std::endl;
//    std::cout << "not moving" << std::endl;
    i_viewMatrix = glm::lookAt(
         glm::vec3(0,0,0),           // Camera's current position
         glm::vec3(0,0,0), // and looks here
         view               // Head is up (set to 0,-1,0 to look upside-down)
    );
//    std::cout << glm::to_string(i_viewMatrix) << std::endl;
    
}

const glm::mat4& Camera::getViewMatrix()
{
    return i_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix()
{
    return i_projMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix()
{
    return i_projViewMatrix;
}
