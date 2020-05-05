//
//  PlatformRenderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#ifndef PlatformRenderer_hpp
#define PlatformRenderer_hpp
#include "../Shader/PlatformShader.hpp"
#include "../Control/Camera.hpp"
#include "../Model/Model.hpp"
class PlatformRenderer {
  public:
    PlatformRenderer();
    
    void render( Camera &camera);

  private:
    Model m_platform;
    PlatformShader m_shader;
    unsigned int diffuse_n,specular_n,normal_n,height_n;
};



#endif /* PlatformRenderer_hpp */