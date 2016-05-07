#ifndef SCENELEVEL_H_
#define SCENELEVEL_H_	

#include <iostream>
#include <deque>

#include "Scene.h"
#include "../math_helper.h"
#include "../GraphPath.h"
#include "../particles/ParticleSystem.h"
#include "../model/TextMenuModel.h"

class SceneLevel : public Scene
{
private:

	Player *player;
	TankTower *tank_tower;

	std::vector<Enemy*> enemies;
	std::vector<House*> buildings;

	std::deque<GameObject*> bullets1_holder;
	std::deque<GameObject*> bullets2_holder;
	std::deque<GameObject*> bullets3_holder;
	std::deque<GameObject*> bullets_holder;

	TextMenuModel * info1;
	TextMenuModel * info2;
	TextMenuModel * info3;
	TextMenuModel * info4;
	TextMenuModel * info5;

public:
	enum LevelStatus
	{
		PLAY,
		WIN,
		LOSE,
		PAUSE
	};
	LevelStatus lstatus;

	SceneLevel(SceneType level, tanks::GameSettings * settings)
		:Scene(level, settings)
	{	

	};
	~SceneLevel()
	{
		Scene::~Scene();
	};
	void init();

	void play(float delta_time, tanks::MoveControlls * moving);
	void display();
	void update();
	void redefine();
	void keyboard(tanks::ButtonControlls button);

	LevelStatus getLstatus() 
	{ 
		return lstatus; 
	};
};

#endif /* SCENELEVEL_H_ */