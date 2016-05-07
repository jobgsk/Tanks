#ifndef PIC_MENU_MODEL_H_
#define PIC_MENU_MODEL_H_

#include "../GameObject.h"
#include "../Settings.h"


class PicMenuModel : public GameObject {
public:

	Vector3<float> position;
	Vector3<float> size;
	tanks::BulletType value;
	bool selected;

	PictureRender * urender;
	PictureRender * srender;

	PicMenuModel(char * texpath, char * stexpath, Vector3<float> p, Vector3<float> s, tanks::BulletType v) : 
		GameObject(1, tanks::ModelType::PIC_MENU), position(p), size(s), value(v)
	{
		m_body = new PhysicsBody();
		m_body->m_position = p;

		urender = new PictureRender(texpath, p, s);
		srender = new PictureRender(stexpath, p, s);
		selected = false;
	};

	/*
	overloaded methods for not playable Game Object
	*/
	void update(float delta_time) {};

	void render()
	{
		if (selected)
			srender->render();
		else
			urender->render();
	};


};

#endif /* PIC_MENU_MODEL_H_ */