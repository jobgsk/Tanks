#ifndef MOVEMENT_H_
#define MOVEMENT_H_	

#include "math_helper.h"
#include "aicore/steering.h"
#include "aicore/steerpipe.h"
#include "aicore/flock_steer.h"
#include "PhysicsBody.h"
/*
	here are classes for each type of movement behaviuor (setup of movement behaviour)
	like : stereeng, pipelne, group ...
*/

class MovementBehavior
{
public:
	// Holds the kinematic of the two agents.
	aicore::Kinematic *kinematic;

	MovementBehavior(Vector3<float> position, Vector3<float> orientation)
	{
		kinematic = new aicore::Kinematic;

		kinematic->position.x = position.x;
		kinematic->position.y = 0.f;
		kinematic->position.z = position.z;
		kinematic->orientation = tanks::direction_to_angle(orientation.x, orientation.z);
		kinematic->velocity.clear();
		kinematic->rotation = 0.0;
	};

	virtual aicore::SteeringOutput update(float duration) = 0;
};

class SteeringMovement : public MovementBehavior
{
public:
	// Holds the steering behaviours.
	aicore::Seek *seek;
	aicore::Flee *flee;
	aicore::Wander *wander;

	// Holds the currently used behaviours. 
	aicore::SteeringBehaviour *m_current;

	SteeringMovement(
		Vector3<float> position, 
		Vector3<float> orientation, 
		PhysicsBody* target);

	virtual aicore::SteeringOutput update(float duration);

	SteeringMovement::~SteeringMovement()
	{
		delete[] kinematic;

		delete[] seek;
		delete[] flee;
		delete[] wander;

		delete[] m_current;
	}
};


class SteeringPipeline : public MovementBehavior
{
private:
	int OBSTACLES;
public:
	/** Holds the obstacles */
	//aicore::Sphere *m_obstacles;
	std::vector<PhysicsBody*> m_obstacles;

	/** Holds the steering pipeline. */
	aicore::SteeringPipe *m_pipe;
	aicore::FixedGoalTargeter *m_targeter;
	aicore::AvoidSpheresConstraint *m_constraint;
	aicore::BasicActuator *m_actuator;

	/* Holds the fallback behaviour. */
	aicore::Wander *m_wander;

	PhysicsBody * m_target;
	float m_scoef;

	SteeringPipeline(
		Vector3<float> position,
		Vector3<float> orientation,
		PhysicsBody* target,
		std::vector<PhysicsBody*> obstacles,
		int speed);

	virtual aicore::SteeringOutput update(float duration);

	SteeringPipeline::~SteeringPipeline()
	{
		delete kinematic;

		delete m_pipe;
		delete m_actuator;
		delete m_constraint;
		delete m_targeter;
		delete m_wander;

		//delete[] m_obstacles;
	}

	//Avoid penetration of obstacles
	//void avoid_obstacles();
};

/*
class FlockingMovement : public MovementBehavior
{
public:
	FlockingMovement(
		Vector3<float> position,
		Vector3<float> orientation) :
		MovementBehavior(position, orientation)
	{
	};

	virtual aicore::SteeringOutput update(float duration)
	{

	};

	FlockingMovement::~FlockingMovement()
	{
		delete[] kinematic;
	}
};

class BlendedFlocking
{
private:
	int SEPARATION_WEIGHT;
	int COHESION_WEIGHT;
	int VMA_WEIGHT;
public:
	// Holds the steering behaviours.
	aicore::Seek *seek;

	// Holds the flock 
	Flock flock;

	// Holds the steering behaviours. 
	Separation *separation;
	Cohesion *cohesion;
	VelocityMatchAndAlign *vMA;

	aicore::BlendedSteering *steering;

	BlendedFlocking(
		std::vector<aicore::Kinematic*> kinematics, 
		PhysicsBody* target)
	{
		static const float accel = 20.0;

		SEPARATION_WEIGHT = 1.0;
		COHESION_WEIGHT = 1.0;
		VMA_WEIGHT = 2.0;

		// Set up all possible behaviours
		seek = new aicore::Seek;
		seek->character = kinematic;
		seek->target = &target->m_position;
		seek->maxAcceleration = accel;

		for (unsigned i = 0; i < kinematics.size(); i++)
		{

			flock.boids.push_back(kinematics[i]);
		}

		// Set up the steering behaviours (we use one for all)
		separation = new Separation;
		separation->maxAcceleration = accel;
		separation->neighbourhoodSize = 5.0;
		separation->neighbourhoodMinDP = - 1.0;
		separation->theFlock = &flock;

		cohesion = new Cohesion;
		cohesion->maxAcceleration = accel;
		cohesion->neighbourhoodSize = 10.0;
		cohesion->neighbourhoodMinDP = 0.0;
		cohesion->theFlock = &flock;

		vMA = new VelocityMatchAndAlign;
		vMA->maxAcceleration = accel;
		vMA->neighbourhoodSize = 15.0;
		vMA->neighbourhoodMinDP = 0.0;
		vMA->theFlock = &flock;

		steering = new aicore::BlendedSteering;
		steering->behaviours.push_back(aicore::BlendedSteering::BehaviourAndWeight(
			separation, SEPARATION_WEIGHT
			));
		steering->behaviours.push_back(aicore::BlendedSteering::BehaviourAndWeight(
			cohesion, COHESION_WEIGHT
			));
		steering->behaviours.push_back(aicore::BlendedSteering::BehaviourAndWeight(
			vMA, VMA_WEIGHT
			));
	}
};
*/


#endif /* MOVEMENT_H_ */
