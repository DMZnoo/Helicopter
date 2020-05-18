//
//  ModelShader.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#include "ModelShader.hpp"
ModelShader::ModelShader()
: Shader()
{
    Shader::LoadShaders("GLSL/ModelVertexShader.glsl", "GLSL/ModelFragmentShader.glsl");
};

void ModelShader::SetProjectionMatrix(glm::mat4 proj) {
    Shader::setMat4("projection",proj);
};

void ModelShader::SetViewMatrix(glm::mat4 view) {
    Shader::setMat4("view",view);
};

void ModelShader::SetModelMatrix(glm::mat4 model) {
    Shader::setMat4("model",model);
};


