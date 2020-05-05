#include "Model.hpp"

void Model::loadModel(char const* path)
{
   //this constructor is used when we have a model to load. Otherwise default is called
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene -> mRootNode)
    {
        std::cout << "Assimp Error: " << importer.GetErrorString() << std::endl;
        throw std::exception();
    }
    
    assembleModel(scene->mRootNode, scene);
    
}

void Model::assembleModel(aiNode *node, const aiScene *scene)
{
    for (unsigned int n = 0; n < node->mNumMeshes; n++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];
        for(unsigned int x = 0; x < mesh->mNumVertices; x++)
        {
            Vertex vertex;
            glm::vec3 coor;
            
            coor.x = mesh->mVertices[x].x;
            coor.y = mesh->mVertices[x].y;
            coor.z = mesh->mVertices[x].z;
            vertex.Position = coor;
            
            coor.x = mesh->mNormals[x].x;
            coor.y = mesh->mNormals[x].y;
            coor.z = mesh->mNormals[x].z;
            vertex.Normal = coor;
            
            if(mesh->mTextureCoords[0])
            {
                glm::vec2 texCoords;
                
                texCoords.x = mesh->mTextureCoords[0][x].x;
                texCoords.y = mesh->mTextureCoords[0][x].y;
                vertex.TexCoords = texCoords;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f,0.0f);
            
            coor.x = mesh->mTangents[x].x;
            coor.y = mesh->mTangents[x].y;
            coor.z = mesh->mTangents[x].z;
            vertex.Tangent = coor;
            
            coor.x = mesh->mBitangents[x].x;
            coor.y = mesh->mBitangents[x].y;
            coor.z = mesh->mBitangents[x].z;
            vertex.Bitangent = coor;
            m_mesh.vertices.push_back(vertex);
        }
        
        for(unsigned int y = 0; y < mesh -> mNumFaces; y++)
        {
            aiFace face = mesh -> mFaces[y];
            for(unsigned int z = 0; z < face.mNumIndices; z++)
            {
                m_mesh.indices.push_back(face.mIndices[z]);
            }
        }
        
        aiMaterial* material = scene -> mMaterials[mesh->mMaterialIndex];
        std::unordered_map<std::string, aiTextureType> materialTexture;
        materialTexture["texture_diffuse"] = aiTextureType_DIFFUSE;
        materialTexture["texture_specular"] = aiTextureType_SPECULAR;
        materialTexture["texture_normal"] = aiTextureType_HEIGHT;
        materialTexture["texture_height"] = aiTextureType_AMBIENT;
        for(auto it = materialTexture.begin(); it != materialTexture.end(); it++)
        {
            for(unsigned int a = 0; a < material -> GetTextureCount(it->second);a++)
            {
                aiString path;
                material -> GetTexture(it->second, a, &path);
                Texture texture;
                char* c = const_cast<char*>(IO_Util::concat("/obj/"+std::string(path.C_Str())).c_str());
                texture.textID = m_texture.LoadTexture(c);
                texture.type = it->first;
                m_mesh.textures.push_back(texture);
            }
            std::cout << material -> GetTextureCount(it->second) << std::endl;
        }
        modelInfo.push_back(m_mesh);
        bindMesh(&m_mesh);
    }
    
    for(unsigned int i = 0; i < node -> mNumChildren; i++)
    {
        assembleModel(node->mChildren[i], scene);
    }
}

void Model::bindMesh(Mesh* mesh)
{
    genVAO();
    genVBO();
    genIBO();
    bindVAO();
    bindVBO();
    GLCall(glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), mesh->vertices.data(), GL_STATIC_DRAW));
    addIBO(mesh->indices);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
    
    
    
}




const std::vector<Mesh> &Model::getModelInfo()
{
    return modelInfo;
}


Model::~Model()
{
    drop();
}

Model::Model(Model &&other)
    : m_renderInfo(other.m_renderInfo)
    , m_vboCount(other.m_vboCount)
    , m_buffers(std::move(other.m_buffers))
{
    other.m_renderInfo.reset();
    other.m_vboCount = 0;
}

Model &Model::operator=(Model &&other)
{
    m_renderInfo = other.m_renderInfo;
    m_vboCount = other.m_vboCount;
    m_buffers = std::move(other.m_buffers);

    other.m_renderInfo.reset();
    other.m_vboCount = 0;

    return *this;
}

void Model::genVAO()
{
//    if (m_renderInfo.vao != 0)
//        drop();

    GLCall(glGenVertexArrays(1, &m_renderInfo.vao));
    
}

void Model::genVBO()
{
//    if(m_renderInfo.vbo != 0)
//        drop();
    GLCall(glGenBuffers(1, &m_renderInfo.vbo));
}

void Model::genIBO()
{
//    if(m_renderInfo.ibo != 0)
//        drop();
    GLCall(glGenBuffers(1, &m_renderInfo.ibo));
}

void Model::bindVAO() const
{
    GLCall(glBindVertexArray(m_renderInfo.vao));
}

void Model::bindVBO() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderInfo.vbo));
}

void Model::bindIBO() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderInfo.ibo));
}



void Model::addVBO(int dimensions,unsigned int stride, const std::vector<GLfloat> &data)
{

    genVBO();
    bindVBO();
    m_dim = dimensions;
    
    GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(),
                 GL_STATIC_DRAW));
    GLCall(glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount)));
    GLCall(glVertexAttribPointer(static_cast<GLuint>(m_vboCount++), m_dim, GL_FLOAT,
                          GL_FALSE, stride*sizeof(float), (GLvoid *)0));
    m_buffers.push_back(m_renderInfo.vbo);
}

void Model::addAttribArray(int dimensions, unsigned int stride)
{
    
    GLCall(glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount)));
    GLCall(glVertexAttribPointer(static_cast<GLuint>(m_vboCount++), dimensions, GL_FLOAT,GL_FALSE, stride*sizeof(float), (void*)(m_dim * sizeof(float))));
    m_dim = dimensions;
    
}

void Model::addIBO(const std::vector<GLuint> &indices)
{
    genIBO();
    m_renderInfo.indicesCount = static_cast<GLuint>(indices.size());
    bindIBO();
    
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                        indices.data(), GL_STATIC_DRAW));
}

void Model::drop()
{
    if (m_renderInfo.vao)
        GLCall(glDeleteVertexArrays(1, &m_renderInfo.vao));
    if (m_buffers.size() > 0)
        GLCall(glDeleteBuffers(static_cast<GLsizei>(m_buffers.size()),
                               m_buffers.data()));

    m_buffers.clear();

    m_vboCount = 0;
    m_renderInfo.reset();
}

int Model::getIndicesCount() const
{
    return m_renderInfo.indicesCount;
}

const RenderInfo &Model::getRendererInfo() const
{
    return m_renderInfo;
}
