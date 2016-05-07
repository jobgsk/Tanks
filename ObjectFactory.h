#ifndef OBJECT_FACTORY_H_
#define OBJECT_FACTORY_H_

#include <iostream>

#include "model/Player.h"
#include "model/Enemy.h"
#include "model/TankTower.h"
#include "model/Terrain.h"
#include "model/House.h"
#include "model/Bullet.h"

#include "MeshFactory.h"
#include "Settings.h"

class ObjectFactory {

public:
	
	static GameObject* createPlayer(int id, int px, int pz, tanks::GameSettings * settings)
	{
		Vector3<float> position = Vector3<float>(px, 0.1, pz);
		Vector3<float> angle = Vector3<float>(0.0, tanks::grad_to_rad(45), 0.0);
		Matrix4<float> r_matrix = Matrix4<float>();
		r_matrix.rotate(angle.x, angle.y, angle.z);
		Vector3<float> direction = r_matrix.vProduct(1, 0, 1);
		
		MeshRender * tank_render = MeshFactory::getTank();
		MeshRender * tower_render = MeshFactory::getTower();

		ModelsStruct* tank_mesh = tank_render->get_mesh();
		ModelsStruct* tower_mesh = tower_render->get_mesh();

		PhysicsBody * tank_body = new PhysicsBody(Vector3<float>(tank_mesh->rx, tank_mesh->ry, tank_mesh->rz));
		tank_body->m_position = position;
		tank_body->m_angle = angle;
		tank_body->m_direction = direction;

		PhysicsBody * tower_body = new PhysicsBody(Vector3<float>(tower_mesh->rx, tower_mesh->ry, tower_mesh->rz));
		tower_body->m_direction = direction;
		tower_body->m_angle = angle;

		Player * player = new Player(
			new MeshRender(tank_mesh), tank_body, settings, id, tanks::ModelType::PLAYER);
		TankTower * tower = new TankTower(
			new MeshRender(tower_mesh), tower_body, player, id, tanks::ModelType::PLAYER_TOWER);
		tower->sync_parent();

		player->add_tower(tower);
		player->state = GameObject::ObjectState::CHANGED;
		return player;
	};

	static GameObject* createEnemy(int id, int px, int pz, tanks::GameSettings * settings)
	{
		Vector3<float> position = Vector3<float>(px, 0.1, pz);
		Vector3<float> angle = Vector3<float>(0.0, tanks::grad_to_rad(45), 0.0);
		Matrix4<float> r_matrix = Matrix4<float>();
		r_matrix.rotate(angle.x, angle.y, angle.z);
		Vector3<float> direction = r_matrix.vProduct(1, 0, 1);

		MeshRender * tank_render = MeshFactory::getTank();
		MeshRender * tower_render = MeshFactory::getTower();

		ModelsStruct* tank_mesh = tank_render->get_mesh();
		ModelsStruct* tower_mesh = tower_render->get_mesh();

		PhysicsBody * tank_body = new PhysicsBody(Vector3<float>(tank_mesh->rx, tank_mesh->ry, tank_mesh->rz));
		tank_body->m_position = position;
		tank_body->m_angle = angle;
		tank_body->m_direction = direction;

		PhysicsBody * tower_body = new PhysicsBody(Vector3<float>(tower_mesh->rx, tower_mesh->ry, tower_mesh->rz));
		tower_body->m_direction = direction;
		tower_body->m_angle = angle;

		Enemy * enemy = new Enemy(
			new MeshRender(tank_mesh), tank_body, settings, id, tanks::ModelType::ENEMY);
		TankTower * tower = new TankTower(
			new MeshRender(tower_mesh), tower_body, enemy, id, tanks::ModelType::ENEMY_TOWER);
		tower->sync_parent();

		enemy->add_tower(tower);
		enemy->state = GameObject::ObjectState::CHANGED;
		return enemy;
	};

	static GameObject* createGrass(int id, int px, int pz)
	{
		MeshRender * render = MeshFactory::getGrass();
		Terrain* obj = new Terrain(
			new MeshRender(render->get_mesh()), new PhysicsBody(), id, tanks::ModelType::TERRAIN);
		obj->m_body->m_position = Vector3<float>(px, 0.0, pz);
		obj->state = GameObject::ObjectState::CHANGED;
		return obj;
	};

	static GameObject* createHouse4(int id, int px, int pz)
	{
		MeshRender* render = MeshFactory::getObstacle4();
		ModelsStruct* mesh = render->get_mesh();
		PhysicsBody * body = new PhysicsBody(Vector3<float>(mesh->rx, mesh->ry, mesh->rz));
		body->m_position = Vector3<float>(px, 0.0, pz);

		House * obj = new House(new MeshRender(mesh), body, id, tanks::ModelType::OBSTACLE4);
		obj->state = GameObject::ObjectState::CHANGED;
		return obj;
	};

	static GameObject* createHouse3(int id, int px, int pz)
	{
		MeshRender* render = MeshFactory::getObstacle3();
		ModelsStruct* mesh = render->get_mesh();
		PhysicsBody * body = new PhysicsBody(Vector3<float>(mesh->rx, mesh->ry, mesh->rz));
		body->m_position = Vector3<float>(px, 0.0, pz);

		House * obj = new House(new MeshRender(mesh), body, id, tanks::ModelType::OBSTACLE3);
		obj->state = GameObject::ObjectState::CHANGED;
		return obj;
	};

	static GameObject* createHouse1(int id, int px, int pz)
	{
		MeshRender* render = MeshFactory::getObstacle1();
		ModelsStruct* mesh = render->get_mesh();
		PhysicsBody * body = new PhysicsBody(Vector3<float>(mesh->rx, mesh->ry, mesh->rz));
		body->m_position = Vector3<float>(px, 0.0, pz);

		House * obj = new House(new MeshRender(mesh), body, id, tanks::ModelType::OBSTACLE1);
		obj->state = GameObject::ObjectState::CHANGED;
		return obj;
	};

	static GameObject* createGraphNode(int id, int px, int pz)
	{
		GraphNode * obj = new GraphNode(id);
		obj->m_body->m_position = Vector3<float>(px, 0.0, pz);
		obj->state = GameObject::ObjectState::CHANGED;
		return obj;
	};
	

	static GameObject* create(int x, int z, char renderChar, int id, tanks::GameSettings * settings)
	{
		float coef = 5.0;
		float px = x * coef;
		float pz = z * coef;

		if (renderChar == 'G') 
			return ObjectFactory::createGrass(id, px, pz);
		
		if (renderChar == 'A')
			return ObjectFactory::createHouse4(id, px, pz);

		if (renderChar == 'B')
		{	
			GameObject* obj = ObjectFactory::createHouse4(id, px, pz);
			obj->m_body->m_angle = Vector3<float>(0.0, tanks::grad_to_rad(180), 0.0);
			return obj;
		}

		if (renderChar == 'C')
			return ObjectFactory::createHouse3(id, px, pz);


		if (renderChar == 'D') {
			GameObject* obj = ObjectFactory::createHouse3(id, px, pz);
			obj->m_body->m_angle = Vector3<float>(0.0, tanks::grad_to_rad(180), 0.0);
			return obj;
		}

		if (renderChar == 'F')
			return ObjectFactory::createHouse1(id, px, pz);
		
		if (renderChar == 'H') {
			GameObject* obj = ObjectFactory::createHouse1(id, px, pz);
			obj->m_body->m_angle = Vector3<float>(0.0, tanks::grad_to_rad(180), 0.0);
			return obj;
		}

		if (renderChar == 'P')
			return ObjectFactory::createPlayer(id, px, pz, settings);
		
		if (renderChar == 'E')
			return ObjectFactory::createEnemy(id, px, pz, settings);

		if (renderChar == 'N')
			return ObjectFactory::createGraphNode(id, px, pz);
		
		return NULL;
	};
	
};



#endif /* OBJECT_FACTORY_H_ */