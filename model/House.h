#ifndef HOUSE_H_
#define HOUSE_H_

#include "../gameObject.h"

class House : public GameObject {
public:
	House(Render *render, PhysicsBody * body, int id, tanks::ModelType type)
		:GameObject(render, body, id, type)
	{

	};

	/*
	overloaded methods for not playable Game Object
	*/
	void play(float delta_time) {};
};

#endif /* HOUSE_H_ */