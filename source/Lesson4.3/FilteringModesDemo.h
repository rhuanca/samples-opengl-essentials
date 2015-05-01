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
	class FilteringModesDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(FilteringModesDemo, DrawableGameComponent)

	public:		
		FilteringModesDemo(Game& game, Camera& camera);
		~FilteringModesDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeTextureCoordinate = 1
		};

		enum FilteringMode
		{
			FilteringModePoint = 0,
			FilteringModeLinear,
			FilteringModePointMipMapPoint,
			FilteringModeLinearMipMapPoint,
			FilteringModePointMipMapLinear,
			FilteringModeTriLinear,
			FilteringModeEnd
		};

		static const std::string FilteringModeNames[];

		FilteringModesDemo();
		FilteringModesDemo(const FilteringModesDemo& rhs);
		FilteringModesDemo& operator=(const FilteringModesDemo& rhs);

		void CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& vertexBuffer);
		void CreateIndexBuffer(UINT* indices, GLuint indexCount, GLuint& indexBuffer);
		void OnKey(int key, int scancode, int action, int mods);
		void OutputFilteringMode();

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		GLint mWorldViewProjectionLocation;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		std::vector<GLuint> mTextureSamplers;
		std::map<FilteringMode, GLuint> mTextureSamplersByFilteringMode;
		FilteringMode mActiveFilteringMode;
		Game::KeyboardHandler mKeyboardHandler;
	};
}
