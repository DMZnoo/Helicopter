//
//  SphereModel.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 18/05/20.
//

#include "SphereModel.hpp"
SphereModel::SphereModel(float radius, int sectors, int stacks)
{
    m_radius = radius;
    sectorCount = sectors;
    if(sectors < 3)
        sectorCount = 3;
    stackCount = stacks;
    if(sectors < 2)
        sectorCount = 2;
    m_mesh.reset();
    
}
void SphereModel::buildVertices()
{
    sectorStep = 2 * PI/sectorCount;
    stackStep = PI/stackCount;
    float lengthInv = 1.0f / m_radius;
    float xy,z;
    for (unsigned int n = 0; n <= stackCount; ++n)
    {
    	stackAngle = PI/2 - n * stackStep;
    	xy = m_radius * cos(stackAngle);
    	z = m_radius * sin(stackAngle);
        
    	for(unsigned int i = 0; i <= sectorCount; ++i)
    	{
    		sectorAngle = i * sectorStep;
    		addVertex(
    			xy * cos(sectorAngle), 
    			xy * sin(sectorAngle),
    			z
    			);
            
    		addNormal(
    			xy * cos(sectorAngle) * lengthInv,
				xy * sin(sectorAngle) * lengthInv,
				z * lengthInv
    			);
    		addTexCoords(
    			((float)i / sectorCount),
    			((float)n / stackCount)
    			);
            m_mesh.vertices.push_back(vertex);
    	}
    }
    float k1,k2;
    for(unsigned int z = 0; z < stackCount; ++z)
    {
    	k1 = z * (sectorCount + 1);
    	k2 = k1 + sectorCount + 1;

    	for(unsigned int i = 0; i < sectorCount; ++i, ++k1, ++k2 )
    	{
    		if(z != 0)
    			addIndices(k1,k2,k1+1);
    		if(z != (stackCount - 1))
    			addIndices(k1+1,k2,k2+1);

    	}
    }

    


}

void SphereModel::bind()
{
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
    m_renderInfo.indicesCount = static_cast<GLuint>(m_mesh.indices.size());
    addIBO(m_mesh.indices);
};


void SphereModel::addVertex(float x, float y, float z) {
    vertex.Position = glm::vec3(x,y,z);
    
};

void SphereModel::addNormal(float normX, float normY, float normZ) {
    vertex.Normal = glm::vec3(normX,normY,normZ);
    
};

void SphereModel::addTexCoords(float textX, float textY) {
    vertex.TexCoords = glm::vec2(textX,textY);
};

void SphereModel::addIndices(float x, float y, float z) {
    m_mesh.indices.push_back(x);
    m_mesh.indices.push_back(y);
    m_mesh.indices.push_back(z);
}
