#include "movement.h"
#include <iostream>

SteeringMovement::SteeringMovement(
	Vector3<float> position, 
	Vector3<float> orientation, 
	PhysicsBody* target) :
	MovementBehavior(position, orientation)
{
	static const float accel = 20.0;
	// Set up all possible behaviours
	seek = new aicore::Seek;
	flee = new aicore::Flee;
	wander = new aicore::Wander;

	seek->character = kinematic;
	seek->target = &target->m_position;
	seek->maxAcceleration = accel;

	flee->character = kinematic;
	flee->target = &target->m_position;
	flee->maxAcceleration = accel;

	wander->character = kinematic;
	wander->maxAcceleration = accel;
	wander->volatility = 20.0;
	wander->turnSpeed = 20.0;

	// Set the current behaviours
	m_current = seek;
	//m_current = wander;
};

aicore::SteeringOutput SteeringMovement::update(float duration)
{
	aicore::SteeringOutput steer;

	// Update the steering if we have a movement algorithm
	if (m_current)
		m_current->getSteering(&steer);
	else
		steer.clear();

	// Update the kinematic
	kinematic->integrate(steer, 0.95, duration);
	kinematic->setOrientationFromVelocity();

	// Check for maximum speed
	kinematic->trimMaxSpeed(20.0);

	return steer;
	//m_body->update_static(kinematic->position, kinematic->orientation);
};

SteeringPipeline::SteeringPipeline(
	Vector3<float> position, 
	Vector3<float> orientation, 
	PhysicsBody* target,
	std::vector<PhysicsBody*> obstacles,
	int speed) :
	MovementBehavior(position, orientation),
	m_obstacles(obstacles),
	m_scoef(speed)
{
	float accel = 100.0 * m_scoef;
	OBSTACLES = obstacles.size();
	// Create the fallback behaviour
	m_wander = new aicore::Wander;
	m_wander->maxAcceleration = accel;
	m_wander->character = kinematic;

	m_wander->volatility = 20.0;
	m_wander->turnSpeed = accel;

	// Create the obstacles
	//m_obstacles = new aicore::Sphere[OBSTACLES];
	//for (unsigned i = 0; i < OBSTACLES; i++) {
		//m_obstacles[i].position.x = obstacles[i]->m_position.x;
		//m_obstacles[i].position.y = 0.f;
		//m_obstacles[i].position.z = obstacles[i]->m_position.z;
		//Vector3<float> radius = obstacles[i]->m_radius;
		//m_obstacles[i].radius = (radius.x > radius.z) ? radius.x : radius.z;
	//}

	// Set up the steering pipe
	m_pipe = new aicore::SteeringPipe;
	m_pipe->character = kinematic;

	m_target = target;
	m_targeter = new aicore::FixedGoalTargeter;
	m_pipe->targeters.push_back(m_targeter);

	m_constraint = new aicore::AvoidSpheresConstraint;
	for (unsigned i = 0; i < OBSTACLES; i++)
	{
		//m_constraint->obstacles.push_back(m_obstacles + i);
		m_constraint->obstacles.push_back(m_obstacles[i]);
	}
	m_constraint->avoidMargin = 2.5;
	m_pipe->constraints.push_back(m_constraint);

	m_actuator = new aicore::BasicActuator;
	m_actuator->maxAcceleration = accel;
	m_pipe->setActuator(m_actuator);

	m_pipe->fallback = m_wander;
	m_pipe->registerComponents();
};

aicore::SteeringOutput SteeringPipeline::update(float duration)
{
	Vector3<float> pos = m_target->m_position;
	//std::cout << "position " << pos.x << " " << pos.y << " " << pos.z ;
	m_targeter->goal.positionSet = true;
	m_targeter->goal.position = pos;

	aicore::SteeringOutput steer;

	m_pipe->getSteering(&steer);

/*std::cout << "linear "
	<< steer.linear.x << " "
	<< steer.linear.x << " "
	<< steer.linear.x << " "
	<< " angular " << steer.angular
	<< std::endl;
*/
	// Update the kinematic
	kinematic->integrate(steer, 0.1, duration * 0.0001);
	kinematic->setOrientationFromVelocity();

	// Check for maximum speed
	kinematic->trimMaxSpeed(20.0 * m_scoef);

	/*std::cout << " kinematic "
		<< kinematic->position.x << " "
		<< kinematic->position.y << " "
		<< kinematic->position.z << " "
		<< std::endl;
		*/
	

	// Avoid penetration of obstacles
	for (unsigned i = 0; i < OBSTACLES; i++)
	{
		//aicore::Sphere &o = m_obstacles[i];
		PhysicsBody * o = m_obstacles[i];
		float distance = kinematic->position.distance(o->m_position);
		if (distance < o->get_radius() + 2.5f)
		{
			Vector3<float> offset = o->m_position - kinematic->position;
			offset.normalize();
			offset *= o->get_radius() + 2.5f;
			kinematic->position = o->m_position - offset;
		}
	}

	return steer;

	//m_body->update_static(kinematic->position, kinematic->orientation);
};
