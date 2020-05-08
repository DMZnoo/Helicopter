//
//  Model.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 28/04/20.
//

#ifndef Model_hpp
#define Model_hpp

#include "Mesh.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Utility/NonCopyable.hpp"
#include "../Renderer/RendererInfo.hpp"
#include "../Debugger.hpp"
#include "../Texture/BaseTexture.hpp"
#include "../Utility/IO_Util.hpp"
#include <map>
#include <GL/glew.h>
#include <vector>



extern const float PI;
class Model : public NonCopyable {
  public:
    
    Model() = default;
    void loadModel(char const*model);
    Model(Model &&other);
    Model &operator=(Model &&other);
    void drop();
    void genVAO();
    void genVBO();
    void genIBO();
    void addIBO(const std::vector<GLuint> &indices);
    void addVBO(int dimensions, unsigned int stride,const std::vector<GLfloat> &data);
    void addAttribArray(int dimensions, unsigned int stride);
    void bindVAO() const;
    void bindVBO() const;
    void bindIBO() const;
    const std::vector<Mesh>& getModelInfo();
    unsigned int getIndicesCount() const;
    void assembleModel(aiNode *node, const aiScene *scene);
    void bindMesh(Mesh* mesh);
    const RenderInfo &getRendererInfo() const;
    virtual ~Model();

  private:
    RenderInfo m_renderInfo;
    int m_dim;
    int m_vboCount = 0;
    std::vector<GLuint> m_buffers;
    std::vector<Mesh> modelInfo;
    Mesh m_mesh;
    BaseTexture m_texture;
    std::string objpath;
};

#endif /* Model_hpp */
