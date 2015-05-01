#pragma once

#include "Common.h"
#include "GameComponent.h"

namespace Library
{
	class Light : public GameComponent
	{
		RTTI_DECLARATIONS(Light, GameComponent)

	public:
		Light(Game& game);
		virtual ~Light();

		const glm::vec4& Color() const;
		void SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
		void SetColor(const glm::vec4& color);

	protected:
		glm::vec4 mColor;
	};
}

