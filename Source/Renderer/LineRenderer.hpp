//
//  LineRenderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 5/05/20.
//

#ifndef LineRenderer_hpp
#define LineRenderer_hpp

#include "../Shader/CubeShader.hpp"
#include "../Control/Camera.hpp"
#include "../Model/CylinderModel.hpp"
class LineRenderer {
  public:
    LineRenderer(std::string path,unsigned int direction);
    
    void render( Camera &camera);

  private:
    CylinderModel m_line;
    CubeShader m_shader;
    BaseTexture m_lineTexture;
    unsigned int xyz;
    float val;
};

#endif /* LineRenderer_hpp */
