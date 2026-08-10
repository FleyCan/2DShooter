#include "Person.hpp"


Vector<float,2> Person::processInput(Input input, double dt) {

	Vector<float,2> targetPosition = position;

	targetPosition[1] -= (input.up * speed);

	targetPosition[1] += (input.down * speed);

	targetPosition[0] -= (input.left * speed);

	targetPosition[0] += (input.right * speed);

	targetPosition[0] = std::clamp(
		targetPosition[0]
		, shape.getRadius()
		, maxPosition[0] - shape.getRadius()
	);
	targetPosition[1] = std::clamp(
		targetPosition[1]
		, shape.getRadius()
		, maxPosition[1] - shape.getRadius()
	);

	return targetPosition;
}

void Person::update(
	  Vector<unsigned int,2> maxPosition
	, Vector<float,2> targetPosition
	, double dt
) {
	position = targetPosition + (position-targetPosition) * std::exp(-16 * dt);
	this->maxPosition = maxPosition;
	shape.setPosition(
		  position[0]
		, position[1]
	);
}
