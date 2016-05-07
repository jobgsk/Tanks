/*
 * Defines the behaviour classes used for steering.
 *
 * Part of the Artificial Intelligence for Games system.
 *
 * Copyright (c) Ian Millington 2003-2006. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */
#include "steering.h"

namespace aicore
{

    void Seek::getSteering(SteeringOutput* output)
    {
        // First work out the direction
        output->linear = *target;
        output->linear -= character->position;

        // If there is no direction, do nothing
        if (output->linear.squareMagnitude() > 0)
        {
            output->linear.normalize();
            output->linear *= maxAcceleration;
        }
    }

    void Flee::getSteering(SteeringOutput* output)
    {
        // First work out the direction
        output->linear = character->position;
        output->linear -= *target;

        // If there is no direction, do nothing
        if (output->linear.squareMagnitude() > 0)
        {
			output->linear.normalize();
            output->linear *= maxAcceleration;
        }
    }

	SeekWithInternalTarget::SeekWithInternalTarget()
	{
		// Make the target pointer point at our internal target.
    	target = &internal_target;
	}

	void Wander::getSteering(SteeringOutput* output)
	{
		// Make sure we have a target
		if (target->squareMagnitude() == 0) {
			internal_target = character->position;
			internal_target.x += volatility;
		}

		Vector3<float> offset = *target - character->position;
		float angle;
		if (offset.x*offset.x + offset.z*offset.z > 0) {
			// Work out the angle to the target from the character
			angle = real_atan2(offset.z, offset.x);
		}
		else
		{
			// We're on top of the target, move it away a little.
			angle = 0;
		}

		// Move the target to the boundary of the volatility circle.
		internal_target = character->position;
		internal_target.x += volatility * real_cos(angle);
		internal_target.z += volatility * real_sin(angle);

		// Add the turn to the target
		internal_target.x += randomBinomial(turnSpeed);
		internal_target.z += randomBinomial(turnSpeed);

		Seek::getSteering(output);
	}

	void AvoidSphere::getSteering(SteeringOutput* output)
	{
		// Clear the output, in case we don't write to it later.
		output->clear();

		// Make sure we're moving
		if (character->velocity.squareMagnitude() > 0)
		{
			// Find the distance from the line we're moving along to the obstacle.
			Vector3<float> movementNormal = character->velocity.unit();
			//Vector3<float> characterToObstacle = obstacle->position - character->position;
			Vector3<float> characterToObstacle = obstacle->m_position - character->position;

			float distanceSquared = characterToObstacle * movementNormal;
			distanceSquared = characterToObstacle.squareMagnitude() - 
				distanceSquared*distanceSquared;

			// Check for collision
			//float radius = obstacle->radius + avoidMargin;
			float radius = obstacle->get_radius() + avoidMargin;
			if (distanceSquared < radius*radius)
			{
				// Find how far along our movement vector the closest pass is
				float distanceToClosest = characterToObstacle * movementNormal;
				
				// Make sure this isn't behind us and is closer than our lookahead.
				if (distanceToClosest > 0 && distanceToClosest < maxLookahead)
				{
					// Find the closest point
					Vector3<float> closestPoint = 
						character->position + movementNormal*distanceToClosest;

					// Find the point of avoidance
					internal_target = 
						//obstacle->position +
						obstacle->m_position +
						//(closestPoint - obstacle->position).unit() *
						(closestPoint - obstacle->m_position).unit() *
						//(obstacle->radius + avoidMargin);
						(obstacle->get_radius() + avoidMargin);

					// Seek this point
					Seek::getSteering(output);
				}
			}
		}
	}

	void BlendedSteering::getSteering(SteeringOutput *output)
	{
		// Clear the output to start with
		output->clear();

		// Go through all the behaviours in the list
		std::vector<BehaviourAndWeight>::iterator baw;
		float totalWeight = 0;
		SteeringOutput temp;
		for (baw = behaviours.begin(); baw != behaviours.end(); baw++)
		{
			// Make sure the children's character is set
			baw->behaviour->character = character;

			// Get the behaviours steering and add it to the accumulator
			baw->behaviour->getSteering(&temp);
			output->linear += temp.linear * baw->weight;
			output->angular += temp.angular * baw->weight;

			totalWeight += baw->weight;
		}

		// Divide the accumulated output by the total weight
		if (totalWeight > 0.0)
		{
			totalWeight = (float)1.0 / totalWeight;
			output->linear *= totalWeight;
			output->angular *= totalWeight;
		}
	}

	void PrioritySteering::getSteering(SteeringOutput* output)
	{
		// We'll need epsilon squared later.
		float epSquared = epsilon*epsilon;

		// Start with zero output, so if there are no behaviours in 
		// the list, we'll output zero.
		output->clear();

		// Go through all the behaviours in the list
		std::vector<SteeringBehaviour*>::iterator b;
		for (b = behaviours.begin(); b != behaviours.end(); b++)
		{
			// Make sure the children's character is set
			(*b)->character = character;

			// Get the steering result from this behaviour
			(*b)->getSteering(output);

			// Check if it is non zero.
			if (output->squareMagnitude() > epSquared)
			{
				// We have a result, so store it and exit.
				lastUsed = *b;
				return;
			}
		}
	}

}; // end of namespace
