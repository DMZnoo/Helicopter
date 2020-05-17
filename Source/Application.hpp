//
//  Application.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 27/04/20.
//

#ifndef Application_hpp
#define Application_hpp
#include "Debugger.hpp"
#include <GLFW/glfw3.h>
#include "Control/Camera.hpp"
#include "Shader/Shader.hpp"
#include "Renderer/SkyRenderer.hpp"
#include "Renderer/CubeRenderer.hpp"
#include "Renderer/PlatformRenderer.hpp"
#include "Renderer/LineRenderer.hpp"
#include "Renderer/PropellerRenderer.hpp"
#include "Renderer/HelicopterBodyRenderer.hpp"

class Application
{
public:
    Application();
    Application(unsigned int windowWidth, unsigned int windowHeight);
    void run();

    ~Application();
    
    
};

#endif /* Application_hpp */
