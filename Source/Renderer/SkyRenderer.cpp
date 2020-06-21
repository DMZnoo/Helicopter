//
//  SkyRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 29/04/20.
//

#include "SkyRenderer.hpp"


SkyboxRenderer::SkyboxRenderer() {
    float vertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    std::copy(&vertices[0], &vertices[108], std::back_inserter(skyboxVertices));
    m_skyCube.genVAO();
    m_skyCube.bindVAO();
    m_skyCube.addVBO(3,3, skyboxVertices);
    skyFaces.reserve(6);
    skyFaces.push_back(IO_Util::concat("right.jpg").c_str());
    skyFaces.push_back(IO_Util::concat("left.jpg").c_str());
    skyFaces.push_back(IO_Util::concat("top.jpg").c_str());
    skyFaces.push_back(IO_Util::concat("bottom.jpg").c_str());
    skyFaces.push_back(IO_Util::concat("front.jpg").c_str());
    skyFaces.push_back(IO_Util::concat("back.jpg").c_str());
//    std::cout <<faces[0] << std::endl;
//    std::cout << skyFaces.size() << std::endl;
//    for(int i = 0; i < sizeof(faces);i++)
//        skyFaces[i] = faces[i];
    m_skyTexture.LoadCubeMap(skyFaces);
    m_shader.use();
    m_shader.setInt("skybox", 0);
    
    
    
}

void SkyboxRenderer::render(Camera &camera) {
    m_skyCube.bindVAO();
    m_skyCube.bindVBO();
    GLCall(glDepthFunc(GL_LEQUAL));
//    glEnable(GL_CULL_FACE);
//    glFrontFace(GL_CCW);
    m_shader.use();
    glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
    m_shader.setMat4("viewMatrix", view);
    m_shader.setMat4("projectionMatrix", camera.getProjMatrix());
    m_skyCube.bindVAO();
    m_skyTexture.BindCubeMapTexture();

    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    GLCall(glDepthFunc(GL_LESS));
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    
};
