#ifndef ANIMATION_BONE_H_
#define ANIMATION_BONE_H_

//#include "../GameObject.h"
//#include "../StraightForce.h"

#include "Vector3.h"

class AnimationBone
{
public:

	int m_id;
	Vector3<float> m_position;
	Vector3<float> m_angle;
	AnimationBone * m_previous;

	Render * m_render;

	AnimationBone(int id)
	{
		m_id = id;
		m_position = Vector3<float>();
		m_angle = Vector3<float>();
		m_previous = this;

		m_render = new BoneRender(1, 0, 0, Vector3<float>(1, 1, 1));
	};

	void draw()
	{

		//float ax = tanks::grad_to_rad(tanks::direction_to_angle(m_angle.y, m_angle.z));
		//float ay = tanks::grad_to_rad(tanks::direction_to_angle(m_angle.x, m_angle.z));
		//float az = tanks::grad_to_rad(tanks::direction_to_angle(m_angle.x, m_angle.y));

		float ax = tanks::grad_to_rad(m_angle.x);
		float ay = tanks::grad_to_rad(m_angle.y);
		float az = tanks::grad_to_rad(m_angle.z);

		float mat[16];
		Matrix4<float> m_matrix = Matrix4<float>();
		m_matrix.init();
		m_matrix.translate(m_position.x, m_position.y, m_position.z);
		//m_matrix.rotate(m_angle.x, m_angle.y, m_angle.z); // + tanks::grad_to_rad(-45)
		//m_matrix.rotate(ax, ay, az);

		m_matrix.rotate(ax, 0, 0);
		m_matrix.rotate(0, ay, 0);
		m_matrix.rotate(0, 0, az);

		m_matrix.get_mat(mat);

		m_render->render(mat);
		return;

	};

};

/*
class AnimationBone : public GameObject 
{
public:

	//SimpleForce *sf;
	AngleForce *af;
	std::vector<PhysicsForce*> forces;

	AnimationBone(
		Render *render,
		PhysicsBody * body,
		int id, tanks::ModelType type)
		:GameObject(render, body, id, type)
	{
		//sf = new SimpleForce(this);
		af = new AngleForce(this);

		//forces.push_back(sf);
		forces.push_back(af);
	};

	void play(float duration)
	{
		state = ObjectState::ACTIVE;
		for (int i = 0; i < this->forces.size(); i++)
		{
			if (!this->forces[i]->exec(duration / 20))
				continue;
			
			this->forces[i]->apply();
			state = ObjectState::CHANGED;
		}
	}

	virtual void update()
	{
		std::cout << " test " 
			<< m_body->m_position.x << " " 
			<< m_body->m_position.y << " "
			<< m_body->m_position.z << std::endl;
		
	};

	virtual void draw()
	{
		if (state == ObjectState::ACTIVE)
		{
			float mat[16];
			Matrix4<float> m_matrix = Matrix4<float>();
			m_matrix.init();
			m_matrix.translate(m_body->m_position.x, m_body->m_position.y, m_body->m_position.z);
			m_matrix.rotate(m_body->m_angle.x, m_body->m_angle.y, m_body->m_angle.z); // + tanks::grad_to_rad(-45)
			m_matrix.get_mat(mat);

			m_render->render(mat);
			return;
		}

	};
};
*/
#endif /* ANIMATION_BONE_H_ */

