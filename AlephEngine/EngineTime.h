#pragma once

namespace AlephEngine
{
	class EngineTime
	{
	private:
		static double time;
		static double deltaTime;

	public:
		static void UpdateTimes();
		static inline double GetTime() { return time; }
		static inline double GetDeltaTime() { return deltaTime; }
	};
}