#pragma once

#include "Game.h"

using namespace Library;

namespace Library
{
	class GameTime;
}

namespace Rendering
{
	class RenderingGame : public Game
	{
		RTTI_DECLARATIONS(RenderingGame, Game)

	public:
		RenderingGame(HINSTANCE instance, const std::wstring& windowTitle);

	protected:
		virtual void Draw(const GameTime& gameTime) override;
	};
}
