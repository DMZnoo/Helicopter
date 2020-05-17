//
//  CraftController.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 13/05/20.
//

#ifndef CraftController_hpp
#define CraftController_hpp

#include "Controller.hpp"
#include <glm/gtx/perpendicular.hpp>

class CraftController : public Controller
{
public:
    CraftController(glm::vec3 initPos, glm::vec3 initDir);
    glm::vec3 updatePos() override;
    glm::vec3 updateKeyboardInput() override;
    
    glm::vec3 getDir() const;
    glm::vec3 getPos() const;
    void setPos(glm::vec3 pos);
    void setDir(glm::vec3 dir);
    float updateAngle();
private:
    float throttle;
    float deltaTime;
    glm::vec3 m_position,m_direction;
    float m_angle,returnAngle;
    float xOffset,zOffset;
    bool landing;
};

#endif /* CraftController_hpp */
