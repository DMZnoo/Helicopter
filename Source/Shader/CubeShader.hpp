//
//  CubeShader.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 2/05/20.
//

#ifndef CubeShader_hpp
#define CubeShader_hpp
#include "Shader.hpp"
class CubeShader : public Shader
{
public:
    CubeShader();
    void SetProjectionMatrix(glm::mat4 proj);
    void SetViewMatrix(glm::mat4 view);
    void SetModelMatrix(glm::mat4 model);
};

#endif /* CubeShader_hpp */
