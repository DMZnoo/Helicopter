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

void PlatformShader::SetModelMatrix(glm::mat4 model) {
    Shader::setMat4("model",model);
};


