//
//  PlatformShader.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#ifndef PlatformShader_hpp
#define PlatformShader_hpp
#include "Shader.hpp"
class PlatformShader : public Shader
{
public:
    PlatformShader();
    void SetProjectionMatrix(glm::mat4 proj);
    void SetViewMatrix(glm::mat4 view);
    void SetModelMatrix(glm::mat4 model);
};


#endif /* PlatformShader_hpp */
