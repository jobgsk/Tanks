#ifndef GRAPH_PATH_H_
#define GRAPH_PATH_H_

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include <string>
#include <fstream>
#include <sstream>

#include "GameObject.h"


class GraphNode;

class GraphEdge {
public:
	GraphNode *m_node1;
	GraphNode *m_node2;
	int m_distance;

public:
	GraphEdge(GraphNode *node1, GraphNode *node2, int distance);

	GraphNode * get_node(GraphNode *node);

	int get_distance() 
	{
		return m_distance;
	}

	//static bool compare_to(GraphEdge* current, GraphEdge* next);

};

class GraphNode : public GameObject
{
private:
	int m_id;
	std::string m_name;
	int m_weight;
	bool m_visited;

	std::vector<GraphEdge*> m_edges;
	GraphEdge* m_main_edge;

public:

	/*
	overloaded methods for not drawable Game Object
	*/
	void draw() {};
	void update(){};

	GraphNode(int id);
	
	int get_id() 
	{ 
		return m_id; 
	};
	void set_id(int id) 
	{ 
		m_id = id; 
	};

	std::string get_name()
	{ 
		return m_name; 
	};
	void set_name(std::string name)
	{ 
		m_name = name; 
	};

	int get_weight() 
	{ 
		return m_weight; 
	};
	void set_weight(int weight) 
	{ 
		m_weight = weight; 
	};

	bool is_visited() 
	{
		return m_visited;
	};
	void set_visited(bool visited) 
	{
		m_visited = visited;
	};

	std::vector<GraphEdge*> get_edges()
	{
		return m_edges;
	};
	void set_edges(std::vector<GraphEdge*> edges) {
		m_edges = edges;
	};
	void set_edge(GraphEdge* edge) 
	{
		m_edges.push_back(edge);
	};

	GraphEdge* get_main_edge() 
	{
		return m_main_edge;
	};
	void set_main_edge(GraphEdge* main_edge) 
	{
		m_main_edge = main_edge;
	};


	/*
	* Dijkstra algorithm
	*/
	void create_graf();
	bool equals(GraphNode *obj);
};

typedef std::map<int, GraphNode*>::iterator n_it_type;

class GraphPath
{
	std::map<int, GraphNode*> m_nodes;
	
public:
	GraphPath()
	{
	};

	GraphPath(std::map<int, GraphNode*> m_nodes);
	void add_node(GraphNode* node);
	
	//void create_nodes(std::string filename);
	void create_edges(std::string filename);

	//GraphPath(std::string nodes_file, std::string edges_file);
	void show_path(GraphNode* end, GraphNode* start);
	std::map<int, GraphNode*> get_nodes()
	{
		return m_nodes;
	};

	void clean_graf()
	{
		for (n_it_type n_it = m_nodes.begin(); n_it != m_nodes.end(); n_it++)
		{
			n_it->second->set_weight(9000);
			n_it->second->set_visited(false);
		}
	};
};

#endif /* GRAPH_PATH_H_ */

