#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"

namespace Library
{
	class Mesh;
	class Light;
	class DirectionalLight;
	class ProxyModel;
}

using namespace Library;

namespace Rendering
{
	class DiffuseLightingDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(DiffuseLightingDemo, DrawableGameComponent)

	public:		
		DiffuseLightingDemo(Game& game, Camera& camera);
		~DiffuseLightingDemo();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeTextureCoordinate = 1,
			VertexAttributeNormal = 2
		};

		DiffuseLightingDemo();
		DiffuseLightingDemo(const DiffuseLightingDemo& rhs);
		DiffuseLightingDemo& operator=(const DiffuseLightingDemo& rhs);

		void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
		void UpdateAmbientLight(const GameTime& gameTime);
		void UpdateDirectionalLight(const GameTime& gameTime);

		static const glm::vec2 LightRotationRate;

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		GLint mWorldLocation;
		GLint mAmbientColorLocation;
		GLint mLightColorLocation;
		GLint mLightDirectionLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		Light* mAmbientLight;
		DirectionalLight* mDirectionalLight;

		ProxyModel* mProxyModel;
	};
}
