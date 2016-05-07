#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <vector>
#include <algorithm>
#include <GL/glut.h>

#include "imageloader.h"
#include "vec3f.h"
#include "../PhysicsBody.h"

namespace partic {
	const float PI = 3.1415926535f;

	//Represents a single particle.
	struct Particle {
		Vec3f pos;
		Vec3f velocity;
		Vec3f color;
		float timeAlive; //The amount of time that this particle has been alive.
		float lifespan;  //The total amount of time that this particle is to live.
	};

	//Returns a random float from 0 to < 1
	float randomFloat();

	//Rotates the vector by the indicated number of degrees about the specified axis
	Vec3f rotate(Vec3f v, Vec3f axis, float degrees);

	//Returns the position of the particle, after rotating the camera
	Vec3f adjParticlePos(Vec3f pos);

	//Returns whether particle1 is in back of particle2
	bool compareParticles(Particle* particle1, Particle* particle2);

	//Returns an array indicating pixel data for an RGBA image that is the same as
	//image, but with an alpha channel indicated by the grayscale image alphaChannel
	char* addAlphaChannel(Image* image, Image* alphaChannel);

	//Makes the image into a texture, using the specified grayscale image as an
	//alpha channel and returns the id of the texture
	GLuint loadAlphaTexture(Image* image, Image* alphaChannel);


	const float GRAVITY = 0.5f;
	const int NUM_PARTICLES = 100;
	//The interval of time, in seconds, by which the particle engine periodically
	//steps.
	const float STEP_TIME = 0.01f;
	//The length of the sides of the quadrilateral drawn for each particle.
	const float PARTICLE_SIZE = 0.2f;

	class ParticleSystem {
		
	private:
		GLuint textureId;
		Particle particles[NUM_PARTICLES];

		//std::vector<Particle*> particles;

		//The amount of time until the next call to step().
		float timeUntilNextStep;
		//The color of particles that the fountain is currently shooting.  0
		//indicates red, and when it reaches 1, it starts over at red again.  It
		//always lies between 0 and 1.
		float colorTime;
		//The angle at which the fountain is shooting particles, in radians.
		float angle;

		Vector3<float> init_position;

		//Returns the current color of particles produced by the fountain.
		Vec3f curColor() {
			Vec3f color = Vec3f(1.0f, colorTime, 0.0f);

			//Make sure each of the color's components range from 0 to 1
			for (int i = 0; i < 3; i++) {
				if (color[i] < 0) {
					color[i] = 0;
				}
				else if (color[i] > 1) {
					color[i] = 1;
				}
			}

			return color;
		}

		//Returns the average velocity of particles produced by the fountain.
		Vec3f curVelocity() {
			return Vec3f(0.5 * cos(angle), 1.0f, 0.5 * sin(angle));
		}

		//Alters p to be a particle newly produced by the fountain.
		void createParticle(Particle* p) {
			p->pos = Vec3f(init_position.x, init_position.y, init_position.z);
			p->velocity = curVelocity() + Vec3f(0.5f * randomFloat(),
				0.5f * randomFloat() + 0.5f,
				0.5f * randomFloat());
			p->color = curColor();
			p->timeAlive = 0;
			p->lifespan = randomFloat() + 0.5;
		}

		//Advances the particle fountain by STEP_TIME seconds.
		void step() {
			colorTime += STEP_TIME / 10;
			while (colorTime >= 1) {
				colorTime -= 1;
			}

			angle = 180.0 + (randomFloat() - 0.5) * 2;

			for (int i = 0; i < NUM_PARTICLES; i++) {
				Particle* p = particles + i;

				p->pos += p->velocity * STEP_TIME;
				p->velocity += Vec3f(0.0f, -GRAVITY * STEP_TIME, 0.0f);
				p->timeAlive += STEP_TIME;
				if (p->timeAlive > p->lifespan) {
					createParticle(p);
				}
			}
		}

	public:

		ParticleSystem(GLuint textureId1) {
			textureId = textureId1;
			for (int i = 0; i < NUM_PARTICLES; i++) {
				createParticle(particles + i);
			}
		}

		void init(Vector3<float> position)
		{
			init_position = position;
			timeUntilNextStep = 0;
			colorTime = 0;
			angle = 0;

			/*for (int i = 0; i < 5 / STEP_TIME; i++) {
				step();
			}*/
		}

		//update the particle fountain by the specified amount of time.
		void update(float dt) {
			step();
			/*while (dt > 0) {
				if (timeUntilNextStep < dt) {
					dt -= timeUntilNextStep;
					step();
					timeUntilNextStep = STEP_TIME;
				}
				else {
					timeUntilNextStep -= dt;
					dt = 0;
				}
			}
			*/
		}

		//Draws the particle fountain.
		void render() {
			std::vector<Particle*> ps;
			for (int i = 0; i < NUM_PARTICLES; i++) {
				ps.push_back(particles + i);
			}
			sort(ps.begin(), ps.end(), compareParticles);

			//glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBegin(GL_QUADS);
			for (unsigned int i = 0; i < ps.size(); i++) {
				Particle* p = ps[i];
				glColor4f(p->color[0], p->color[1], p->color[2], (1 - p->timeAlive / p->lifespan));
				float size = PARTICLE_SIZE / 2;

				//Vec3f pos = adjParticlePos(p->pos);
				Vec3f pos = p->pos;

				glTexCoord2f(0, 0);
				glVertex3f(pos[0] - size, pos[1] - size, pos[2]);
				glTexCoord2f(0, 1);
				glVertex3f(pos[0] - size, pos[1] + size, pos[2]);
				glTexCoord2f(1, 1);
				glVertex3f(pos[0] + size, pos[1] + size, pos[2]);
				glTexCoord2f(1, 0);
				glVertex3f(pos[0] + size, pos[1] - size, pos[2]);

				glColor4f(1.f, 1.f, 1.f, 1.f);
			}
			glEnd();
		}
	};

}

#endif /* PARTICLE_SYSTEM_H_ */