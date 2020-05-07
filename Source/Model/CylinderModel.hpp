//
//  CylinderModel.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 5/05/20.
//

#ifndef CylinderModel_hpp
#define CylinderModel_hpp
#include "Model.hpp"
#include <cmath>
class CylinderModel : public Model
{
public:
    CylinderModel(float topR, float bottomR, float height, int sectors, int stacks);
    void buildVertices();
    unsigned int getBaseIndex() const;
    unsigned int getTopIndex() const;
    void bind();
    void bindBase();
    void bindTop();
    void bindSides();
    
    
private:
    void setup();
    void addVertex(float x, float y, float z);
    void addNormal(float normX, float normY, float normZ);
    void addTexCoords(float textX, float textY);
    void addIndices(float x, float y, float z);
    void loadIBO(const std::vector<GLuint> &indices, unsigned int offset);
    RenderInfo m_renderInfo;
    Vertex vertex;
    int m_dim;
    int m_vboCount = 0;
    std::vector<GLuint> m_buffers;
    std::vector<Mesh> modelInfo;
    Mesh m_mesh;
    BaseTexture m_lineTexture;
    int sectorCount,stackCount;
    float topRadius,baseRadius,height;
    std::vector<float> unitCircleVertices;
    std::vector<float> sideNormals;
    unsigned int baseIndex,topIndex;
};
#endif /* CylinderModel_hpp */
