#pragma once

#include "DrawableGameComponent.h"
#include "PointLightEffect.h"

namespace Library
{
	class Light;
	class PointLight;
	class ProxyModel;
}

using namespace Library;

namespace Rendering
{
	class PointLightDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(PointLightDemo, DrawableGameComponent)

	public:		
		PointLightDemo(Game& game, Camera& camera);
		~PointLightDemo();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		PointLightDemo();
		PointLightDemo(const PointLightDemo& rhs);
		PointLightDemo& operator=(const PointLightDemo& rhs);

		void UpdateAmbientLight(const GameTime& gameTime);
		void UpdatePointLight(const GameTime& gameTime);
		void UpdateSpecularLight(const GameTime& gameTime);

		static const float LightModulationRate;
		static const float LightMovementRate;
		static const float RadiusModulationRate;

		PointLightEffect mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		Light* mAmbientLight;
		PointLight* mPointLight;
		glm::vec4 mSpecularColor;
		float mSpecularPower;

		ProxyModel* mProxyModel;
	};
}
