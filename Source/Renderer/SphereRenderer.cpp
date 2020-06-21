//
//  SphereRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 18/05/20.
//

#include "SphereRenderer.hpp"


SphereRenderer::SphereRenderer(std::string path,glm::vec3 axis, float speed)
:m_sphere(0.1f,36,18)
{
    m_shader.use();
    m_sphere.buildVertices();
    m_sphere.bind();
    m_sphereTexture.LoadTexture(IO_Util::concat(path).c_str());
    model = glm::mat4(1.f);
    rotate = 0.f;
    rotationAxis = axis;
    rotationSpeed = speed;
}

void SphereRenderer::render(Camera &camera) { 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    GLCall(glDepthFunc(GL_LESS));
    m_shader.use();
    m_shader.SetProjectionMatrix(camera.getProjMatrix());
    m_shader.SetViewMatrix(camera.getViewMatrix());
    model = glm::mat4(1.f);
    model = glm::rotate(model,glm::radians(rotate+=rotationSpeed), rotationAxis);
    if(rotationAxis == glm::vec3(1,0,0))
        model = glm::translate(model, glm::vec3(0,0,2));
    else
        model = glm::translate(model, glm::vec3(2,0,0));
    
    m_shader.SetModelMatrix(model);
    m_sphere.bindVAO();
    m_sphereTexture.Bind2DTexture();
    GLCall(glDrawElements(GL_TRIANGLES,m_sphere.getIndicesCount(),GL_UNSIGNED_INT,0));

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glDisableVertexAttribArray(0);
    glDisable(GL_CULL_FACE);
    
}
