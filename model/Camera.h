#ifndef CAMERA_H_
#define CAMERA_H_

#include "../GameObject.h"

class Camera : public GameObject {

public:
	float m_distance;
	GameObject *m_target;
	float m_y_angle_diff;

	enum CameraPosition
	{
		BEHIND,
		ONTOP,
		INFRONT
	};
	CameraPosition m_camera_position;

	Camera(GameObject *target, float distance)
		:GameObject(1, tanks::ModelType::CAMERA)
	{
		m_distance = distance;
		m_target = target;
		m_y_angle_diff = 0;
	};

	void play(float delte_time);

	void set_behind();
	void set_ontop();
	void set_infront();

	/*
		overloaded methods for not drawable Game Object
	*/
	void draw() {};
	void update(){};

};

#endif /* CAMERA_H_ */