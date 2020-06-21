//
//  Main.cpp
//
//  Created by JINWOO LEE on 3/03/20.
//


// Include GLFW
#include "Application.hpp"
//Replace '{ROOT}' with your root to the source folder
std::string ROOT = "{ROOT}/Helicopter-2/Source/Resources/";
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

