#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <cmath>

#include "Vector3.h"
#include "Matrix4.h"

class PhysicsBody;
namespace tanks {

	float grad_to_rad(float grad);

	float rad_to_grad(float rad);
	/*
	angle between of objects
	*/
	float get_angle_between(PhysicsBody body, Vector3<float> next_position);
	/*
	angle between of vectors
	*/
	float get_angle_between_vectors(Vector3<float> v1, Vector3<float> v2);
	/*
	get perpendicular vector towards current
	*/
	Vector3<float> get_orthogonal(Vector3<float> direction);
	/*
	get angle by direction vector around Y
	*/
	float direction_to_angle(float x, float y);

	Vector3<float> angle_to_direction(float angle);
	/*
	get angle by matrix
	*/
	Vector3<float> angle_to_direction(Vector3<float>);

};
#endif // MATH_HELPER_H
