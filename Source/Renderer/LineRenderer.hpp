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
#include "../Model/Model.hpp"
class LineRenderer {
  public:
    LineRenderer(float length,float radius);
    
    void render( Camera &camera);

  private:
    Model m_line;
    CubeShader m_shader;
    
};

#endif /* LineRenderer_hpp */
