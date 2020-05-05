//
//  CubeShader.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 2/05/20.
//

#include "CubeShader.hpp"


CubeShader::CubeShader()
: Shader()
{
    Shader::LoadShaders("GLSL/CubeVertexShader.glsl", "GLSL/CubeFragmentShader.glsl");
};

void CubeShader::SetProjectionMatrix(glm::mat4 proj) { 
    Shader::setMat4("projection",proj);
};

void CubeShader::SetViewMatrix(glm::mat4 view) { 
    Shader::setMat4("view",view);
};

void CubeShader::SetModelMatrix() { 
    Shader::setMat4("model",glm::mat4(1.0));
};
