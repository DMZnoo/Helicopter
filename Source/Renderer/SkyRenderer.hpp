#ifndef SkyRenderer_hpp
#define SkyRenderer_hpp

#include "../Model/Model.hpp"
#include "../Shader/SkyShader.hpp"
#include "../Texture/SkyTexture.hpp"
#include "../Control/Camera.hpp"


class SkyboxRenderer {
  public:
    SkyboxRenderer();
    
    void render( Camera &camera);

  private:
    Model m_skyCube;
    SkyTexture m_skyTexture;
    SkyShader m_shader;
    std::vector<float> skyboxVertices;
    std::vector<std::string> skyFaces;
//    unsigned int skyboxVAO, skyboxVBO;
    
};
#endif // SkyRenderer_hpp
