#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"

namespace Library
{
	class Mesh;
	class Light;
}

using namespace Library;

namespace Rendering
{
	class AmbientLightingDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(AmbientLightingDemo, DrawableGameComponent)

	public:		
		AmbientLightingDemo(Game& game, Camera& camera);
		~AmbientLightingDemo();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeTextureCoordinate = 1
		};

		AmbientLightingDemo();
		AmbientLightingDemo(const AmbientLightingDemo& rhs);
		AmbientLightingDemo& operator=(const AmbientLightingDemo& rhs);

		void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
		void UpdateAmbientLight(const GameTime& gameTime);

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		GLint mAmbientColorLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		Light* mAmbientLight;
	};
}
