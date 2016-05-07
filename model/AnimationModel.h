#ifndef ANIMATION_MODEL_H_
#define ANIMATION_MODEL_H_

#include "AnimationBone.h"


class AnimationModel
{
public:
	//Render * m_render;
	int m_id;
	std::vector<AnimationBone*> m_bones;

	AnimationModel(int aid)
	{
		m_id = aid;
		//m_render = new BoneRender(1, 0, 0, Vector3<float>(1, 1, 1));
	};

	AnimationBone* get_by_id(int bid)
	{
		for (int i = 0; i < m_bones.size(); i++)
			if (m_bones[i]->m_id == bid)
				return m_bones[i];
		return NULL;
	}

	void add_bone(int bid, float p1x, float p1y, float p1z, float ax, float ay, float az)
	{
		AnimationBone * bone = new AnimationBone(bid);
		bone->m_position = Vector3<float>(p1x, p1y, p1z);
		/*bone->m_angle = Vector3<float>(
			tanks::grad_to_rad(dx), 
			tanks::grad_to_rad(dy), 
			tanks::grad_to_rad(dz));
		*/
		//float dx = p2x - p1x;
		//float dy = p2y - p1y;
		//float dz = p2z - p1z;

		//float ax = tanks::direction_to_angle(dz, dy);
		//float ay = tanks::direction_to_angle(dx, dz);
		//float az = tanks::direction_to_angle(dx, dy);

		bone->m_angle = Vector3<float>(
			ax,
			ay,
			az);
		//if (bid > 0)
		//	bone->m_previous = get_by_id(bid-1);
		m_bones.push_back(bone);
	}

	

	void test()
	{
		for (int i = 0; i < m_bones.size(); i++)
		{
			std::cout
				<< "id "
				<< m_bones[i]->m_id << " "
				<< "position "
				<< m_bones[i]->m_position.x << " "
				<< m_bones[i]->m_position.y << " "
				<< m_bones[i]->m_position.z << " "
				<< "angle "
				<< m_bones[i]->m_angle.x << " "
				<< m_bones[i]->m_angle.y << " "
				<< m_bones[i]->m_angle.z << " "
				<< std::endl;
		}
	}

	void draw()
	{
		for (int i = 0; i < m_bones.size(); i++)
		{
			m_bones[i]->draw();
		}

	};

};

#endif /* ANIMATION_MODEL_H_ */