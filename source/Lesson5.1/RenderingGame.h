#pragma once

#include "Game.h"

using namespace Library;

namespace Library
{
	class GameTime;
	class FirstPersonCamera;
	class Grid;
}

namespace Rendering
{
	class AmbientLightingDemo;

	class RenderingGame : public Game
	{
		RTTI_DECLARATIONS(RenderingGame, Game)

	public:
		RenderingGame(HINSTANCE instance, const std::wstring& windowTitle);

	protected:
		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;
		virtual void Shutdown() override;

	private:
		void OnKey(int key, int scancode, int action, int mods);

		FirstPersonCamera* mCamera;
		KeyboardHandler mKeyboardHandler;
		Grid* mGrid;

		AmbientLightingDemo* mAmbientLightingDemo;
	};
}
