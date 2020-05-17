//
//  HelicopterBodyRenderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 9/05/20.
//

#ifndef HelicopterBodyRenderer_hpp
#define HelicopterBodyRenderer_hpp

#include "../Shader/PlatformShader.hpp"
#include "../Control/Camera.hpp"
#include "../Model/Model.hpp"
#include "../Entity/Player.hpp"
class HelicopterBodyRenderer {
  public:
    HelicopterBodyRenderer(std::string path);
    glm::mat4 transferLocation();
    void render( Camera &camera);
    
  private:
    Model m_helicopter;
    PlatformShader m_shader;
//    unsigned int diffuse_n,specular_n,normal_n,height_n;
    std::string typeModel;
    glm::mat4 model;
    float modelHeight;
    BaseTexture m_Texture;
    glm::vec3 direction;
    Player player_1;
};

#endif /* HelicopterBodyRenderer_hpp */
