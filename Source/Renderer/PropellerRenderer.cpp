//
//  PropellerRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 8/05/20.
//

#include "PropellerRenderer.hpp"


PropellerRenderer::PropellerRenderer(std::string path,glm::vec3 axis, float length,bool tilt)
:m_propeller(0.1f,0.1f,length,36,1)
{
    m_shader.use();
    m_propeller.buildVertices();
    m_propeller.bind();
    m_Texture.LoadTexture(IO_Util::concat(path).c_str());
    model = glm::mat4(1.0f);
    rotationAxis = axis;
    tilted = tilt;
}

void PropellerRenderer::render(Camera &camera) { 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    GLCall(glDepthFunc(GL_LESS));
    
    m_shader.use();
    m_shader.SetProjectionMatrix(camera.getProjMatrix());
    m_shader.SetViewMatrix(camera.getViewMatrix());
    if(tilted)
    {
        model = glm::rotate(model, glm::radians(90.0f),rotationAxis);
        model = glm::rotate(model, PROPELLER_SPEED, glm::vec3(0,1,0));
        model = glm::translate(model, glm::vec3(0,0,0));
    } else {
        model = glm::rotate(model, PROPELLER_SPEED,rotationAxis);
        model = glm::translate(model, glm::vec3(0,5.0f,0));
    }

    m_shader.SetModelMatrix(model);
    
    m_propeller.bindVAO();
    m_Texture.Bind2DTexture();
    GLCall(glDrawElements(GL_TRIANGLES,m_propeller.getIndicesCount(),GL_UNSIGNED_INT,0));

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glDisableVertexAttribArray(0);
    glDisable(GL_CULL_FACE);
}

void PropellerRenderer::setLocation(glm::mat4 location) { 
    model = location;
}

