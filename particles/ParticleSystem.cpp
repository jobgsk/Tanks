#include "ParticleSystem.h"

//Returns a random float from 0 to < 1
float partic::randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

//Rotates the vector by the indicated number of degrees about the specified axis
Vec3f partic::rotate(Vec3f v, Vec3f axis, float degrees) {
	axis = axis.normalize();
	float radians = degrees * partic::PI / 180;
	float s = sin(radians);
	float c = cos(radians);
	return v * c + axis * axis.dot(v) * (1 - c) + v.cross(axis) * s;
}

//Returns the position of the particle, after rotating the camera
Vec3f partic::adjParticlePos(Vec3f pos) {
	return partic::rotate(pos, Vec3f(1, 0, 0), -60);
}

//Returns whether particle1 is in back of particle2
bool partic::compareParticles(Particle* particle1, Particle* particle2) {
	return partic::adjParticlePos(particle1->pos)[2] <
		partic::adjParticlePos(particle2->pos)[2];
}

//Returns an array indicating pixel data for an RGBA image that is the same as
//image, but with an alpha channel indicated by the grayscale image alphaChannel
char* partic::addAlphaChannel(Image* image, Image* alphaChannel) {
	char* pixels = new char[image->width * image->height * 4];
	for (int y = 0; y < image->height; y++) {
		for (int x = 0; x < image->width; x++) {
			for (int j = 0; j < 3; j++) {
				pixels[4 * (y * image->width + x) + j] =
					image->pixels[3 * (y * image->width + x) + j];
			}
			pixels[4 * (y * image->width + x) + 3] =
				alphaChannel->pixels[3 * (y * image->width + x)];
		}
	}

	return pixels;
}

//Makes the image into a texture, using the specified grayscale image as an
//alpha channel and returns the id of the texture
GLuint partic::loadAlphaTexture(Image* image, Image* alphaChannel) {
	char* pixels = partic::addAlphaChannel(image, alphaChannel);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		image->width, image->height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels);

	delete pixels;
	return textureId;
}