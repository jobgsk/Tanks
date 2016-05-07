
#include "SceneLevel.h"

GameObject * find_go(std::vector<GameObject*> glist, int id, tanks::ModelType type)
{
	for (int i = 0; i < glist.size(); i++)
	{
		GameObject * go = glist[i];
		if (go->m_id == id && go->m_type == type)
			return go;
	}
	std::cout << " find_go fail " << id << " " << type << std::endl;
	return NULL;
}

void SceneLevel::init()
{
	redispaly = true;
	if (player != nullptr)
		player->bvalue = m_settings->bullet;
	if (inited)
		return;
		

	MapStream vms2("3DModels/map/5.2.txt", m_settings);
	vms2.load_map(&game_objects);

	player = (Player*)ObjectFactory::create(0, 0, 'P', 1, m_settings);
	tank_tower = (TankTower*)player->tower;

	player->m_bullets1_holder = &bullets1_holder;
	player->m_bullets2_holder = &bullets2_holder;
	player->m_bullets3_holder = &bullets3_holder;
	player->bvalue = m_settings->bullet;
	std::cout << "bvalue" << player->bvalue << std::endl;

	game_objects.push_back(player);
	camera = new Camera(tank_tower, 4.0);
	camera->set_behind();
	game_objects.push_back(camera);

	for (int i = 0; i < game_objects.size(); i++)
	{
		GameObject * go = game_objects[i];
		go->add_interacts(game_objects);
	}

	std::vector<GameObject*> waiting1;
	std::vector<GameObject*> waiting2;
	std::vector<GameObject*> waiting3;

	Enemy * enemy1 = (Enemy*)find_go(game_objects, 1, tanks::ModelType::ENEMY);
	Enemy * enemy2 = (Enemy*)find_go(game_objects, 2, tanks::ModelType::ENEMY);
	Enemy * enemy3 = (Enemy*)find_go(game_objects, 3, tanks::ModelType::ENEMY);
	Enemy * enemy4 = (Enemy*)find_go(game_objects, 4, tanks::ModelType::ENEMY);
	Enemy * enemy5 = (Enemy*)find_go(game_objects, 5, tanks::ModelType::ENEMY);
	Enemy * enemy6 = (Enemy*)find_go(game_objects, 6, tanks::ModelType::ENEMY);

	waiting2.push_back(enemy1);
	waiting2.push_back(enemy2);

	waiting3.push_back(enemy1);
	waiting3.push_back(enemy2);
	waiting3.push_back(enemy3);

	enemy1->waiting = waiting1;
	enemy2->waiting = waiting1;

	enemy3->waiting = waiting2;

	enemy4->waiting = waiting3;
	enemy5->waiting = waiting3;
	enemy6->waiting = waiting3;

	enemy1->state = GameObject::ObjectState::ACTIVE;
	enemy2->state = GameObject::ObjectState::ACTIVE;
	enemy3->state = GameObject::ObjectState::WAITING;
	enemy4->state = GameObject::ObjectState::WAITING;
	enemy5->state = GameObject::ObjectState::WAITING;
	enemy6->state = GameObject::ObjectState::WAITING;

	enemy1->bvalue = tanks::BulletType::TYPE1;
	enemy2->bvalue = tanks::BulletType::TYPE1;
	enemy3->bvalue = tanks::BulletType::TYPE2;
	enemy4->bvalue = tanks::BulletType::TYPE3;
	enemy5->bvalue = tanks::BulletType::TYPE1;
	enemy6->bvalue = tanks::BulletType::TYPE1;

	enemy1->m_bullets1_holder = &bullets1_holder;
	enemy2->m_bullets1_holder = &bullets1_holder;
	enemy3->m_bullets2_holder = &bullets2_holder;
	enemy4->m_bullets3_holder = &bullets3_holder;
	enemy5->m_bullets1_holder = &bullets1_holder;
	enemy6->m_bullets1_holder = &bullets1_holder;

	enemy1->speed = 1.0;
	enemy2->speed = 1.0;
	enemy3->speed = 2.0;
	enemy4->speed = 1.0;
	enemy5->speed = 1.0;
	enemy6->speed = 1.0;

	enemy1->set_movement(game_objects, player);
	enemy2->set_movement(game_objects, player);
	enemy3->set_movement(game_objects, player);
	enemy4->set_movement(game_objects, player);
	enemy5->set_movement(game_objects, player);
	enemy6->set_movement(game_objects, player);

	//enemy5->m_target = player;
	//enemy6->m_target = player;

	enemies.push_back(enemy1);
	enemies.push_back(enemy2);
	enemies.push_back(enemy3);
	enemies.push_back(enemy4);
	enemies.push_back(enemy5);
	enemies.push_back(enemy6);
	

	Image* image = loadBMP("3DModels/particlesystem/circle.bmp");
	Image* alphaChannel = loadBMP("3DModels/particlesystem/circlealpha.bmp");
	
	for (int i = 0; i < 300; i++)
	{
		tanks::BulletType bvalue;
		if (i < 100)
			bvalue = tanks::BulletType::TYPE1;
		else if (i < 200)
			bvalue = tanks::BulletType::TYPE2;
		else
			bvalue = tanks::BulletType::TYPE3;

		PhysicsBody * bullet_body = new PhysicsBody();
		partic::ParticleSystem* particle = new partic::ParticleSystem(
			partic::loadAlphaTexture(image, alphaChannel));

		SphereRender * render = new SphereRender(1, 0, 0, 1);
		Bullet * bullet = new Bullet(
			render, bullet_body, particle, i, tanks::ModelType::BULLET, bvalue);

		bullet->add_interacts(game_objects);

		if (bvalue == tanks::BulletType::TYPE1)
			bullets1_holder.push_back(bullet);
		else if (bvalue == tanks::BulletType::TYPE2)
			bullets2_holder.push_back(bullet);
		else if (bvalue == tanks::BulletType::TYPE3)
			bullets3_holder.push_back(bullet);

		bullets_holder.push_back(bullet);
	}

	info1 = new TextMenuModel("Health: ", 450, 570, tanks::MenuType::EMPTY);
	info2 = new TextMenuModel("Tanks: ", 450, 550, tanks::MenuType::EMPTY);
	info5 = new TextMenuModel("Hits: ", 450, 530, tanks::MenuType::EMPTY);
	info3 = new TextMenuModel("You loos, Game over", 200, 500, tanks::MenuType::EMPTY);
	info4 = new TextMenuModel("You win, Game over", 200, 500, tanks::MenuType::EMPTY);

	// Play game theme
	m_settings->mMusic->setVolume(50.f);
	m_settings->mMusic->play();

	set_init();
	lstatus = LevelStatus::PLAY;
};

void SceneLevel::play(float delta_time, tanks::MoveControlls * moving)
{
	if (lstatus != LevelStatus::PLAY)
		return;

	if (moving->move_forvard == true)
	{
		player->move_forward = true;
	}
	else if (moving->move_back == true)
	{
		player->move_back = true;
	}

	if (moving->move_left == true)
	{
		player->turn_left = true;
	}
	else if (moving->move_right == true)
	{
		player->turn_right = true;
	}

	if (moving->turn_left == true)
	{
		tank_tower->turn_left = true;
	}
	else if (moving->turn_right == true)
	{
		tank_tower->turn_right = true;
	}
	/*for (go_it_type go_it = game_objects.begin(); go_it != game_objects.end(); go_it++)
	{
		go_it->second->play();
	}
	*/
	for (int i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->play(delta_time);
	}

	for (int i = 0; i < bullets_holder.size(); i++)
	{
		bullets_holder[i]->play(delta_time);
	}

	/*
	apply physics forces to the game object
	*/
	/*for (int j = 0; j < game_objects[i]->forces.size(); j++)
	{
		if (!game_objects[i]->forces[j]->exec(5))
			continue;

		game_objects[i]->state = GameObject::ObjectState::CHANGED;

		if (game_objects[i]->forces[j]->collide())
		{
			game_objects[i]->forces[j]->reset();
			continue;
		}
		
		game_objects[i]->forces[j]->apply();
	}
	*/
}

void SceneLevel::display()
{
	/*for (go_it_type go_it = game_objects.begin(); go_it != game_objects.end(); go_it++)
	{
		go_it->second->draw();
	}
	*/
	for (int i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->draw();
	}

	for (int i = 0; i < bullets_holder.size(); i++)
	{
		if (bullets_holder[i]->state != GameObject::ObjectState::DESTROYED)
			bullets_holder[i]->draw();
	}

	std::stringstream sstm1;
	std::stringstream sstm2;
	std::stringstream sstm5;

	sstm1 << ((TextRender*)info1->urender)->m_init_text << player->m_helth;
	sstm2 << ((TextRender*)info2->urender)->m_init_text << player->m_kills;
	sstm5 << ((TextRender*)info5->urender)->m_init_text << player->m_hits;

	((TextRender*)info1->urender)->m_render_text = sstm1.str();
	((TextRender*)info2->urender)->m_render_text = sstm2.str();
	((TextRender*)info5->urender)->m_render_text = sstm5.str();

	info1->render();
	info2->render();
	info5->render();

	if (lstatus == LevelStatus::LOSE)
	{
		info3->render();
	}
	if (lstatus == LevelStatus::WIN)
	{
		info4->render();
	}
	redispaly = false;
};


void SceneLevel::redefine()
{
	for (int i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->redefine();
	}

	for (int i = 0; i < bullets_holder.size(); i++)
	{
		bullets_holder[i]->redefine();
	}

	Enemy * enemy1 = (Enemy*)find_go(game_objects, 1, tanks::ModelType::ENEMY);
	Enemy * enemy2 = (Enemy*)find_go(game_objects, 2, tanks::ModelType::ENEMY);
	Enemy * enemy3 = (Enemy*)find_go(game_objects, 3, tanks::ModelType::ENEMY);
	Enemy * enemy4 = (Enemy*)find_go(game_objects, 4, tanks::ModelType::ENEMY);
	Enemy * enemy5 = (Enemy*)find_go(game_objects, 5, tanks::ModelType::ENEMY);
	Enemy * enemy6 = (Enemy*)find_go(game_objects, 6, tanks::ModelType::ENEMY);

	enemy1->state = GameObject::ObjectState::ACTIVE;
	enemy2->state = GameObject::ObjectState::ACTIVE;
	enemy3->state = GameObject::ObjectState::WAITING;
	enemy4->state = GameObject::ObjectState::WAITING;
	enemy5->state = GameObject::ObjectState::WAITING;
	enemy6->state = GameObject::ObjectState::WAITING;

	enemy1->set_movement(game_objects, player);
	enemy2->set_movement(game_objects, player);
	enemy3->set_movement(game_objects, player);
	enemy4->set_movement(game_objects, player);
	enemy5->set_movement(game_objects, player);
	enemy6->set_movement(game_objects, player);

	lstatus = LevelStatus::PLAY;
};

void SceneLevel::update()
{
	if (lstatus != LevelStatus::PLAY)
		return;

	//for (go_it_type go_it = game_objects.begin(); go_it != game_objects.end(); go_it++)
	for (int i = 0; i < game_objects.size(); i++)
	{
		//GameObject * go = go_it->second;
		GameObject * go = game_objects[i];
		if (go->state == GameObject::ObjectState::CHANGED || 
			go->state == GameObject::ObjectState::WAITING)
		{
			/*
				update matrix by vector
			*/
			go->update();

			if (go->state == GameObject::ObjectState::CHANGED)
				go->state = GameObject::ObjectState::ACTIVE;

			redispaly = true;
		}
	}

	if (player->state == GameObject::ObjectState::DESTROYED)
	{
		lstatus = LevelStatus::LOSE;
	}
	else if (player->m_kills >= enemies.size())
	{
		lstatus = LevelStatus::WIN;
	}
};

void SceneLevel::keyboard(tanks::ButtonControlls button)
{
	if (button == tanks::ButtonControlls::FIRE)
	{
		player->fire();
	}
	else if (button == tanks::ButtonControlls::SHOW_MAP)
	{
		camera->set_ontop();
	}
	else if (button == tanks::ButtonControlls::SHOW_GAME)
	{
		camera->set_behind();
	}
};