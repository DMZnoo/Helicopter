//
//  SkyTexture.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 2/05/20.
//

#include "SkyTexture.hpp"

void SkyTexture::LoadCubeMap(std::vector<std::string> sides) {
    GLCall(glGenTextures(1,&textID));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textID));
    stbi_set_flip_vertically_on_load(false);
    for(unsigned int i = 0; i < 6; i++)
        {
            unsigned char *data = stbi_load(sides[i].c_str(), &width, &height, &number_of_components, 0);
            if(data)
                {
                    GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
                    stbi_image_free(data);
                }
            else
                {
                    std::cout << "Cubemap failed at load, Path: " << sides[i] << std::endl;
                    stbi_image_free(data);
                }
            
        }
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    
};



void SkyTexture::BindCubeMapTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
};



SkyTexture::~SkyTexture() {
    
}
