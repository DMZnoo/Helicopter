//
//  SkyShader.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 2/05/20.
//

#include "SkyShader.hpp"


SkyShader::SkyShader()
: Shader()
{
    Shader::LoadShaders("GLSL/SkyVertexShader.glsl", "GLSL/SkyFragmentShader.glsl");
};

void SkyShader::SetProjectionMatrix(glm::mat4 proj) { 
    Shader::setMat4("projectionMatrix",proj);
};

void SkyShader::SetViewMatrix(glm::mat4 view) { 
    Shader::setMat4("viewMatrix",view);
};
