//
//  Player.hpp
//
//  Created by JINWOO LEE on 12/05/20.
//

#ifndef Player_hpp
#define Player_hpp
#include "Entity.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Control/CraftController.hpp"
#include "../Control/Camera.hpp"
#include <iostream>
class Player : public Entity
{
public:
    Player(glm::vec3 initPos, glm::vec3 initDir);
    glm::mat4 update(glm::mat4 target);
    void updateView(Camera &camera);
    ~Player();
    
private:
    CraftController controller;
    float RotatedAngle;
};

#endif /* Player_hpp */
