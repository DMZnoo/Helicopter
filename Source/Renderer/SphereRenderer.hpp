//
//  SphereRenderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 18/05/20.
//

#ifndef SphereRenderer_hpp
#define SphereRenderer_hpp
#include "../Shader/CubeShader.hpp"
#include "../Control/Camera.hpp"
#include "../Model/SphereModel.hpp"

class SphereRenderer
{
    public:
      SphereRenderer(std::string path,glm::vec3 axis, float speed);
      
      void render( Camera &camera);
private:
    SphereModel m_sphere;
    CubeShader m_shader;
    BaseTexture m_sphereTexture;
    glm::mat4 model;
    float rotate,rotationSpeed;
    glm::vec3 rotationAxis;
    
};

#endif /* SphereRenderer_hpp */
