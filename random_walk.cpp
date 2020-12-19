#include <deque>
#include <time.h>
#include "vect.h"

using Path = std::deque<std::pair<double, double>>;

VECTOR::Vector process_path(Path& path, double target, double dstep) 
{
	using VECTOR::Vector;
	std::srand(time(0));
	double direction = 0.0;
	Vector step;
	Vector result(0.0, 0.0);
	while (result.magval() < target) {
		auto test = result.magval();
		if (test > 90) {
			bool test_stop = true;
		}
		//todo: when many steps the error is accummuldte. check 100 and 1
		direction = std::rand() % 360;
		step.reset(dstep, direction, Vector::POL);
		result = result + step;
		path.push_back(std::make_pair(result.xval(), result.yval()));
	}
	return result;
}
