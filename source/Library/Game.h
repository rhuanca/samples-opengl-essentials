#pragma once

#include "Common.h"
#include "GameClock.h"
#include "GameTime.h"
#include "GameComponent.h"
#include <functional>

namespace Library
{
	class Game : public RTTI
	{
		RTTI_DECLARATIONS(Game, RTTI)

	public:
		typedef std::function<void(int, int, int, int)> KeyboardHandler;
		
		Game(HINSTANCE instance, const std::wstring& windowTitle);
		~Game();

		HINSTANCE Instance() const;
		GLFWwindow* Window() const;
		HWND Game::WindowHandle() const;
		bool DepthBufferEnabled() const;
		const std::wstring& WindowClass() const;
		const std::wstring& WindowTitle() const;
		int ScreenWidth() const;
		int ScreenHeight() const;
		float AspectRatio() const;
		bool IsFullScreen() const;
		const std::vector<GameComponent*>& Components() const;
		const ServiceContainer& Services() const;

		virtual void Run();
		virtual void Exit();
		virtual void Initialize();
		virtual void Update(const GameTime& gameTime);
		virtual void Draw(const GameTime& gameTime);

		void AddKeyboardHandler(KeyboardHandler handler);
		void RemoveKeyboardHandler(KeyboardHandler handler);

	protected:
		virtual void InitializeWindow();
		virtual void InitializeOpenGL();
		virtual void Shutdown();

		static const UINT DefaultScreenWidth;
		static const UINT DefaultScreenHeight;
		static const UINT DefaultFrameRate;
		
		HINSTANCE mInstance;
		std::wstring mWindowTitle;		
		GLFWwindow* mWindow;
		UINT mScreenWidth;
		UINT mScreenHeight;
		bool mIsFullScreen;

		GLint mMajorVersion;
		GLint mMinorVersion;

		bool mDepthStencilBufferEnabled;

		GameClock mGameClock;
		GameTime mGameTime;

		std::vector<GameComponent*> mComponents;
		ServiceContainer mServices;

		std::map<KeyboardHandler*, KeyboardHandler> mKeyboardHandlers;

	private:
		Game(const Game& rhs);
		Game& operator=(const Game& rhs);

		static Game* sInternalInstance;

		static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

		POINT CenterWindow(int windowWidth, int windowHeight);
	};
}