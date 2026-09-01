#pragma once

struct Firemode {

	double RPM;
	double counter = 0;

	Firemode(double RPM)
		: RPM{RPM}
	{}

	Firemode() = default;

	virtual bool ready(double dt, bool trigger) = 0;

};

struct Semi : public Firemode {

	bool lastState;

	Semi(double RPM)
		: Firemode{RPM}
	{}

	bool ready(double dt, bool state) {
		counter += dt;
		if(state) {
			if(RPM / 60 * counter > 1) {
				if(state == !lastState) {
					lastState = state;
					counter = 0;
					return true;

				}
			}
		}
			lastState = state;
			return false;
	}
};

struct Full : public Firemode {

	Full(double RPM)
	: Firemode{RPM}
	{}

	bool ready(double dt, bool state) {
		counter += dt;
		if(state) {
			if(RPM / 60 * counter > 1) {
					counter = 0;
					return true;
			}
		}
		return false;
	}
};

struct Burst : public Firemode {

	int burstCount;
	int bulletCounter = 0;

	bool lastState = false;
	bool active = false;

	Burst(double RPM, int burstCount)
	: Firemode{RPM}
	, burstCount{burstCount}
	{}

	bool ready(double dt, bool state) {
		counter += dt;

		if(bulletCounter == 0 && !state) {
			lastState = state;
			return false;
		}

		if(state == !lastState && bulletCounter == 0) active = true;

		if(active) {
			if(RPM / 60 * counter > 1) {
				++bulletCounter;
				counter = 0;
				lastState = state;
				return true;
			}

			if(bulletCounter == burstCount) {
				bulletCounter = 0;
				active = false;
			}
		}

		lastState = state;
		return false;
	}
};

//If you click fast enough (ig inside one frame) it shoots only once
struct Binary : public Firemode {

	bool lastState;

	Binary(double RPM)
	: Firemode{RPM}
	{}

	bool ready(double dt, bool state) {
		counter += dt;
			if(RPM / 60 * counter > 1) {
				if(state == !lastState) {
					lastState = state;
					counter = 0;
					return true;

				}
			}
		lastState = state;
		return false;
	}
};
