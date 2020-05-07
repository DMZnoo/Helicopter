//
//  LineRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 5/05/20.
//

#include "LineRenderer.hpp"
LineRenderer::LineRenderer(std::string path,unsigned int direction)
:m_line(0.01f,0.01f,30.0f,36,1)
{
    m_shader.use();
    m_line.buildVertices();
    m_line.bind();
    m_lineTexture.LoadTexture(IO_Util::concat(path).c_str());
    xyz = direction;
    val = 0.0f;
}

void LineRenderer::render(Camera &camera)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    GLCall(glDepthFunc(GL_LESS));
    m_shader.use();
    m_shader.SetProjectionMatrix(camera.getProjMatrix());
    m_shader.SetViewMatrix(camera.getViewMatrix());
//    val += 0.05f;
    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(val,0,0));

    if (xyz == 0)
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1,0,0));
    else if (xyz == 1)
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0,1,0));
    else
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0,0,1));
    
    
    m_shader.SetModelMatrix(model);
    
    m_line.bindVAO();
    m_lineTexture.Bind2DTexture();
    GLCall(glDrawElements(GL_TRIANGLES,m_line.getIndicesCount(),GL_UNSIGNED_INT,0));

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glDisableVertexAttribArray(0);
    glDisable(GL_CULL_FACE);
}
