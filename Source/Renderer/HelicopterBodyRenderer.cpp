//
//  HelicopterBodyRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 9/05/20.
//

#include "HelicopterBodyRenderer.hpp"
extern std::string ROOT;
HelicopterBodyRenderer::HelicopterBodyRenderer(std::string path)
:player_1(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0,0,1))
{
    
    m_helicopter.loadModel(IO_Util::concat(path.c_str()).c_str());
    m_shader.use();
    model = glm::mat4(1.0f);
    modelHeight = m_helicopter.getModelHeight();
    m_Texture.LoadTexture(IO_Util::concat("helicopter/helicopter.jpg").c_str());
    direction = glm::vec3(0,0,1);
};

void HelicopterBodyRenderer::render(Camera &camera) {
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    GLCall(glDepthFunc(GL_LESS));
    m_shader.use();
    m_shader.SetProjectionMatrix(camera.getProjMatrix());
    if(LOCK_ON_OBJECT)
        player_1.updateView(camera);
    m_shader.SetViewMatrix(camera.getViewMatrix());
    model = glm::mat4(1.0f);
    glDisable(GL_CULL_FACE);
    model = glm::scale(model, glm::vec3(0.5f));
    model = player_1.update(model);
    m_shader.SetModelMatrix(model);
    
    for(unsigned int i = 0; i < m_helicopter.getModelInfo().size(); i++)
    {
        m_Texture.Bind2DTexture();
        GLCall(glBindVertexArray(m_helicopter.getRendererInfo().vao_list[i]));
        GLCall(glDrawElements(GL_TRIANGLES,m_helicopter.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
        glDisable(GL_CULL_FACE);
        glBindVertexArray(0);
    }
};
    glm::mat4 HelicopterBodyRenderer::transferLocation() {
        return model;
    }
