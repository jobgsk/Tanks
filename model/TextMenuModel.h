#ifndef TEXT_MENU_MODEL_H_
#define TEXT_MENU_MODEL_H_

#include "../GameObject.h"
#include "../Settings.h"


class TextMenuModel : public GameObject {
public:
	tanks::MenuType value;
	bool selected;

	TextRender * srender;
	TextRender * urender;

	TextMenuModel(std::string text, int x, int y, tanks::MenuType v) : GameObject(1, tanks::ModelType::TEXT_MENU),
		value(v)
	{
		m_body = new PhysicsBody();
		m_body->m_position = Vector3<float>((float)x, (float)y, 0.0);

		srender = new TextRender("* " + text, x, y);
		urender = new TextRender("  " + text, x, y);
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

#endif /* TEXT_MENU_MODEL_H_ */