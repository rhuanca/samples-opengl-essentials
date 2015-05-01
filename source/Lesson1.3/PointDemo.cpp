#include "PointDemo.h"
#include "Game.h"
#include "GameException.h"
#include "Utility.h"

namespace Rendering
{
	RTTI_DEFINITIONS(PointDemo)

	PointDemo::PointDemo(Game& game, Camera& camera)
		: DrawableGameComponent(game, camera), mShaderProgram(0), mVertexArrayObject(0)
	{
	}

	PointDemo::~PointDemo()
	{
		glDeleteProgram(mShaderProgram);
		glDeleteVertexArrays(1, &mVertexArrayObject);
	}

	void PointDemo::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		
		// Load and compile vertex shader
		std::vector<char> vertexShaderSource;
		Utility::LoadBinaryFile(L"Content\\Effects\\PointDemo.vert", vertexShaderSource);
		GLchar* sourcePointer = &vertexShaderSource[0];
		GLint length = vertexShaderSource.size();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &sourcePointer, &length);
		glCompileShader(vertexShader);

		// Load and compile fragment shader
		std::vector<char> fragmentShaderSource;
		Utility::LoadBinaryFile(L"Content\\Effects\\PointDemo.frag", fragmentShaderSource);
		sourcePointer = &fragmentShaderSource[0];
		length = fragmentShaderSource.size();

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &sourcePointer, &length);
		glCompileShader(fragmentShader);

		// Create and link the shader program
		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, vertexShader);
		glAttachShader(mShaderProgram, fragmentShader);
		glLinkProgram(mShaderProgram);

		// Clean up temporary shader objects
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Create vertex array object
		glGenVertexArrays(1, &mVertexArrayObject);
	}

	void PointDemo::Draw(const GameTime& gameTime)
	{
		glBindVertexArray(mVertexArrayObject);
		glUseProgram(mShaderProgram);
		glPointSize(80.0f);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
	}
}