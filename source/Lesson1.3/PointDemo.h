#pragma once

#include "DrawableGameComponent.h"

using namespace Library;

namespace Rendering
{
	class PointDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(PointDemo, DrawableGameComponent)

	public:		
		PointDemo(Game& game, Camera& camera);
		~PointDemo();

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		PointDemo();
		PointDemo(const PointDemo& rhs);
		PointDemo& operator=(const PointDemo& rhs);

		GLuint mShaderProgram;
		GLuint mVertexArrayObject;
	};
}
