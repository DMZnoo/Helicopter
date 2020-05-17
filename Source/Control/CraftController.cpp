//
//  CraftController.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 13/05/20.
//

#include "CraftController.hpp"
extern GLFWwindow* window;

CraftController::CraftController(glm::vec3 initPos, glm::vec3 initDir) {
    throttle = 10.0f;
    m_angle = 0.f;
    m_position = initPos;
    m_direction = initDir;
    xOffset = 0.0f;
    zOffset = 0.0f;
    returnAngle = 0.f;
    landing = false;
};

glm::vec3 CraftController::updatePos() {
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);

    
    lastTime = currentTime;
    return m_position;
}
glm::vec3 CraftController::updateKeyboardInput() {
    
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        if(glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE)
        {
            
            LOCK_ON_OBJECT = !LOCK_ON_OBJECT;
        }
    }
    if(m_position[1] > 0.f)
    {
        
        // Move forward
        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
            
            m_position += m_direction * deltaTime * throttle;
        }
        // Move backward
        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
            
            m_position -= m_direction * deltaTime * throttle;
        };
        // Move left
        if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
            
            m_angle += 2.0f;
            returnAngle = -m_angle;
            m_position[0] += cos(glm::radians(m_angle)) * deltaTime * throttle;
            m_position[2] += sin(glm::radians(m_angle)) * deltaTime * throttle;
            m_direction = glm::vec3(
                cos(glm::radians(m_angle + 90.f)),
                m_direction[1],
                sin(glm::radians(m_angle + 90.f))
            );
        }
        // Move right
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
            
            m_angle -= 2.0f;
            returnAngle = -m_angle;
            m_position[0] -= cos(glm::radians(m_angle)) * deltaTime * throttle;
            m_position[2] -= sin(glm::radians(m_angle)) * deltaTime * throttle;
            m_direction = glm::vec3(
                cos(glm::radians(m_angle + 90.f)),
                m_direction[1],
                sin(glm::radians(m_angle + 90.f))
            );
        }
    }
    
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        landing = false;
        if(PROPELLER_SPEED >= 200.0f)
        {
            
            m_position[1] += throttle * deltaTime;
            
        }
        
        if(PROPELLER_SPEED + ACCELERATION < 200.0f)
        {
            ACCELERATION += 0.01f;
        }
        
        PROPELLER_SPEED += ACCELERATION;

    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if(m_position[1]-0.01f > 0.0f)
            m_position[1] -= throttle * deltaTime;
        else
        {
            landing = true;
        }
        
    }
    if(landing)
    {
        if(ACCELERATION-0.01f >= 0.f)
            ACCELERATION -= 0.01f;
        else
            PROPELLER_SPEED = 0.f;


    }


    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        ACTIVATE_GRID = true;
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
    {
        ACTIVATE_GRID = false;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        PROPELLER_SPEED += ACCELERATION;
    }
    return m_direction;
}
glm::vec3 CraftController::getPos() const
{
    return m_position;
}
glm::vec3 CraftController::getDir() const
{
   
    return m_direction;
}

float CraftController::updateAngle()
{
    return returnAngle;
}


void CraftController::setPos(glm::vec3 pos) {
    m_position = pos;
    
}

void CraftController::setDir(glm::vec3 dir) {
    m_direction = dir;
}
