//
//  Application.hpp
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
#include "Renderer/ModelRenderer.hpp"
#include "Renderer/LineRenderer.hpp"
#include "Renderer/PropellerRenderer.hpp"
#include "Renderer/HelicopterBodyRenderer.hpp"
#include "Renderer/SphereRenderer.hpp"
class Application
{
public:
    Application();
    Application(unsigned int windowWidth, unsigned int windowHeight);
    void run();

    ~Application();
    
    
};

#endif /* Application_hpp */
