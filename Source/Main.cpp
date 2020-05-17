//
//  Main.cpp
//  Assignment_1_Jinwoo_Lee
//
//  Created by JINWOO LEE on 3/03/20.
//


// Include GLFW
#include "Application.hpp"
// Include GLM
std::string ROOT = "/Users/daniel/Downloads/Helicopter/Source/Resources/";
const float PI = acos(-1);
bool ACTIVATE_GRID = false;
float PROPELLER_SPEED = 0.0f;
bool LOCK_ON_OBJECT = false;
float ACCELERATION = 0.0f;



int main( void )
{
    Application app(1024,768);
    app.run();
    return 0;
}

