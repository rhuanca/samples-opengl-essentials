#pragma once

#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"

namespace Library
{
	class BasicEffect : public ShaderProgram
    {
		RTTI_DECLARATIONS(BasicEffect, ShaderProgram)

        SHADER_VARIABLE_DECLARATION(WorldViewProjection)

    public:
        BasicEffect();
		BasicEffect(const BasicEffect& rhs);
		BasicEffect& operator=(const BasicEffect& rhs);

		virtual void Initialize(GLuint vertexArrayObject) override;
		virtual void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer) const override;
		void CreateVertexBuffer(VertexPositionColor* vertices, UINT vertexCount, GLuint& vertexBuffer) const;
		virtual UINT VertexSize() const override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
			VertexAttributeColor = 1
		};
    };
}