#pragma once

namespace Library
{
	class GameTime
	{
	public:
		GameTime();
		GameTime(double totalGameTime, double elapsedGameTime);

		double TotalGameTime() const;
		void SetTotalGameTime(double totalGameTime);

		double ElapsedGameTime() const;
		void SetElapsedGameTime(double elapsedGameTime);

	private:
		double mTotalGameTime;
		double mElapsedGameTime;
	};
}
