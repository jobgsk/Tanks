#ifndef SCENELOADING_H_
#define SCENELOADING_H_

#include "Scene.h"
#include "SceneLevel.h"

#include "../model/TextMenuModel.h"

class SceneLoading : public Scene {
public:

	std::vector<TextMenuModel*> mlist;
	int current;
	
	SceneLoading(SceneType level, tanks::GameSettings * settings)
		:Scene(level, settings)
	{
	}

	~SceneLoading()
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
		TextMenuModel * menu2 = new TextMenuModel("Loading...", 200, 250, tanks::MenuType::EMPTY);
		
		mlist.push_back(menu1);
		mlist.push_back(menu2);

		camera = new Camera(menu1, 4.0);
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

	void play(float delta_time, tanks::MoveControlls * moving) {};
	void update() {};
	void keyboard(tanks::ButtonControlls button) {};

};

#endif /* SCENELOADING_H_ */