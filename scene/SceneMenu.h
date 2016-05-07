#ifndef SCENEMENU_H_
#define SCENEMENU_H_

#include "Scene.h"
#include "../model/TextMenuModel.h"

class SceneMenu : public Scene {
public:

	std::vector<TextMenuModel*> mlist;
	int current;

	SceneMenu(SceneType level, tanks::GameSettings * settings)
		:Scene(level, settings)
	{
	}

	~SceneMenu()
	{
		Scene::~Scene();
	};

	void init()
	{
		redispaly = true;
		if (inited)
			return;
		//std::string text, int x, int y
		TextMenuModel * menu1 = new TextMenuModel("TanKombat", 200, 550, tanks::MenuType::EMPTY);
		TextMenuModel * menu2 = new TextMenuModel("Play", 200, 475, tanks::MenuType::PLAY);
		TextMenuModel * menu3 = new TextMenuModel("Help", 200, 450, tanks::MenuType::HELP);
		TextMenuModel * menu4 = new TextMenuModel("Settings", 200, 425, tanks::MenuType::SETTINGS);
		TextMenuModel * menu5 = new TextMenuModel("A Editor", 200, 400, tanks::MenuType::AEDITOR);
		
		TextMenuModel * menu6 = new TextMenuModel("Quit", 200, 375, tanks::MenuType::QUIT);

		/*
		std::stringstream text4;
	text4 << "For navigation W, S, Q, E";
	m_array[4].text = text4.str();
	m_array[4].position_y = 400;

	std::stringstream text5;
	text5 << "For fire F";
	m_array[5].text = text5.str();
	m_array[5].position_y = 375;

	std::stringstream text6;
	text6 << "For fire direction A, D";
	m_array[6].text = text6.str();
	m_array[6].position_y = 350;

	std::stringstream text7;
	text7 << "For view mode N, M";
	m_array[7].text = text7.str();
	m_array[7].position_y = 325;
		*/

		mlist.push_back(menu1);
		mlist.push_back(menu2);
		mlist.push_back(menu3);
		mlist.push_back(menu4);
		mlist.push_back(menu5);
		mlist.push_back(menu6);

		camera = new Camera(menu1, 4.0);
		camera->set_infront();

		current = 0;
		set_init();
	};

	tanks::MenuType get_current()
	{
		return mlist[current]->value;
	};

	void display()
	{
		for (int i = 0; i < mlist.size(); i++)
		{
			if (i == current)
				mlist[i]->selected = true;
			else
				mlist[i]->selected = false;

			mlist[i]->render();
		}
	};

	void up()
	{
		if (current == 0)
			return;

		current--;
		redispaly = true;
	};

	void down()
	{
		if ((current + 1) < mlist.size())
			current++;
		redispaly = true;
	};

	void play(float delta_time, tanks::MoveControlls * moving)
	{
	/*std:cout
		<< " forvard " << moving->move_forvard
		<< " back " << moving->move_back
		<< " left " << moving->move_left
		<< " right " << moving->move_right
		<< " left " << moving->turn_left
		<< " right " << moving->turn_right << std::endl;
		*/
	};

	void update() 
	{
		
	};

	void keyboard(tanks::ButtonControlls button)
	{
		if (button == tanks::ButtonControlls::MOVE_DOWN)
		{
			down();
			return;
		}
		else if (button == tanks::ButtonControlls::MOVE_UP)
		{
			up();
			return;
		}
	};

};

#endif /* SCENEMENU_H_ */