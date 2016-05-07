#ifndef SCENE_SETTINGS_H_
#define SCENE_SETTINGS_H_

#include "Scene.h"
#include "../model/PicMenuModel.h"

class SceneSettings : public Scene {
public:

	std::vector<PicMenuModel*> mlist;
	int current;

	SceneSettings(SceneType type, tanks::GameSettings * settings)
		:Scene(type, settings)
	{

	}

	~SceneSettings()
	{
		Scene::~Scene();
	};

	void init()
	{
		redispaly = true;
		if (inited)
			return;

		PicMenuModel * menu1 = new PicMenuModel(
			"3DModels/Textures/menu1.bmp", 
			"3DModels/Textures/menu1s.bmp",
			Vector3<float>(0, 2, 0), 
			Vector3<float>(2.5, 0.5, 0),
			tanks::BulletType::TYPE1);
		PicMenuModel * menu2 = new PicMenuModel(
			"3DModels/Textures/menu2.bmp", 
			"3DModels/Textures/menu2s.bmp",
			Vector3<float>(0, 0, 0), 
			Vector3<float>(2.5, 0.5, 0),
			tanks::BulletType::TYPE2);
		PicMenuModel * menu3 = new PicMenuModel(
			"3DModels/Textures/menu3.bmp", 
			"3DModels/Textures/menu3s.bmp",
			Vector3<float>(0, -2, 0), 
			Vector3<float>(2.5, 0.5, 0),
			tanks::BulletType::TYPE3);

		mlist.push_back(menu1);
		mlist.push_back(menu2);
		mlist.push_back(menu3);

		camera = new Camera(menu2, 10.0);
		camera->set_infront();

		current = 0;
		set_init();
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

	void setup()
	{
		m_settings->bullet = mlist[current]->value;
		std::cout << " bullet " << m_settings->bullet << std::endl;
	};

	tanks::BulletType get_current()
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
	
	void play(float delta_time, tanks::MoveControlls * moving) 
	{
		
	};

	void update() {};
	
	void keyboard(tanks::ButtonControlls button)
	{
		if (button == tanks::ButtonControlls::MOVE_DOWN)
		{
			down();
			return;
		}
		
		if (button == tanks::ButtonControlls::MOVE_UP)
		{
			up();
			return;
		}

		if (button == tanks::ButtonControlls::ENTER)
		{
			setup();
			return;
		}
	};

	
};

#endif /* SCENE_SETTINGS_H_ */