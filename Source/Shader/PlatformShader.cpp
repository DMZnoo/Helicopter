//
//  PlatformShader.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#include "PlatformShader.hpp"
PlatformShader::PlatformShader()
: Shader()
{
    Shader::LoadShaders("GLSL/PlatformVertexShader.glsl", "GLSL/PlatformFragmentShader.glsl");
};

void PlatformShader::SetProjectionMatrix(glm::mat4 proj) {
    Shader::setMat4("projection",proj);
};

void PlatformShader::SetViewMatrix(glm::mat4 view) {
    Shader::setMat4("view",view);
};

void PlatformShader::SetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 0.2f, 1.0f));    // it's a bit too big for our scene, so scale it down
    Shader::setMat4("model",model);
};


