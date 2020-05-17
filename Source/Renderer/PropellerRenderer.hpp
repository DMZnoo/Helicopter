//
//  PropellerRenderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 8/05/20.
//

#ifndef PropellerRenderer_hpp
#define PropellerRenderer_hpp
#include "../Shader/CubeShader.hpp"
#include "../Control/Camera.hpp"
#include "../Model/CylinderModel.hpp"
#include <glm/gtx/transform2.hpp>
extern float PROPELLER_SPEED;
class PropellerRenderer
{
    public:
        PropellerRenderer(std::string path,glm::vec3 axis, float length, bool tilt);
        void setLocation(glm::mat4 location);
        void render( Camera &camera);

    private:
      CylinderModel m_propeller;
      CubeShader m_shader;
      BaseTexture m_Texture;
    glm::mat4 model;
    glm::vec3 newLoc;
    glm::vec3 rotationAxis;
    bool tilted;
};

#endif /* PropellerRenderer_hpp */
