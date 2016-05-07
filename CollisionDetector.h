#ifndef COLLISION_DETECTOR_H_
#define COLLISION_DETECTOR_H_

#include <iostream>

#include "GameObject.h"
#include "PhysicsForce.h"

class CollisionDetector
{
protected:
	PhysicsForce* m_force;
public:
	CollisionDetector()
	{
	};

	CollisionDetector(PhysicsForce *force)
	{
		m_force = force;
	};
	virtual bool collide(GameObject *target) = 0;
};

class BoxCollider : public CollisionDetector
{
public:
	BoxCollider(PhysicsForce *force)
		:CollisionDetector(force)
	{
	};

	bool collide(GameObject *target);
};

class SphereBoxCollider : public CollisionDetector
{
public:
	SphereBoxCollider(PhysicsForce *force)
		:CollisionDetector(force)
	{
	};

	bool collide(GameObject *target);
};

class TerrainCollider : public CollisionDetector
{
public:
	TerrainCollider(PhysicsForce *force)
		:CollisionDetector(force)
	{
	};
	bool collide(GameObject *target);
};


#endif /* COLLISION_DETECTOR_H_ */