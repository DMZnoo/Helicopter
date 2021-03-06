//
//  Camera.hpp
//
//  Created by JINWOO LEE on 27/04/20.
//

#ifndef Camera_hpp
#define Camera_hpp


#include <GLFW/glfw3.h>
#include "../Entity/Entity.hpp"
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
    void setViewMatrix(glm::mat4 viewMatrix);
    void cameraPosUpdate(glm::vec3 objPos, float dir);
    
private:
    Controller controller;
    glm::mat4 i_viewMatrix;
    glm::mat4 i_projMatrix;
    float RotatedAngle;
    glm::vec3 objectPosition;
    
    

    
    
};

#endif /* Camera_hpp */
