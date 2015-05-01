#include "WrappingModesDemo.h"
#include "GameException.h"
#include "ColorHelper.h"
#include "Camera.h"
#include "Utility.h"
#include "ShaderProgram.h"
#include "VectorHelper.h"
#include "Model.h"
#include "Mesh.h"
#include "SOIL.h"

using namespace glm;

namespace Rendering
{
	RTTI_DEFINITIONS(WrappingModesDemo)

	WrappingModesDemo::WrappingModesDemo(Game& game, Camera& camera)
		: DrawableGameComponent(game, camera), mShaderProgram(), mVertexArrayObject(0), mVertexBuffer(0),
		mIndexBuffer(0), mWorldViewProjectionLocation(-1), mWorldMatrix(), mIndexCount(), mColorTexture(0),
		mTextureSamplers(), mTextureSamplersByWrappingMode(), mActiveWrappingMode(WrappingModeRepeat), mKeyboardHandler(nullptr)
	{
	}

	WrappingModesDemo::~WrappingModesDemo()
	{
		mGame->RemoveKeyboardHandler(mKeyboardHandler);
		glDeleteSamplers(mTextureSamplers.size(), &mTextureSamplers[0]);
		glDeleteTextures(1, &mColorTexture);
		glDeleteBuffers(1, &mIndexBuffer);
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteVertexArrays(1, &mVertexArrayObject);
	}

	void WrappingModesDemo::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		// Build the shader program
		std::vector<ShaderDefinition> shaders;
		shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, L"Content\\Effects\\WrappingModesDemo.vert"));
		shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER, L"Content\\Effects\\WrappingModesDemo.frag"));
		mShaderProgram.BuildProgram(shaders);
		
		float size = 10.0f;
		float halfSize = size / 2.0f;

		// Create the vertex buffer
		VertexPositionTexture vertices[] =
		{
			VertexPositionTexture(vec4(-halfSize, 1.0f, 0.0, 1.0f), vec2(0.0f, 3.0f)),
			VertexPositionTexture(vec4(-halfSize, size + 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
			VertexPositionTexture(vec4(halfSize, size + 1.0f, 0.0f, 1.0f), vec2(3.0f, 0.0f)),
			VertexPositionTexture(vec4(halfSize, 1.0f, 0.0f, 1.0f), vec2(3.0f, 3.0f))
		};

		CreateVertexBuffer(vertices, ARRAYSIZE(vertices), mVertexBuffer);

		// Create the index buffer
		UINT indices[] =
		{
			0, 2, 1,
			0, 3, 2
		};

		mIndexCount = ARRAYSIZE(indices);
		CreateIndexBuffer(indices, mIndexCount, mIndexBuffer);		
		
		// Find the WVP uniform location
		mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram.Program(), "WorldViewProjection");
		if (mWorldViewProjectionLocation == -1)
		{
			throw GameException("glGetUniformLocation() did not find uniform location.");
		}

		// Load the texture
		mColorTexture = SOIL_load_OGL_texture("Content\\Textures\\Cover.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB);
		if (mColorTexture == 0)
		{
			throw GameException("SOIL_load_OGL_texture() failed.");
		}

		// Configure the texture samplers
		mTextureSamplers.resize(WrappingModeEnd);
		glGenSamplers(mTextureSamplers.size(), &mTextureSamplers[0]);

		for (WrappingMode mode = (WrappingMode)0; mode < WrappingModeEnd; mode = (WrappingMode)(mode + 1))
		{
			mTextureSamplersByWrappingMode[mode] = mTextureSamplers[mode];
		}

		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeRepeat], GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeRepeat], GL_TEXTURE_WRAP_T, GL_REPEAT);

		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeMirroredRepeat], GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeMirroredRepeat], GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToEdge], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToEdge], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToBorder], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToBorder], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glSamplerParameterfv(mTextureSamplersByWrappingMode[WrappingModeClampToBorder], GL_TEXTURE_BORDER_COLOR, &ColorHelper::Purple[0]);

		// Create the vertex array object
		glGenVertexArrays(1, &mVertexArrayObject);
		glBindVertexArray(mVertexArrayObject);

		glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)offsetof(VertexPositionTexture, Position));
		glEnableVertexAttribArray(VertexAttributePosition);

		glVertexAttribPointer(VertexAttributeTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)offsetof(VertexPositionTexture, TextureCoordinates));
		glEnableVertexAttribArray(VertexAttributeTextureCoordinate);

		glBindVertexArray(0);

		// Attach the keyboard handler
		using namespace std::placeholders;
		mKeyboardHandler = std::bind(&WrappingModesDemo::OnKey, this, _1, _2, _3, _4);
		mGame->AddKeyboardHandler(mKeyboardHandler);
	}

	void WrappingModesDemo::Draw(const GameTime& gameTime)
	{
		glBindVertexArray(mVertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBindTexture(GL_TEXTURE_2D, mColorTexture);

		glBindSampler(0, mTextureSamplersByWrappingMode[mActiveWrappingMode]);

		glUseProgram(mShaderProgram.Program());

		mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
		glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void WrappingModesDemo::CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& vertexBuffer)
	{
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTexture) * vertexCount, &vertices[0], GL_STATIC_DRAW);
	}

	void WrappingModesDemo::CreateIndexBuffer(UINT* indices, GLuint indexCount, GLuint& indexBuffer)
	{
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * indexCount, indices, GL_STATIC_DRAW);
	}

	void WrappingModesDemo::OnKey(int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			WrappingMode activeMode = WrappingMode(mActiveWrappingMode + 1);
			if (activeMode >= WrappingModeEnd)
			{
				activeMode = (WrappingMode)(0);
			}

			mActiveWrappingMode = activeMode;
		}
	}
}