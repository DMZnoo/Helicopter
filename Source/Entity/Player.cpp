//
//  Player.cpp
//
//  Created by JINWOO LEE on 12/05/20.
//

#include "Player.hpp"
Player::Player(glm::vec3 initPos, glm::vec3 initDir)
:controller(initPos,initDir)
{
    Position = initPos;
    Direction = initDir;
    Rotation = glm::vec3(0,0,0);
    RotatedAngle = 0.0f;

}
glm::mat4 Player::update(glm::mat4 target)
{
    if(LOCK_ON_OBJECT)
    {
        //adjust the direction by the object's direction.
            glm::vec3 newDir = controller.updateKeyboardInput();
            RotatedAngle = controller.updateAngle();
            Direction = newDir;
            Position = controller.updatePos();
    }
    target = glm::translate(target,Position);
    target = glm::rotate(target,glm::radians(RotatedAngle),glm::vec3(0,1,0));
    
    return target;
};

void Player::updateView(Camera & camera)
{
        RotatedAngle = controller.updateAngle();
        camera.cameraPosUpdate(Position, RotatedAngle);
}




Player::~Player()
{
    clear();
}
