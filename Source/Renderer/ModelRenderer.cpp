//
//  PlatformRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#include "ModelRenderer.hpp"
extern std::string ROOT;
ModelRenderer::ModelRenderer(std::string path, std::string type) {
    
    m_platform.loadModel(IO_Util::concat(path.c_str()).c_str());
    m_shader.use();
    this->typeModel = type;
    model = glm::mat4(1.0f);
};

void ModelRenderer::render(Camera &camera) { 
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    GLCall(glDepthFunc(GL_LESS));
    m_shader.use();
    m_shader.SetProjectionMatrix(camera.getProjMatrix());
    m_shader.SetViewMatrix(camera.getViewMatrix());
    
    if(typeModel == "platform")
    {

        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.2f, 1.0f));
    } else if (typeModel == "nanosuit")
    {
        glDisable(GL_CULL_FACE);
        model = glm::scale(model, glm::vec3(0.3f));
    }

    m_shader.SetModelMatrix(model);
    
    for(unsigned int i = 0; i < m_platform.getModelInfo().size(); i++)
    {
        
        diffuse_n = 1;specular_n = 1; normal_n = 1; height_n = 1;
        for(unsigned int n = 0; n < m_platform.getModelInfo()[i].textures.size();n++)
        {
            GLCall(glActiveTexture(GL_TEXTURE0 + n));
            std::string num;
            std::string type = m_platform.getModelInfo()[i].textures[n].type;
            if(type == "texture_diffuse")
                num = std::to_string(diffuse_n++);
            else if (type == "texture_specular")
                num = std::to_string(specular_n++);
            else if (type == "texture_normal")
                num = std::to_string(normal_n++);
            else
                num = std::to_string(height_n++);
            m_shader.setInt((type+num).c_str(),i);
            
            glBindTexture(GL_TEXTURE_2D,m_platform.getModelInfo()[i].textures[n].textID);
            
        }
        GLCall(glBindVertexArray(m_platform.getRendererInfo().vao_list[i]));
        GLCall(glDrawElements(GL_TRIANGLES,m_platform.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
        glDisable(GL_CULL_FACE);
        glBindVertexArray(0);
    }

    
    
};
void ModelRenderer::setLocation(glm::mat4 location) {
   
    model = location;
}
