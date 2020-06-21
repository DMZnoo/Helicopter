//
//  Renderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 28/04/20.
//

#ifndef CubeRenderer_hpp
#define CubeRenderer_hpp
#include "../Shader/CubeShader.hpp"
#include "../Texture/BaseTexture.hpp"
#include "../Control/Camera.hpp"
#include "../Model/Model.hpp"
class CubeRenderer {
  public:
    CubeRenderer();
    glm::mat4 transferLocation();
    void render( Camera &camera);

  private:
    Model m_cube;
    BaseTexture m_cubeTexture;
    CubeShader m_shader;
    unsigned int cubeVAO,cubeVBO;
    std::vector<float> cubeVertices;
    glm::mat4 model;
};

#endif /* CubeRenderer_hpp */
