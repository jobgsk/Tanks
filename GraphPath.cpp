#include <algorithm>

#include "GraphPath.h"

GraphEdge::GraphEdge(GraphNode *node1, GraphNode *node2, int distance)
{
	m_node1 = node1;
	m_node2 = node2;

	m_distance = distance;

};

// sort using a custom function object
struct {
	bool operator()(GraphEdge* current, GraphEdge* next)
	{
		return next->get_distance() > current->get_distance();
	}
} compare_to;

GraphNode * GraphEdge::get_node(GraphNode *node)
{
	if (m_node1->equals(node))
		return m_node2;
	return m_node1;
}


GraphNode::GraphNode(int id)
	:GameObject(id, tanks::ModelType::PATH_NODE)
{
	m_id = id;
	m_name = "node";

	m_weight = 9000;
	m_visited = false;
};

void GraphNode::create_graf()
{
	for (int i = 0; i < m_edges.size(); i++) 
	{
		GraphEdge *road = m_edges[i];
		GraphNode *neighbor = road->get_node(this);
		if (neighbor->is_visited())
			continue;

		int expected_weight = m_weight + road->get_distance();
		if (expected_weight < neighbor->get_weight())
		{
			neighbor->set_weight(expected_weight);
			neighbor->set_main_edge(road);
		}
	}

	set_visited(true);
	std::sort(m_edges.begin(), m_edges.end(), compare_to);

	for (int i = 0; i < m_edges.size(); i++)
	{
		GraphEdge *road = m_edges[i];
		GraphNode *neighbor = road->get_node(this);
		if (neighbor->is_visited())
			continue;

		neighbor->create_graf();
	}
};

bool GraphNode::equals(GraphNode *other)
{
	if (other == NULL)
		return false;
	
	if (get_id() != other->get_id()) {
		return false;
	}

	if (get_name() != other->get_name()) {
		return false;
	}

	return true;
};

GraphPath::GraphPath(std::map<int, GraphNode*> nodes)
{
	for (n_it_type n_it = nodes.begin(); n_it != nodes.end(); n_it++)
	{
		m_nodes[n_it->first] = n_it->second;
	}
};
/*void GraphPath::create_nodes(std::string filename)
{
	std::ifstream infile;
	infile.open(filename, std::fstream::in);
	if (!infile)
	{
		std::cout << "Cannot open nodes file! " << std::endl;
	}

	int id;
	std::string name;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		iss >> id >> name;
		m_nodes[id] = new GraphNode(id, name);
	}
};
*/

void GraphPath::add_node(GraphNode* node)
{
	m_nodes[node->get_id()] = node;
};

void GraphPath::create_edges(std::string filename)
{
	std::ifstream infile;
	infile.open(filename, std::fstream::in);
	if (!infile)
	{
		std::cout << "Cannot open edges file! " << std::endl;
	}

	int node_id1, node_id2;
	float distance;

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		iss >> node_id1 >> node_id2;

		GraphNode * node1 = m_nodes[node_id1];
		GraphNode * node2 = m_nodes[node_id2];

		//Vector3<float> dist = node2->m_body.m_position - node1->m_body.m_position;
		distance = (node2->m_body->m_position - node1->m_body->m_position).magnitude();
		GraphEdge * edge = new GraphEdge(node1, node2, distance);
		node1->set_edge(edge);
		node2->set_edge(edge);
	}
};

void GraphPath::show_path(GraphNode* end, GraphNode* start)
{
	int distance = 0;
	while (end != start) {
		
		GraphEdge * road = end->get_main_edge();
		std::cout
			<< "From: " << end->get_name()
			<< "distance: " << road->get_distance()
			<< "to: " << road->get_node(end)->get_name()
			<< std::endl;
		distance += road->get_distance();
		end = road->get_node(end);
	}

	std::cout << "Full path: " << distance << std::endl;
}