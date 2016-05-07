#include "Bullet.h"
#include "Player.h"

void Bullet::play(float duration)
{
	if (state == ObjectState::DESTROYED)
		return;

	if (state == ObjectState::CHANGED)
	{
		if (shoot_delay > 0)
		{
			shoot_delay -= duration;
			//m_particle->update(duration);
			return;
		}
	
		state = ObjectState::DESTROYED;
		return;
	}

	if (m_body->m_position.magnitude() > 75)
	{
		state = ObjectState::DESTROYED;
		return;
	}

	sf->set_force(sf_value);
	for (int j = 0; j < this->forces.size(); j++)
	{
		if (!this->forces[j]->exec(duration))
			continue;

		if (this->forces[j]->collide())
		{
			GameObject * collider = this->forces[j]->m_collider;
			if (collider != m_instigator)
			{
				//std::cout << " fire colide" << std::endl;

				if (dynamic_cast<Tank*>(collider) && collider->state != ObjectState::DESTROYED)
				{
					Tank* tank = dynamic_cast<Tank*>(collider);
					tank->dec_helth(bvalue);

					((Tank *)m_instigator)->m_hits++;
					if (tank->state == ObjectState::DESTROYED)
						((Tank *)m_instigator)->m_kills++;
				}
				
				//m_particle->init(m_body->m_position);
				state = ObjectState::CHANGED;
				shoot_delay = 500;
				
				return;
			}
		}

		this->forces[j]->apply();
		//state = ObjectState::A;
	}
	
};


//void load_texture(const char * dir_name);
void Bullet::draw()
{
	if (state == ObjectState::ACTIVE)
	{
		/*std::cout << " test "
			<< m_body->m_position.x << " "
			<< m_body->m_position.y << " "
			<< m_body->m_position.z << std::endl;
			*/
		float mat[16];
		Matrix4<float> m_matrix = Matrix4<float>();
		m_matrix.init();
		m_matrix.translate(m_body->m_position.x, m_body->m_position.y, m_body->m_position.z);
		m_matrix.rotate(m_body->m_angle.x, m_body->m_angle.y, m_body->m_angle.z);
		m_matrix.get_mat(mat);

		m_render->render(mat);
		return;
	}
	
	if (state == ObjectState::CHANGED)
	{
		//m_particle->render();
		return;
	}
	
};