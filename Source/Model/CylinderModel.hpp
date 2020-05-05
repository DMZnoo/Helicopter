//
//  CylinderModel.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 5/05/20.
//

#ifndef CylinderModel_hpp
#define CylinderModel_hpp
#include "Model.hpp"
#include <glm/gtc/constants.hpp>
class CylinderModel : public Model
{
public:
    CylinderModel();
    void generateUnitCircle();
private:
    RenderInfo m_renderInfo;
    int m_dim;
    int m_vboCount = 0;
    std::vector<GLuint> m_buffers;
    std::vector<Mesh> modelInfo;
    float PI = glm::pi<float>();
    Mesh m_mesh;
    BaseTexture m_texture;
    float sectorCount;
    
};
#endif /* CylinderModel_hpp */
