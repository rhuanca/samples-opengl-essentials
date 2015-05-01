#pragma once

#include "DrawableGameComponent.h"
#include "BlinnPhongEffect.h"

namespace Library
{
	class Light;
	class DirectionalLight;
	class ProxyModel;
}

using namespace Library;

namespace Rendering
{
	class BlinnPhongDemo : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(BlinnPhongDemo, DrawableGameComponent)

	public:		
		BlinnPhongDemo(Game& game, Camera& camera);
		~BlinnPhongDemo();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		BlinnPhongDemo();
		BlinnPhongDemo(const BlinnPhongDemo& rhs);
		BlinnPhongDemo& operator=(const BlinnPhongDemo& rhs);

		void UpdateAmbientLight(const GameTime& gameTime);
		void UpdateDirectionalLight(const GameTime& gameTime);
		void UpdateSpecularLight(const GameTime& gameTime);

		static const glm::vec2 LightRotationRate;
		static const float LightModulationRate;

		BlinnPhongEffect mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		glm::mat4 mWorldMatrix;
		GLuint mIndexCount;
		GLuint mColorTexture;
		Light* mAmbientLight;
		DirectionalLight* mDirectionalLight;
		glm::vec4 mSpecularColor;
		float mSpecularPower;

		ProxyModel* mProxyModel;
	};
}
