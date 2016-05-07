#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
/*
Vector3<float> player(0.0, 0.0, 0.0);
Vector3<float> enemy(1.0, 1.0, 1.0);

float angle = acos(player.normalize * enemy.normalize);
float rDistance = (enemy - player).magnitude();
float sDistance = (enemy - player).squareMagnitude();

Vector3<float> direction = (enemy - player);
direction.normalize();

std::cout << "  Angle(degrees) between objects " << angle << std::endl;
std::cout << "  Distance(regular) between objects " << rDistance << std::endl;
std::cout << "  Distance(squared) between objects " << sDistance << std::endl;
std::cout << " direction from the main player to the enemy "
<< " x " << direction.x
<< " y " << direction.y
<< " z " << direction.z << std::endl;
std::cout << " velocity to get the player to the enemy in 5 seconds " << (rDistance / 5) << std::endl;
*/
template <class T>
class Vector3
{
public:
	/* value of x axis */
	T x;
	/* value of y axis */
	T y;
	/* value of z axis */
	T z;

	Vector3()
		:x(0), y(0), z(0){};

	Vector3(T x, T y, T z)
		:x(x), y(y), z(z){};

	/** Creates a vector between the given two points. */
	Vector3(const Vector3& from, const Vector3& to)
	{
		x = to.x - from.x;
		y = to.y - from.y;
		z = to.z - from.z;
	}

	/* Fliip all components of the vector */
	void invert()
	{
		//std::cout << " void invert() " << std::endl;
		x = -x;
		y = -y;
		z = -z;
	}

	/* value of vector */
	T magnitude() const
	{
		//std::cout << " T magnitude() const " << std::endl;
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	/* value of vector */
	T squareMagnitude() const
	{
		return (pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	/* Turns a non-zero vector into a vector of unit lenght */
	void normalize()
	{
		//std::cout << " void normalize() " << std::endl;
		T length = magnitude();
		if (length > 0)
		{
			(*this) *= ((T)1) / length;
		}
	}

	/** Returns a unit vector in the direction of this vector. */
	Vector3 unit() const
	{
		Vector3 result = *this;
		result.normalize();
		return result;
	}

	/* Multiplies this vector by the given scalar */
	void operator*=(const T value)
	{
		//std::cout << " void operator*=(const T value) " << std::endl;
		x *= value;
		y *= value;
		z *= value;
	}

	/* Returns a copy this vector, scaled the given value */
	Vector3 operator*(const T value) const
	{
		//std::cout << " Vector3 operator*(const T value) " << std::endl;
		return Vector3(x*value, y*value, z*value);
	}

	/* Adds the given vector to this */
	void operator+=(const Vector3& v)
	{
		//std::cout << "void operator+=(const Vector3& v)" << std::endl;
		x += v.x;
		y += v.y;
		z += v.z;
	}

	/* Returns the value of the given vector, added to this */
	Vector3 operator+(const Vector3& v) const
	{
		//std::cout << " Vector3 operator+(const Vector3& v)  " << std::endl;
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	/* Substract of the given vector from this */
	void operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	/* Returns the value of given vector, subtracted from this */
	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	/*
	Calculates and return a component-wise product of this
	vector with a given vector
	*/
	Vector3 componentProduct(const Vector3 &vector) const
	{
		return Vector3(x * vector.x, y * vector.y, z * vector.z);
	}
	/*
	Performs a component-wise product with a given vector and
	sets this vector to its result
	*/
	void componentProductUpdate(const Vector3 &vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
	}
	/*
	Calculate and return the scalar product of this vector
	with the given vector
	*/
	T scalarProduct(const Vector3 &vector) const
	{
		return x*vector.x + y*vector.y + z*vector.z;
	}
	/*
	Calculate and return the scalar product of this vector
	with the given vector
	*/
	T operator*(const Vector3 &vector) const
	{
		//std::cout << " T operator*(const Vector3 &vector) " << std::endl;
		return x*vector.x + y*vector.y + z*vector.z;
	}
	/*
	Calculate and return the vector product of this vector
	with the given vector
	*/
	Vector3 vectorProduct(const Vector3 &vector) const
	{
		return Vector3(
			y*vector.z - z*vector.y,
			z*vector.x - x*vector.z,
			x*vector.y - y*vector.x);
	}
	/*
	Calculate and return the vector product of this vector
	with the given vector
	*/
	Vector3 operator%(const Vector3 &vector) const
	{
		return vectorProduct(vector);
	}
	/*
	Updates this vector to be vector product of its current
	value and given vector
	*/
	void operator%=(const Vector3 &vector)
	{
		*this = vectorProduct(vector);
	}
	/*
	Orthonormal Basis
	*/
	void makeOrthonormalBasis(Vector3 *a, Vector3 *b, Vector3 *c)
	{
		a->normalize();
		(*c) = (*a) % (*b);
		if (c->squareMagnitude() == 0.0) return; // Or generate error 
		c->normalize();
		(*b) = (*c) % (*a);
	}
	/*
		convert angle to vector
	*/
	Vector3 angleToVector()
	{
		T radius = 1;
		T d_x = radius * sinf(z) * cosf(y);
		T d_y = radius * sinf(z) * sinf(y);
		T d_z = radius * cosf(z);
		return Vector3(d_x, d_y, d_z);
	}

	/** Zero all the components of the vector. */
	void clear()
	{
		x = y = z = 0;
	}

	/** Checks if the two vectors have identical components. */
	bool operator==(const Vector3& other) const
	{
		return x == other.x &&
			y == other.y &&
			z == other.z;
	}

	/** Checks if the two vectors have non-identical components. */
	bool operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}

	/** Finds this distance from this point to that given. */
	T distance(const Vector3 &other) const
	{
		return Vector3<T>(*this, other).magnitude();
	}

};

#endif /* VECTOR3_H_ */