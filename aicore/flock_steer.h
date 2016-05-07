/*
* Steering behaviours for the flocking demo.
*
* Part of the Artificial Intelligence for Games system.
*
* Copyright (c) Ian Millington 2003-2006. All Rights Reserved.
*
* This software is distributed under licence. Use of this software
* implies agreement with all terms and conditions of the accompanying
* software licence.
*/
#ifndef DEMO_FLOCK_STEER_H
#define DEMO_FLOCK_STEER_H

#include "steering.h"
#include <list>


/**
 * This class stores a flock of creatures.
 */
class Flock
{
public:
	std::list<aicore::Kinematic*> boids;
	bool *inNeighbourhood;
	unsigned arraySize;

	Flock();

	/**
	 * Sets up the boolean flags of boids in the neighbourhood of the given boid.
	 */
	unsigned prepareNeighourhood(
		const aicore::Kinematic* of,
		float size,
		float minDotProduct = -1.0
		);

	/**
	 * Returns the geometric center of the flock.
	 */
	Vector3<float> getNeighbourhoodCenter();

	/**
	 * Returns the average velocity of the flock.
	 */
	Vector3<float> getNeighbourhoodAverageVelocity();
};

class BoidSteeringBehaviour : public aicore::SteeringBehaviour
{
public:
	Flock *theFlock;
	float neighbourhoodSize;
	float neighbourhoodMinDP;
	float maxAcceleration;
};

class Separation : public BoidSteeringBehaviour
{
	aicore::Flee flee;

public:
	virtual void getSteering(aicore::SteeringOutput* output);
};

class Cohesion : public BoidSteeringBehaviour
{
	aicore::Seek seek;

public:
	virtual void getSteering(aicore::SteeringOutput* output);
};

class VelocityMatchAndAlign : public BoidSteeringBehaviour
{
public:
	virtual void getSteering(aicore::SteeringOutput* output);
};



#endif
