#include "AI.h"
#include "model/Tank.h"

GraphNode * PathFinder::find_closest_node(GameObject* current)
{
	Vector3<float> current_position = current->m_body->m_position;

	node_it_type node_it = m_nodes_map.begin();
	GraphNode *closest_node = node_it->second;
	
	for (; node_it != m_nodes_map.end(); node_it++)
	{
		if (closest_node == node_it->second)
		{
			continue;
		}
		

		float prev_distance = (closest_node->m_body->m_position - current_position).magnitude();
		float curr_distance = (node_it->second->m_body->m_position - current_position).magnitude();
		if (curr_distance < prev_distance)
		{
			closest_node = node_it->second;
		}		
	}
	return closest_node;
};

GraphNode * PathFinder::find_random_node()
{
	int size = m_nodes_map.size();
	int index = rand() % size + 1;
	//std::cout << " >>>>" << index << " " << size << std::endl;
	return m_nodes_map[index];
};

GraphNode * PathFinder::find_next_node()
{
	int size = m_path_nodes.size();
	GraphNode * next = m_path_nodes[(size-1)];
	m_path_nodes.pop_back();
	return next;
};

void PathFinder::create_path()
{
	if (m_start_node == NULL)
		return;
	m_graph.clean_graf();
	m_start_node->set_weight(0);
	m_start_node->create_graf();

	m_path_nodes.clear();

	std::vector<GraphNode *>::iterator it;
	while (m_end_node != m_start_node) {
		//it = m_path_nodes.begin();
		//m_path_nodes.insert(it, m_end_node);
		m_path_nodes.push_back(m_end_node);

		GraphEdge * road = m_end_node->get_main_edge();
		m_end_node = road->get_node(m_end_node);
	}
	m_path_nodes.push_back(m_start_node);
};

void MovementBehaviour::find_direction()
{
	m_movement_state = MovementState::ROTATE;
	/*
	define side to rotate
	*/
	r_direct = 1;
	float current_angle = tanks::direction_to_angle(m_go->m_body->m_direction.x, m_go->m_body->m_direction.z);

	Vector3<float> target_direction = (m_next_position - m_go->m_body->m_position);
	float target_angle = tanks::direction_to_angle(target_direction.x, target_direction.z);

	/*
		considering the curent angle
	*/
	target_angle -= current_angle;
	//std::cout << " find_direction " << current_angle << " " << target_angle << std::endl;

	/*
	TODO: if more or less 320 need +/- 320
	*/
	if (target_angle > 0 && target_angle < 180)
	{
		r_direct = -1;
		return;
	}
};

float MovementBehaviour::rotate_behaviour()
{
	// get angle between of directions of objects
	float delta_angle = tanks::get_angle_between(*m_go->m_body, m_next_position);

	float force = 1;
	if (delta_angle < 5.0)
	{
		//std::cout << " angle " << delta_angle << std::endl;
		m_movement_state = MovementState::MOVE;
		return 0;
	}

	if (delta_angle > 2)
	{
		//move with constant speed
		return force * r_direct;
	}

	//slow down the speed 
	force = 2.5 * r_direct * (delta_angle / 10);
	
	if (force < 0.05)
		force = 0.05;
	return force;
};

float MovementBehaviour::move_behaviour()
{
	// get radius between of objects
	float distatnce = (m_next_position - m_go->m_body->m_position).magnitude();
	
	float force = 1;
	if (distatnce < 4)
	{
		//std::cout << " distatnce " << distatnce << std::endl;
		m_movement_state = MovementState::STOP;
		return 0;
	}

	if (distatnce > 20)
	{
		//move with constant speed
		return force;
	}

	//slow down the speed 
	force = force * (distatnce / 20);
	if (force < 0.05)
		force = 0.05;
	return force;
};

void MovementBehaviour::exec()
{
	reset_events();

	if (m_movement_state == MovementState::ROTATE)
	{
		m_event_rotate = rotate_behaviour();
		return;
	}

	if (m_movement_state == MovementState::MOVE)
	{
		m_event_move = move_behaviour();
		return;
	}
};

bool VisionDetector::collide(GameObject* o, float angle_can_see)
{
	float grad_angle_betwen = tanks::get_angle_between(*m_go->m_body, o->m_body->m_position);
	if (grad_angle_betwen < angle_can_see)
		return true;
	return false;
};

bool VisionDetector::overlap(GameObject* target, GameObject* obstacle)
{
	float target_distance = (target->m_body->m_position - m_go->m_body->m_position).magnitude();
	float obstacle_distace = (obstacle->m_body->m_position - m_go->m_body->m_position).magnitude();

	if (obstacle_distace < target_distance)
		return true;
	return false;
};

bool VisionDetector::find_target()
{
	if (!collide(m_target, m_angle_can_see))
		return false;
	
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		if (!collide(m_obstacles[i], m_angle_can_see))
			continue;

		if (overlap(m_target, m_obstacles[i]))
			return false;
	}
	return true;
};

void AI::get_target_path()
{
	m_path.m_start_node = m_curr_node;
	m_path.m_end_node = m_path.find_closest_node(m_vision.m_target);

	m_path.create_path();
	//m_path.m_graph.show_path(m_path.m_end_node, m_path.m_start_node);

	m_state_behaviour = StateBehaviour::TARGER_PATH;
	//std::cout << " TARGER_PATH " << std::endl;
};

void AI::get_rundom_path()
{
	m_path.m_start_node = m_curr_node;
	m_path.m_end_node = m_path.find_random_node();

	m_path.create_path();
	//m_path.m_graph.show_path(m_path.m_end_node, m_path.m_start_node);

	m_state_behaviour = StateBehaviour::RANDOM_PATH;
	//std::cout << " RANDOM_PATH " << std::endl;
};

void AI::get_next_node(bool target)
{
	if (target)
		get_target_path();
	else if (m_path.m_path_nodes.size() == 0)
		get_rundom_path();	

	m_curr_node = m_path.find_next_node();
	m_move.set_next_position(m_curr_node->m_body->m_position);
	m_move.find_direction();
};

void AI::exec()
{
	reset_events();
	// if move - move to node

	// if stop , get next node:
	// 1 - look for player, if yes get node close to player
	// 2 - get closed node rundomly

	// recrate path 
	// move to next node 

	m_move.exec();

	if (m_vision.collide(m_vision.m_target, 10))
	{
		m_event_fire = true;
	}

	if (m_state_behaviour == StateBehaviour::SHOOTING)
	{
		float target_distance = (m_vision.m_target->m_body->m_position - m_go->m_body->m_position).magnitude();
		if (target_distance < 25 && m_vision.collide(m_vision.m_target, 90))
		{
			if (m_move.m_movement_state == MovementBehaviour::MovementState::ROTATE)
			{
				//std::cout << " >>>>>>>>>>>>SHOOTING<<<<<<<<<<<<<< " << std::endl;
				m_event_rotate = m_move.m_event_rotate;
				//std::cout << " m_event_rotate " << m_event_rotate << std::endl;
				return;
			}

			m_event_fire = true;
			return;
		}
			
		get_next_node(false);
		return;
	}

	if (m_state_behaviour == StateBehaviour::TARGER_PATH)
	{
		float target_distance = (m_vision.m_target->m_body->m_position - m_go->m_body->m_position).magnitude();
		if (target_distance < 15 && m_vision.collide(m_vision.m_target, 90))
		{
			m_move.set_next_position(m_vision.m_target->m_body->m_position);
			m_move.find_direction();
			m_state_behaviour = StateBehaviour::SHOOTING;
			return;
		}
	}

	if (m_state_behaviour != StateBehaviour::TARGER_PATH && m_vision.find_target())
	{
		get_next_node(true);
		//std::cout << " >>>>>>>>>>>>LOOK<<<<<<<<<<<<<< " << std::endl;
		return;
	}
		
	if (m_move.m_movement_state == MovementBehaviour::MovementState::MOVE)
	{
		m_event_move = m_move.m_event_move;
		//std::cout << " m_event_move " << m_event_move << std::endl;
		return;
	}
			
	if (m_move.m_movement_state == MovementBehaviour::MovementState::ROTATE)
	{
		m_event_rotate = m_move.m_event_rotate;
		//std::cout << " m_event_rotate " << m_event_rotate << std::endl;
		return;
	}
			
	if (m_move.m_movement_state == MovementBehaviour::MovementState::STOP)
	{
		get_next_node(false);
		//std::cout << " get_next_node false " << std::endl;
		return;
	}
};
