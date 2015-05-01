#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"
#include "Game.h"

namespace Library
{
	class Mesh;
}

using namespace Library;

namespace Rendering
{
	class WrappingModesDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(WrappingModesDemo, DrawableGameComponent)

	public:		
		WrappingModesDemo(Game& game, Camera& camera);
		~WrappingModesDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeTextureCoordinate = 1
		};

		enum WrappingMode
		{
			WrappingModeRepeat = 0,
			WrappingModeMirroredRepeat,
			WrappingModeClampToEdge,
			WrappingModeClampToBorder,
			WrappingModeEnd
		};

		WrappingModesDemo();
		WrappingModesDemo(const WrappingModesDemo& rhs);
		WrappingModesDemo& operator=(const WrappingModesDemo& rhs);

		void CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& vertexBuffer);
		void CreateIndexBuffer(UINT* indices, GLuint indexCount, GLuint& indexBuffer);
		void OnKey(int key, int scancode, int action, int mods);

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		std::vector<GLuint> mTextureSamplers;
		std::map<WrappingMode, GLuint> mTextureSamplersByWrappingMode;
		WrappingMode mActiveWrappingMode;
		Game::KeyboardHandler mKeyboardHandler;
	};
}
