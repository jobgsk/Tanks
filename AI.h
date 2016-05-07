#ifndef AI_H_
#define AI_H_

#include <iostream>
#include <vector>
#include <map>
#include <iostream>

#include "GameObject.h"
#include "Vector3.h"
#include "GraphPath.h"

#include "aicore/steering.h"

typedef std::map<int, GraphNode*>::iterator node_it_type;
class PathFinder
{
	
	std::map<int, GraphNode*> m_nodes_map;

public:
	GraphPath m_graph;

	GraphNode * m_start_node;
	GraphNode * m_end_node;
	std::vector<GraphNode*> m_path_nodes;
	PathFinder(){};
	PathFinder(GraphPath graph)
	{
		m_graph = graph;
		m_nodes_map = m_graph.get_nodes();
	};

	GraphNode * find_closest_node(GameObject* current);
	GraphNode * find_random_node();
	GraphNode * find_next_node();
	void create_path();
};

class MovementBehaviour
{
public:
	//float m_step_distance;
	//float m_step_angle;
	int r_direct;
	// position towards need to move
	Vector3<float> m_next_position;
	GameObject *m_go;

	enum MovementState
	{
		MOVE,
		ROTATE,
		STOP
	};
	MovementState m_movement_state;

	//keys events
	float m_event_move;
	float m_event_rotate;
	
	void reset_events()
	{
		m_event_move = 0;
		m_event_rotate = 0;
	};
	MovementBehaviour(){};
	MovementBehaviour(GameObject * obj)
	{
		m_go = obj;
		//m_step_distance = 10.f;
		//m_step_angle = 90.f;

	};

	void set_next_position(Vector3<float> next_position)
	{
		m_next_position = next_position;
	};

	void find_direction();
	float rotate_behaviour();
	float move_behaviour();
	void exec();
};

class VisionDetector
{
protected:
	GameObject * m_go;
	std::vector<GameObject*> m_obstacles;

public:
	GameObject* m_target;
	float m_angle_can_see;

	VisionDetector() {};
	VisionDetector(GameObject *go, float angle_can_see)
	{
		m_go = go;
		m_angle_can_see = angle_can_see;
	};

	void set_target(GameObject* target)
	{
		m_target = target;
	}

	void set_obstacles(GameObject* obj)
	{
		m_obstacles.push_back(obj);
	};

	bool find_target();
	bool collide(GameObject* o, float angle_can_see);
	bool overlap(GameObject* target, GameObject* obstacle);
};


class AI
{
public:
	GameObject* m_go;
	PathFinder m_path;
	MovementBehaviour m_move;
	VisionDetector m_vision;

	GraphNode *m_curr_node;
	bool debug;

	enum StateBehaviour
	{
		TARGER_PATH,
		RANDOM_PATH,
		SHOOTING
	};
	StateBehaviour m_state_behaviour;

	//keys events
	float m_event_move;
	float m_event_rotate;
	bool m_event_fire;

	void reset_events()
	{
		m_event_move = 0;
		m_event_rotate = 0;
		m_event_fire = false;
	};
	AI(){};
	AI(GameObject* go, PathFinder path, MovementBehaviour move, VisionDetector vision)
	{
		m_go = go;
		m_path = path;
		m_move = move;
		m_vision = vision;
		// 1 - look for player, if yes get node close to player

		// 2 - get closed node rundomly

		//init path rundomly
		m_curr_node = m_path.find_closest_node(m_go);
		get_next_node(false);

		debug = false;
	};
	void get_target_path();
	void get_rundom_path();

	virtual void get_next_node(bool target);
	virtual void exec();
	virtual void exec(float duration) {};
};

#endif /* AI_H_ */