#pragma once

#include "DrawableGameComponent.h"
#include "BasicEffect.h"

namespace Library
{
	class Mesh;
}

using namespace Library;

namespace Rendering
{
	class ModelDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(ModelDemo, DrawableGameComponent)

	public:		
		ModelDemo(Game& game, Camera& camera);
		~ModelDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeColor = 1
		};

		ModelDemo();
		ModelDemo(const ModelDemo& rhs);
		ModelDemo& operator=(const ModelDemo& rhs);

		void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
	};
}
