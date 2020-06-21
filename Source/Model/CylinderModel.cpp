//
//  CylinderModel.cpp
//
//  Created by JINWOO LEE on 5/05/20.
//

#include "CylinderModel.hpp"
CylinderModel::CylinderModel(float topR, float bottomR, float height, int sectors, int stacks)
{
    this->sectorCount = sectors;
    if(sectorCount < 3)
        this->sectorCount = 3;
    this->stackCount = stacks;
    if(stackCount < 1)
        this->stackCount = 1;
    this->height = height;
    this->baseRadius = bottomR;
    this->topRadius = topR;
    setup();
    
}
void CylinderModel::setup()
{
    
    float sectorStep = 2*PI/sectorCount;
    float sectorAngle;
    float zAngle = atan2(baseRadius-topRadius,height);
    for(unsigned int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i* sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle));
        unitCircleVertices.push_back(sin(sectorAngle));
        unitCircleVertices.push_back(0);
        
        sideNormals.push_back(cos(sectorAngle)*cos(zAngle));
        sideNormals.push_back(sin(sectorAngle)*cos(zAngle));
        sideNormals.push_back(sin(zAngle));
        
    }
    m_mesh.reset();
    
    
};

void CylinderModel::buildVertices()
{
    float z;
    float radius;
    for(int i =0; i <= stackCount; ++i)
    {
        z = -(height * 0.5f) + (float)i / stackCount * height;
        radius = baseRadius + (float)i / stackCount * (topRadius-baseRadius);
        float decentVal = 1.0f - (float)i / stackCount;
        for(int n = 0,offset = 0; n <= sectorCount; ++n,offset += 3)
        {
            addVertex(unitCircleVertices[offset] * radius, unitCircleVertices[offset+1] * radius, z);
            addNormal(sideNormals[offset], sideNormals[offset+1], sideNormals[offset+2]);
            addTexCoords((float)n / sectorCount, decentVal);
            m_mesh.vertices.push_back(vertex);
            
        }
    }
    
    unsigned int baseVertexIndex = (unsigned int)m_mesh.vertices.size() / 3;
    
    //Build base
    z = -height * 0.5f;
    addVertex(0, 0, z);
    addNormal(0, 0, -1);
    addTexCoords(0.5f, 0.5f);
    m_mesh.vertices.push_back(vertex);
    for(int i = 0, offset = 0; i < sectorCount; ++i, offset += 3)
    {
        addVertex(unitCircleVertices[offset] * baseRadius, unitCircleVertices[offset+1] * baseRadius, z);
        addNormal(0,0,-1);
        addTexCoords(-unitCircleVertices[offset] * 0.5f + 0.5f, -unitCircleVertices[offset+1] * 0.5f + 0.5f);
        m_mesh.vertices.push_back(vertex);
    }
    
    unsigned int topVertexIndex = (unsigned int)m_mesh.vertices.size() / 3;
    
    //Build Top
    z = height * 0.5f;
    addVertex(0, 0, z);
    addNormal(0, 0, 1);
    addTexCoords(0.5f, 0.5f);
    m_mesh.vertices.push_back(vertex);
    for(int i = 0, offset = 0; i < sectorCount; ++i, offset += 3)
    {
        addVertex(unitCircleVertices[offset] * topRadius, unitCircleVertices[offset+1] * topRadius, z);
        addNormal(0,0,1);
        addTexCoords(unitCircleVertices[offset] * 0.5f + 0.5f, -unitCircleVertices[offset+1] * 0.5f + 0.5f);
        m_mesh.vertices.push_back(vertex);
    }
    
    //Build indices for the side
    unsigned int k1,k2;
    for(int i =0; i < stackCount; ++ i)
    {
        k1 = i *(sectorCount + 1);
        k2 = k1 + sectorCount + 1;
        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            addIndices(k1, k1+1, k2);
            addIndices(k2, k1+1, k2+1);
        }
    }
    
    baseIndex = (unsigned int)m_mesh.indices.size();
    
    //Build indices for the base
    for(int i = 0, k=baseVertexIndex+1; i < sectorCount; ++i, ++k)
    {
        if(i < (sectorCount - 1))
            addIndices(baseVertexIndex, k+1, k);
        else
            addIndices(baseVertexIndex, baseVertexIndex+1, k);
    }
    
    topIndex = (unsigned int)m_mesh.indices.size();
    //Build indices for the top
    for(int i = 0, k=topVertexIndex+1; i < sectorCount; ++i, ++k)
    {
        if(i < (sectorCount - 1))
            addIndices(topVertexIndex, k, k+1);
        else
            addIndices(topVertexIndex, k, topVertexIndex + 1);
    }
    
}

void CylinderModel::addVertex(float x, float y, float z) {
    vertex.Position = glm::vec3(x,y,z);
    
};

void CylinderModel::addNormal(float normX, float normY, float normZ) { 
    vertex.Normal = glm::vec3(normX,normY,normZ);
    
};

void CylinderModel::addTexCoords(float textX, float textY) { 
    vertex.TexCoords = glm::vec2(textX,textY);
};

void CylinderModel::addIndices(float x, float y, float z) { 
    m_mesh.indices.push_back(x);
    m_mesh.indices.push_back(y);
    m_mesh.indices.push_back(z);
}

unsigned int CylinderModel::getBaseIndex() const { 
    return baseIndex;
}

unsigned int CylinderModel::getTopIndex() const { 
    return topIndex;
}




void CylinderModel::bindBase() { 
    genVAO();
    genVBO();
    
    bindVAO();
    bindVBO();
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_mesh.vertices.size() * sizeof(Vertex), m_mesh.vertices.data(), GL_STATIC_DRAW));
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    loadIBO(m_mesh.indices,baseIndex);
    

}
void CylinderModel::bind() {
    genVAO();
    genVBO();
    
    bindVAO();
    bindVBO();
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_mesh.vertices.size() * sizeof(Vertex), m_mesh.vertices.data(), GL_STATIC_DRAW));
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    addIBO(m_mesh.indices);
    

}


void CylinderModel::bindTop() { 
    genVAO();
    genVBO();
    
    bindVAO();
    bindVBO();
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_mesh.vertices.size() * sizeof(Vertex), m_mesh.vertices.data(), GL_STATIC_DRAW));
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    loadIBO(m_mesh.indices,topIndex);
}

void CylinderModel::bindSides() { 
    genVAO();
    genVBO();
    
    bindVAO();
    bindVBO();
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_mesh.vertices.size() * sizeof(Vertex), m_mesh.vertices.data(), GL_STATIC_DRAW));
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    loadIBO(m_mesh.indices,0);
}

void CylinderModel::loadIBO(const std::vector<GLuint> &indices, unsigned int offset) { 
    genIBO();
    unsigned int indexCount = ((unsigned int)indices.size() - baseIndex)/2;
    if(offset == 0)
        indexCount = baseIndex;
    m_renderInfo.indicesCount = static_cast<GLuint>(indexCount);
    bindIBO();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint),
                        &indices[offset], GL_STATIC_DRAW));
}













