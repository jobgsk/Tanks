#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <cmath>
#include "Vector3.h"
/*
*                  |M11	M12		M13		M14|
* [x	y	z	1]* |M21	M22		M23		M24|
*                  |M31	M32		M33		M34|
*                  |M41	M42		M43		M44|
*
* x' = (x * M11) + (y * M21) + (z * M31) + (1 * M41)
* y' = (x * M12) + (y * M22) + (z * M32) + (1 * M42)
* z' = (x * M13) + (y * M23) + (z * M33) + (1 * M43)
*
*
*      |1		0		0		0|
* TR = |0		1		0		0|
*      |0		0		1		0|
* 		|x		y		z		1|
*
*      |x		0		0		0|
*  S = |0		y		0		0|
*      |0		0		z		0|
* 		|0		0		0		1|
*
*      |1		0		0		0|
* Rx = |0		cosQ	sinQ	0|
*      |0		-sinQ	cosQ	0|
* 		|0		0		0		1|
*
*      |cosQ	0		-sinQ	0|
* Ry = |0		1		0		0|
*      |sinQ	0		cos		0|
* 		|0		0		0		1|
*
*/

template <class T>
class Matrix4
{
	T MV[4][4];
	void product(T TRM[4][4])
	{
		T M3[4][4];

		M3[0][0] = TRM[0][0] * MV[0][0] + TRM[0][1] * MV[1][0] + TRM[0][2] * MV[2][0] + TRM[0][3] * MV[3][0];
		M3[0][1] = TRM[0][0] * MV[0][1] + TRM[0][1] * MV[1][1] + TRM[0][2] * MV[2][1] + TRM[0][3] * MV[3][1];
		M3[0][2] = TRM[0][0] * MV[0][2] + TRM[0][1] * MV[1][2] + TRM[0][2] * MV[2][2] + TRM[0][3] * MV[3][2];
		M3[0][3] = TRM[0][0] * MV[0][3] + TRM[0][1] * MV[1][3] + TRM[0][2] * MV[2][3] + TRM[0][3] * MV[3][3];

		M3[1][0] = TRM[1][0] * MV[0][0] + TRM[1][1] * MV[1][0] + TRM[1][2] * MV[2][0] + TRM[1][3] * MV[3][0];
		M3[1][1] = TRM[1][0] * MV[0][1] + TRM[1][1] * MV[1][1] + TRM[1][2] * MV[2][1] + TRM[1][3] * MV[3][1];
		M3[1][2] = TRM[1][0] * MV[0][2] + TRM[1][1] * MV[1][2] + TRM[1][2] * MV[2][2] + TRM[1][3] * MV[3][2];
		M3[1][3] = TRM[1][0] * MV[0][3] + TRM[1][1] * MV[1][3] + TRM[1][2] * MV[2][3] + TRM[1][3] * MV[3][3];

		M3[2][0] = TRM[2][0] * MV[0][0] + TRM[2][1] * MV[1][0] + TRM[2][2] * MV[2][0] + TRM[2][3] * MV[3][0];
		M3[2][1] = TRM[2][0] * MV[0][1] + TRM[2][1] * MV[1][1] + TRM[2][2] * MV[2][1] + TRM[2][3] * MV[3][1];
		M3[2][2] = TRM[2][0] * MV[0][2] + TRM[2][1] * MV[1][2] + TRM[2][2] * MV[2][2] + TRM[2][3] * MV[3][2];
		M3[2][3] = TRM[2][0] * MV[0][3] + TRM[2][1] * MV[1][3] + TRM[2][2] * MV[2][3] + TRM[2][3] * MV[3][3];

		M3[3][0] = TRM[3][0] * MV[0][0] + TRM[3][1] * MV[1][0] + TRM[3][2] * MV[2][0] + TRM[3][3] * MV[3][0];
		M3[3][1] = TRM[3][0] * MV[0][1] + TRM[3][1] * MV[1][1] + TRM[3][2] * MV[2][1] + TRM[3][3] * MV[3][1];
		M3[3][2] = TRM[3][0] * MV[0][2] + TRM[3][1] * MV[1][2] + TRM[3][2] * MV[2][2] + TRM[3][3] * MV[3][2];
		M3[3][3] = TRM[3][0] * MV[0][3] + TRM[3][1] * MV[1][3] + TRM[3][2] * MV[2][3] + TRM[3][3] * MV[3][3];


		MV[0][0] = M3[0][0];
		MV[0][1] = M3[0][1];
		MV[0][2] = M3[0][2];
		MV[0][3] = M3[0][3];

		MV[1][0] = M3[1][0];
		MV[1][1] = M3[1][1];
		MV[1][2] = M3[1][2];
		MV[1][3] = M3[1][3];

		MV[2][0] = M3[2][0];
		MV[2][1] = M3[2][1];
		MV[2][2] = M3[2][2];
		MV[2][3] = M3[2][3];

		MV[3][0] = M3[3][0];
		MV[3][1] = M3[3][1];
		MV[3][2] = M3[3][2];
		MV[3][3] = M3[3][3];
	};
	
public:
	Matrix4()
	{
		init();
	};

	void init()
	{
		MV[0][0] = 1, MV[0][1] = 0, MV[0][2] = 0, MV[0][3] = 0;
		MV[1][0] = 0, MV[1][1] = 1, MV[1][2] = 0, MV[1][3] = 0;
		MV[2][0] = 0, MV[2][1] = 0, MV[2][2] = 1, MV[2][3] = 0;
		MV[3][0] = 0, MV[3][1] = 0, MV[3][2] = 0, MV[3][3] = 1;
	};

	void get_mat(T mat[])
	{
		mat[0] = MV[0][0], mat[1] = MV[0][1], mat[2] = MV[0][2], mat[3] = MV[0][3];
		mat[4] = MV[1][0], mat[5] = MV[1][1], mat[6] = MV[1][2], mat[7] = MV[1][3];
		mat[8] = MV[2][0], mat[9] = MV[2][1], mat[10] = MV[2][2], mat[11] = MV[2][3];
		mat[12] = MV[3][0], mat[13] = MV[3][1], mat[14] = MV[3][2], mat[15] = MV[3][3];
	}

	void translate(T tx, T ty, T tz)
	{
		T TRM[4][4] = {
				{ 1, 0, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 1, 0 },
				{ tx, ty, tz, 1 } };

		product(TRM);
	};

	void rotate(T ax, T ay, T az)
	{
		/*T XRM[4][4] = {
			{ 1, 0, 0, 0 },
			{ 0, cos(ax), -sin(ax), 0 },
			{ 0, sin(ax), cos(ax), 0 },
			{ 0, 0, 0, 1 } };


		T YRM[4][4] = {
			{ cos(ay), 0, -sin(ay), 0 },
			{ 0, 1, 0, 0 },
			{ sin(ay), 0, cos(ay), 0 },
			{ 0, 0, 0, 1 } };
		

		T ZRM[4][4] = {
			{ cos(ay), -sin(ay), 0, 0 },
			{ sin(ay), cos(ay), 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 } };

		M  = X.Y.Z

		M' = X.Y
		M  = M'.Z
			

		M' = X.Y

			| 1  0  0 |   | C  0 - D |
		M'= | 0  A -B | . | 0  1  0 |
			| 0  B  A |   | D  0  C |

			 | 1*C + 0*0 + 0*D   1*0 + 0*1 + 0*0   1*-D + 0*0 + 0*C |
		M' = | 0*C + A*0 + -B*D  0*0 + A*1 + -B*0  0*-D + A*0 + -B*C |
			 | 0*C + B*0 + A*D   0*0 + B*1 + A*0   0*-D + B*0 + A*C |

			 M = M'.Z

			| C   0 - D |	| E -F  0 |
		M = |-BD  A - BC | .| F  E  0 |
			| AD  B   AC |	| 0  0  1 |

			| C*E + 0*F + -D*0     C*-F  + 0*E + -D*0    C*0  + 0*0 + -D*1 |
		M =	|-BD*E + A*F + -BC*0  -BD*-F + A*E + -BC*0  -BD*0 + A*0 + -BC*1 |
			| AD*E + B*F + AC*0	   AD*-F + B*E +  AC*0   AD*0 + 0*0 +  AC*1 |
			*/

		T A = cos(ax);
		T B = sin(ax);
		T C = cos(ay);
		T D = sin(ay);
		T E = cos(az);
		T F = sin(az);

		T AD = A * D;
		T BD = B * D;

		T RM[4][4] = {
				{ (C*E),			(-C*F),		-D,		0 },
				{ (-BD*E + A*F), (BD*F + A*E), (-B*C),	0 },
				{ (AD*E + B*F), (-AD*F + B*E), (A*C),	0 },
				{ 0,			0,				0,		1 }
		};

		product(RM);
	};

	void scale(T sx, T sy, T sz)
	{
		T TRM[4][4] = {
				{ sx, 0, 0, 0 },
				{ 0, sy, 0, 0 },
				{ 0, 0, sz, 0 },
				{ 0, 0, 0, 1 } };

		product(TRM);
	};

	Vector3<T> vProduct(T vx, T vy, T vz)
	{
		T x = vx*MV[0][0] + vy*MV[1][0] + vz*MV[2][0] + 1 * MV[3][0];
		T y = vx*MV[0][1] + vy*MV[1][1] + vz*MV[2][1] + 1 * MV[3][1];
		T z = vx*MV[0][2] + vy*MV[1][2] + vz*MV[2][2] + 1 * MV[3][2];
		return Vector3<T>(x, y, z);
	};
};

#endif /* MATRIX4_H_ */