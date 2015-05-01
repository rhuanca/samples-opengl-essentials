#pragma once

#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"

namespace Library
{
	class SkyboxEffect : public ShaderProgram
    {
		RTTI_DECLARATIONS(SkyboxEffect, ShaderProgram)

        SHADER_VARIABLE_DECLARATION(WorldViewProjection)

    public:
        SkyboxEffect();
		SkyboxEffect(const SkyboxEffect& rhs);
		SkyboxEffect& operator=(const SkyboxEffect& rhs);

		virtual void Initialize(GLuint vertexArrayObject) override;
		virtual void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer) const override;
		void CreateVertexBuffer(VertexPosition* vertices, UINT vertexCount, GLuint& vertexBuffer) const;
		virtual UINT VertexSize() const override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
		};
    };
}