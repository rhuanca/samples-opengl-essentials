#pragma once

#include "Common.h"
#include "DrawableGameComponent.h"
#include "BasicEffect.h"

namespace Library
{
	class Mesh;

	class Skybox : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(Skybox, DrawableGameComponent)

	public:
		Skybox(Game& game, Camera& camera, const std::string& posXFilename, const std::string& negXFilename, const std::string& posYFilename, const std::string& negYFilename, const std::string& posZFilename, const std::string& negZFilename, float scale);
		~Skybox();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;		
		virtual void Draw(const GameTime& gameTime) override;

	private:
		Skybox();
		Skybox(const Skybox& rhs);
		Skybox& operator=(const Skybox& rhs);

		std::string mPosXFilename;
		std::string mNegXFilename;
		std::string mPosYFilename;
		std::string mNegYFilename;
		std::string mPosZFilename;
		std::string mNegZFilename;

		BasicEffect mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		UINT mIndexCount;
		GLuint mSkyboxTexture;
		glm::mat4 mWorldMatrix;
		glm::mat4 mScaleMatrix;
		GLuint mSkyboxTextureSampler;
	};
}