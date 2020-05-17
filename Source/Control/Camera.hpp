//
//  Camera.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 27/04/20.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "../Entity/Entity.cpp"
#include "Controller.hpp"

extern unsigned int width,height;

class Camera : public Entity
{
public:
    Camera(int width, int height);
    void update();
    void init();
    const glm::mat4 &getViewMatrix();
    const glm::mat4 &getProjMatrix();
    const glm::mat4 &getProjectionViewMatrix();
    void setViewMatrix(glm::mat4 viewMatrix);
    void LockEngaged();
    void cameraPosUpdate(glm::vec3 objPos, float dir);
    
private:
    Controller controller;
    glm::mat4 i_viewMatrix;
    glm::mat4 i_projMatrix;
    glm::mat4 i_projViewMatrix;
    float RotatedAngle;
    glm::vec3 objectPosition;
    
    

    
    
};

#endif /* Camera_hpp */
