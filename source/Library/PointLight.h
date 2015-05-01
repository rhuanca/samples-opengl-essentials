#pragma once

#include "Common.h"
#include "Light.h"

namespace Library
{
	class PointLight : public Light
	{
		RTTI_DECLARATIONS(PointLight, Light)

	public:
		PointLight(Game& game);
		virtual ~PointLight();

		const glm::vec3& Position() const;
		FLOAT Radius() const;

		virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
        virtual void SetPosition(const glm::vec3& position);
		virtual void SetRadius(float value);

		static const float DefaultRadius;

	protected:
		glm::vec3 mPosition;
		float mRadius;
	};
}

