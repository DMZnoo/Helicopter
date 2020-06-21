//
//  SkyShader.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 2/05/20.
//

#ifndef SkyShader_hpp
#define SkyShader_hpp
#include "Shader.hpp"
class SkyShader : public Shader
{
public:
    SkyShader();
    void SetProjectionMatrix(glm::mat4 proj);
    void SetViewMatrix(glm::mat4 view);
};


#endif /* SkyShader_hpp */
