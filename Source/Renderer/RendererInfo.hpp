//
//  RendererInfo.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 29/04/20.
//

#ifndef RendererInfo_hpp
#define RendererInfo_hpp

struct RenderInfo {
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ibo = 0;
    unsigned int indicesCount = 0;

    inline void reset()
    {
        vao = 0;
        vbo = 0;
        ibo = 0;
        indicesCount = 0;
    }
};

#endif /* RendererInfo_hpp */
