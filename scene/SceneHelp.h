#ifndef SCENE_HELP_H_
#define SCENE_HELP_H_

#include "Scene.h"
#include "../model/TextMenuModel.h"

class SceneHelp : public Scene {
public:

	std::vector<TextMenuModel*> mlist;
	int current;

	SceneHelp(SceneType type, tanks::GameSettings * settings)
		:Scene(type, settings)
	{

	}

	~SceneHelp()
	{
		Scene::~Scene();
	};

	void init()
	{
		redispaly = true;
		if (inited)
			return;

		TextMenuModel * menu1 = new TextMenuModel("Use W/S/Q/E/ for player control", 200, 475, tanks::MenuType::EMPTY);
		TextMenuModel * menu2 = new TextMenuModel("Use A/D for tower controle", 200, 450, tanks::MenuType::EMPTY);
		TextMenuModel * menu3 = new TextMenuModel("Use F to fire", 200, 425, tanks::MenuType::EMPTY);
		TextMenuModel * menu4 = new TextMenuModel("Use N/M to change game's view", 200, 400, tanks::MenuType::EMPTY);
		TextMenuModel * menu5 = new TextMenuModel("Use Enter to select menu", 200, 375, tanks::MenuType::EMPTY);
		TextMenuModel * menu6 = new TextMenuModel("Use Esc to go to the previous screen", 200, 350, tanks::MenuType::EMPTY);
		TextMenuModel * menu7 = new TextMenuModel("Use Esc to start game from the begining", 200, 325, tanks::MenuType::EMPTY);
		
		mlist.push_back(menu1);
		mlist.push_back(menu2);
		mlist.push_back(menu3);
		mlist.push_back(menu4);
		mlist.push_back(menu5);
		mlist.push_back(menu6);
		mlist.push_back(menu7);

		camera = new Camera(menu2, 4.0);
		camera->set_infront();

		current = 0;
		set_init();
	};

	void display()
	{
		for (int i = 0; i < mlist.size(); i++)
		{
			mlist[i]->render();
		}

	};

	void play(float delta_time, tanks::MoveControlls * moving)
	{

	};

	void update() {};

	void keyboard(tanks::ButtonControlls button)
	{
		
	};


};

#endif /* SCENE_HELP_H_ */