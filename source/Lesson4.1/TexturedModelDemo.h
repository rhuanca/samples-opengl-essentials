#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"
#include "Game.h"

namespace Library
{
	class Mesh;
}

using namespace Library;

namespace Rendering
{
	class TexturedModelDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(TexturedModelDemo, DrawableGameComponent)

	public:		
		TexturedModelDemo(Game& game, Camera& camera);
		~TexturedModelDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeTextureCoordinate = 1
		};

		TexturedModelDemo();
		TexturedModelDemo(const TexturedModelDemo& rhs);
		TexturedModelDemo& operator=(const TexturedModelDemo& rhs);

		void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
		void OnKey(int key, int scancode, int action, int mods);

		Game::KeyboardHandler mKeyboardHandler;

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		GLuint mAltTexture;
		GLuint mActiveTexture;
	};
}
