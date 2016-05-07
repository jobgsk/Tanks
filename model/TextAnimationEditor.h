#ifndef TEXT_ANIMATION_EDITOR_MODEL_H_
#define TEXT_ANIMATION_EDITOR_MODEL_H_

#include "../GameObject.h"
#include "../Settings.h"
#include "AnimationBone.h"


class TextAnimationEditor : public GameObject {
public:
	tanks::MenuType value;
	bool selected;

	TextRender * m_render;
	AnimationBone * m_bone;

	TextAnimationEditor(std::string text, int x, int y, AnimationBone * bone, tanks::MenuType v) :
		GameObject(1, tanks::ModelType::TEXT_MENU),
		value(v),
		m_bone(bone)
	{
		m_body = new PhysicsBody();
		m_body->m_position = Vector3<float>((float)x, (float)y, 0.0);
		m_body->m_angle = Vector3<float>(
			0, 
			tanks::direction_to_angle(m_body->m_direction.x, m_body->m_direction.z),
			0);

		m_render = new TextRender(text, x, y);
		selected = false;
	};


	/*
	overloaded methods for not playable Game Object
	*/
	void update(float delta_time) {};

	void render()
	{
		std::stringstream sstm1;
		sstm1 << m_render->m_init_text
			<< " pos " 
			<< m_bone->m_position.x << " "
			<< m_bone->m_position.y << " "
			<< m_bone->m_position.z << " "
			<< " | angl "
			<< m_bone->m_angle.x << " "
			<< m_bone->m_angle.y << " "
			<< m_bone->m_angle.z;
		m_render->m_render_text = sstm1.str();
		m_render->render();
	};
};

#endif /* TEXT_ANIMATION_EDITOR_MODEL_H_ */
