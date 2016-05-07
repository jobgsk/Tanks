
#include "Camera.h"

void Camera::play(float delte_time)
{
	if (m_camera_position == CameraPosition::BEHIND)
		set_behind();
}

void Camera::set_behind()
{
	Vector3<float> t_position = m_target->getPosition();
	//Vector3<float> t_direction = m_target->getDirection();

	//Vector3<float> rvector(0.0, tanks::grad_to_rad(135), 0.0);
	Vector3<float> t_angle = m_target->m_body->m_angle; // +rvector;
	
	//m_body->m_angle += rvector;
	Matrix4<float> r_matrix = Matrix4<float>();
	r_matrix.rotate(t_angle.x, t_angle.y + tanks::grad_to_rad(m_y_angle_diff), t_angle.z);
	Vector3<float> t_direction = r_matrix.vProduct(1, 0, 1);


	//Vector3<float> t_position(1, 1, 1);

	//std::cout << " target::position x " << target->position.x << " y " << target->position.y << std::endl;
	//Vector3<float> t_direction = target->getDirection();

	/*
	float camX = distance * player->get_vx() + player->get_cx(); //player_center[0];
	float camZ = distance * player->get_vz() + player->get_cz(); //player_center[2];
	gluLookAt(camX, 2.0, camZ,   // Camera position
	player->get_cx(), 0.0, player->get_cz(),    // Look at point
	0.0, 1.0, 0.0);   // Up vector
	*/

	//Vector3<float> t_direction(t_position.x, t_position.y, t_position.z);

	t_direction.invert();
	t_direction.normalize();

	//position = (t_direction * m_distance) + t_position;
	//direction = t_position;

	Vector3<float> behind_position = (t_direction * m_distance) + t_position;
	m_body->m_position = Vector3<float>(behind_position.x, m_distance/1.5, behind_position.z);
	m_body->m_direction = Vector3<float>(t_position.x, 1.0, t_position.z);

	m_camera_position = CameraPosition::BEHIND;
}

void Camera::set_ontop()
{
	std::cout << " set_ontop " << std::endl;
	m_body->m_position = Vector3<float>(0.01, m_distance * 25, 0.01);
	m_body->m_direction = Vector3<float>(0.0, 1.0, 0.0);
	m_camera_position = CameraPosition::ONTOP;
}

void Camera::set_infront()
{
	std::cout << " set_infront " << std::endl;
	m_body->m_position = Vector3<float>(0.0, 0.0, 5.0);
	m_body->m_direction = Vector3<float>(0.0, 0.0, 0.0);
	m_camera_position = CameraPosition::INFRONT;
}