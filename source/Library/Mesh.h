#pragma once

#include "Common.h"

struct aiMesh;

namespace Library
{
    class Material;
    class ModelMaterial;

    class Mesh
    {
        friend class Model;

    public:
        ~Mesh();

        Model& GetModel();
        ModelMaterial* GetMaterial();
        const std::string& Name() const;

        const std::vector<glm::vec3>& Vertices() const;
        const std::vector<glm::vec3>& Normals() const;
        const std::vector<glm::vec3>& Tangents() const;
        const std::vector<glm::vec3>& BiNormals() const;
        const std::vector<std::vector<glm::vec3>*>& TextureCoordinates() const;
        const std::vector<std::vector<glm::vec4>*>& VertexColors() const;
        UINT FaceCount() const;
        const std::vector<UINT>& Indices() const;

        void CreateIndexBuffer(GLuint& indexBuffer);

    private:
        Mesh(Model& model, aiMesh& mesh);
        Mesh(const Mesh& rhs);
        Mesh& operator=(const Mesh& rhs);

        Model& mModel;
        ModelMaterial* mMaterial;
        std::string mName;
        std::vector<glm::vec3> mVertices;
        std::vector<glm::vec3> mNormals;
        std::vector<glm::vec3> mTangents;
        std::vector<glm::vec3> mBiNormals;
        std::vector<std::vector<glm::vec3>*> mTextureCoordinates;
        std::vector<std::vector<glm::vec4>*> mVertexColors;
        UINT mFaceCount;
        std::vector<UINT> mIndices;
    };
}