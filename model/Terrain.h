#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../GameObject.h"

typedef struct {
	float x;
	float y;
	float z;
} map_struct;

class Terrain : public GameObject {
	map_struct *map_array;
public:	
	Terrain(Render *render, PhysicsBody * body, int id, tanks::ModelType type)
		:GameObject(render, body, id, type)
	{
	
	};

	/*
		overloaded methods for not playable Game Object
	*/
	void play(float delta_time) {};
};

#endif /* TERRAIN_H_ */