#include "utility/utility.h"

utility::TimePoint utility::durationStart()
{
	return std::chrono::system_clock::now();
}

float utility::duration(const TimePoint& start)
{
	std::chrono::duration<float> duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
	return duration.count();
}

float utility::duration(std::function<void()> func)
{
	const TimePoint start = durationStart();

	func();

	return duration(start);
}

bool utility::intersectionPoint(Vec2f a1, Vec2f b1, Vec2f a2, Vec2f b2, Vec2f* i)
{
	Vec2f p = a1;
	Vec2f v = b1 - a1;
	Vec2f q = a2;
	Vec2f w = b2 - a2;

	float denominator = v.x * w.y - v.y * w.x;
	if (denominator != 0)
	{
		float t = (p.y * w.x - p.x * w.y + q.x * w.y - q.y * w.x) / denominator;
		float s = (q.y * v.x - q.x * v.y + p.x * v.y - p.y * v.x) / -denominator;

		if (t >= 0 && t <= 1 && s >= 0 && s <= 1)
		{
			*i = p + v * t;
			return true;
		}
	}

	return false;
}
