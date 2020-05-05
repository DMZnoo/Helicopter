//
//  Camera.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 27/04/20.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
class Camera
{
public:
    Camera(int width, int height);
    void update();
    
    const glm::mat4 &getViewMatrix();
    const glm::mat4 &getProjMatrix();
    const glm::mat4 &getProjectionViewMatrix();
    void lookAt(glm::vec3 view);
private:
    glm::mat4 i_viewMatrix;
    glm::mat4 i_projMatrix;
    glm::mat4 i_projViewMatrix;
    glm::vec3 m_direction,position;
    float xAngle,yAngle,initialFOV,speed,mouseSpeed;
    double xpos, ypos;
    int windowWidth,windowHeight;
    
};

#endif /* Camera_hpp */
