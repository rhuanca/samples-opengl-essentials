#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"

using namespace Library;

namespace Rendering
{
	class ColoredTriangleDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(ColoredTriangleDemo, DrawableGameComponent)

	public:		
		ColoredTriangleDemo(Game& game, Camera& camera);
		~ColoredTriangleDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeColor = 1
		};

		ColoredTriangleDemo();
		ColoredTriangleDemo(const ColoredTriangleDemo& rhs);
		ColoredTriangleDemo& operator=(const ColoredTriangleDemo& rhs);

		ShaderProgram mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
	};
}
