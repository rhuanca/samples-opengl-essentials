#pragma once

#include "Common.h"
#include "DrawableGameComponent.h"
#include "BasicEffect.h"

namespace Library
{
	class Grid : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(Grid, DrawableGameComponent)

	public:
		Grid(Game& game, Camera& camera);
		Grid(Game& game, Camera& camera, GLuint size, GLuint scale, const glm::vec4& color);
		~Grid();

		const glm::vec3& Position() const;
		const glm::vec4& Color() const;
		const GLuint Size() const;
		const GLuint Scale() const;

		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		void SetColor(const glm::vec4& color);
		void SetSize(GLuint size);
		void SetScale(GLuint scale);

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		Grid();
		Grid(const Grid& rhs);
		Grid& operator=(const Grid& rhs);
		
		void InitializeGrid();

		static const GLuint DefaultSize;
		static const GLuint DefaultScale;
		static const glm::vec4 DefaultColor;

		BasicEffect mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
	
		glm::vec3 mPosition;
		GLuint mSize;
		GLuint mScale;
		glm::vec4 mColor;
		glm::mat4 mWorldMatrix;
		UINT mVertexCount;
	};
}