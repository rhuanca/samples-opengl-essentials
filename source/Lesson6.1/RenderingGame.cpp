#include "RenderingGame.h"
#include "GameException.h"
#include "FirstPersonCamera.h"
#include "ColorHelper.h"
#include "VectorHelper.h"
#include "Grid.h"
#include "Skybox.h"
#include "Utility.h"
#include <sstream>

#include "EnvironmentMappingDemo.h"

namespace Rendering
{
	RTTI_DEFINITIONS(RenderingGame)

	RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowTitle)
		: Game(instance, windowTitle),
		mCamera(nullptr), mKeyboardHandler(nullptr), mGrid(nullptr), mSkybox(nullptr),
		mEnvironmentMappingDemo(nullptr)
	{
		mDepthStencilBufferEnabled = true;
	}

	void RenderingGame::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		mCamera = new FirstPersonCamera(*this);
		mComponents.push_back(mCamera);
		mServices.AddService(Camera::TypeIdClass(), mCamera);

		using namespace std::placeholders;
		mKeyboardHandler = std::bind(&RenderingGame::OnKey, this, _1, _2, _3, _4);
		AddKeyboardHandler(mKeyboardHandler);

		mGrid = new Grid(*this, *mCamera);
		mComponents.push_back(mGrid);

		mSkybox = new Skybox(*this, *mCamera, "Content\\Textures\\Maskonaive2_1024\\posx.jpg", "Content\\Textures\\Maskonaive2_1024\\negx.jpg", "Content\\Textures\\Maskonaive2_1024\\posy.jpg", "Content\\Textures\\Maskonaive2_1024\\negy.jpg", "Content\\Textures\\Maskonaive2_1024\\posz.jpg", "Content\\Textures\\Maskonaive2_1024\\negz.jpg", 100.0f);
		mComponents.push_back(mSkybox);

		mEnvironmentMappingDemo = new EnvironmentMappingDemo(*this, *mCamera);
		mComponents.push_back(mEnvironmentMappingDemo);
		
		Game::Initialize();

		mCamera->SetPosition(0, 5, 20);
	}

	void RenderingGame::Shutdown()
	{
		DeleteObject(mEnvironmentMappingDemo);

		RemoveKeyboardHandler(mKeyboardHandler);
		DeleteObject(mSkybox)
		DeleteObject(mGrid);
		DeleteObject(mCamera);

		Game::Shutdown();
	}

	void RenderingGame::Draw(const GameTime& gameTime)
	{
		static const GLfloat one = 1.0f;

		glClearBufferfv(GL_COLOR, 0, &ColorHelper::CornflowerBlue[0]);
		glClearBufferfv(GL_DEPTH, 0, &one);

		Game::Draw(gameTime);

		glfwSwapBuffers(mWindow);
	}

	void RenderingGame::OnKey(int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			Exit();
		}
	}
}