#include "CollisionDetector.h"

bool BoxCollider::collide(GameObject *target)
{
	Vector3<float> current_position = m_force->m_go->m_body->m_position + m_force->m_delta_position;
	Vector3<float> current_radius = m_force->m_go->m_body->m_radius;

	Vector3<float> target_position = target->m_body->m_position;
	Vector3<float> target_radius = target->m_body->m_radius;

	float distance_between_x = fabs(current_position.x - target_position.x);
	float distance_between_y = fabs(current_position.y - target_position.y);
	float distance_between_z = fabs(current_position.z - target_position.z);

	float radius_summ_x = current_radius.x + target_radius.x;
	float radius_summ_y = current_radius.y + target_radius.y;
	float radius_summ_z = current_radius.z + target_radius.z;


	if (distance_between_x > radius_summ_x) return false;
	if (distance_between_y > radius_summ_y) return false;
	if (distance_between_z > radius_summ_z) return false;

	/*std::cout << " collision dx" << distance_between_x << " rx " << radius_summ_x
		<< " dy " << distance_between_y << " ry " << radius_summ_y
		<< " dz " << distance_between_z << " rz " << radius_summ_z
		<< std::endl;
	*/
	return true;
}

bool TerrainCollider::collide(GameObject *target)
{
	Vector3<float> current_position = m_force->m_go->m_body->m_position + m_force->m_delta_position;
	Vector3<float> current_radius = m_force->m_go->m_body->m_radius * 0.5;

	Vector3<float> target_position = target->m_body->m_position;
	Vector3<float> target_radius = target->m_body->m_radius;

	float distance_between_y = fabs(current_position.y - target_position.y);
	float radius_summ_y = current_radius.y + target_radius.y;

	if (current_position.y > 0) return false;
	//if (distance_between_y > radius_summ_y) return false;

	/*std::cout << " gravity "
		<< " px " << m_force->m_body->m_position.x
		<< " py " << m_force->m_body->m_position.y
		<< " pz " << m_force->m_body->m_position.z
		<< " dx " << m_force->m_delta_position.x
		<< " dy " << m_force->m_delta_position.y
		<< " dz " << m_force->m_delta_position.z
		<< std::endl;
		*/
	return true;
}
