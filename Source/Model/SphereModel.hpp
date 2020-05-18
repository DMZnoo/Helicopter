//
//  Sphere.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 18/05/20.
//

#ifndef Sphere_hpp
#define Sphere_hpp
#include "Model.hpp"
#include <cmath>
extern const float PI;

class SphereModel : public Model
{
public:
    SphereModel(float radius, int sectors, int stacks);
     void bind();
    
    void buildVertices();
    
    
private:
    void addVertex(float x, float y, float z);
    void addNormal(float normX, float normY, float normZ);
    void addTexCoords(float textX, float textY);
    void addIndices(float x, float y, float z);
    
    RenderInfo m_renderInfo;
    Vertex vertex;
    Mesh m_mesh;
    
    int sectorCount,stackCount;
    float m_radius;
    float sectorAngle, stackAngle, sectorStep, stackStep;
};

#endif /* Sphere_hpp */
