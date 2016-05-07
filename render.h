#ifndef RENDER_H_
#define RENDER_H_

/*
here is render of diferent privitives for opengl
move here code from object.cpp
*/
#include <stdio.h>
#include <assert.h>
#include <iostream>

#include "vector3.h"
#include "matrix4.h"
#include "gloader.h"

#include "StaticModelLoader.h"

class Render{
protected:
	float m_r, m_g, m_b;
public:

	Render(float r, float g, float b) :
		m_r(r), m_g(g), m_b(b)
	{
	};

	Render() :
		m_r(0.8), m_g(0.8), m_b(0.8)
	{
	};

	virtual void render()
	{

	};

	virtual void render(float mat[])
	{

	};
};

class MeshRender : public Render{
protected:
	ModelsStruct *m_mesh;
public:

	Matrix4<float> m_matrix;
	
	MeshRender(ModelsStruct * mesh) : Render()
	{
		m_matrix = Matrix4<float>();
		StaticModelLoader * loader = mesh->loader;
		m_mesh = CopyModel(loader);
	};

	MeshRender(char *meshpath, char *matpath, char * texpath) : Render()
	{
		m_matrix = Matrix4<float>();
		StaticModelLoader* loader = new StaticModelLoader(meshpath, matpath);
		loader->load_texture(texpath);
		m_mesh = CopyModel(loader);

		std::cout << m_mesh->rx << " " << m_mesh->ry << " " << m_mesh->rz << std::endl;
	};

	ModelsStruct* get_mesh()
	{
		return m_mesh;
	};

	virtual ~MeshRender()
	{
		delete[] m_mesh->v_array;
	};

	virtual void render(float mat[])
	{
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		GLuint texture = -1;
		for (int i = 0; i < m_mesh->f_num; i++)
		{
			if (texture == -1 || texture != m_mesh->f_array[i].material->TexID)
			{
				if (m_mesh->f_array[i].material->map_kd.size() > 0)
				{
					texture = m_mesh->f_array[i].material->TexID;
					//std::cout << " GL_TEXTURE_2D " << m_model->f_array[i].material->TexID << std::endl;
					glBindTexture(GL_TEXTURE_2D, texture);
				}
			}
			draw_poligon(i);
		}
		glPopMatrix();
	};

	virtual void render()
	{
		for (int i = 0; i < m_mesh->v_num; i++)
		{
			Vector3<float> new_coord = m_matrix.vProduct(
				m_mesh->v_array[i].ox, m_mesh->v_array[i].oy, m_mesh->v_array[i].oz);
			m_mesh->v_array[i].x = new_coord.x;
			m_mesh->v_array[i].y = new_coord.y;
			m_mesh->v_array[i].z = new_coord.z;
		}

		GLuint texture = -1;
		for (int i = 0; i < m_mesh->f_num; i++)
		{
			if (texture == -1 || texture != m_mesh->f_array[i].material->TexID)
			{
				if (m_mesh->f_array[i].material->map_kd.size() > 0)
				{
					texture = m_mesh->f_array[i].material->TexID;
					//std::cout << " GL_TEXTURE_2D " << m_model->f_array[i].material->TexID << std::endl;
					glBindTexture(GL_TEXTURE_2D, texture);
				}
			}
			draw_poligon(i);
		}
	};

	void draw_poligon(int i)
	{
		glBegin(GL_POLYGON);
		/*if (model->f_array[i].material->kdr) {
			glColor3f(m_model->f_array[i].material->kdr, 
			m_model->f_array[i].material->kdg,	m_model->f_array[i].material->kdb);
		}
		*/
		for (int j = 0; j < m_mesh->f_array[i].fi_num; j++) {

			if (m_mesh->vn_num > 0)
				glNormal3f(
				m_mesh->f_array[i].fi_array[j].vn->x,
				m_mesh->f_array[i].fi_array[j].vn->y,
				m_mesh->f_array[i].fi_array[j].vn->z);

			if (m_mesh->vt_num > 0)
				glTexCoord2f(
				m_mesh->f_array[i].fi_array[j].vt->u,
				m_mesh->f_array[i].fi_array[j].vt->v);

			glVertex3f(
				m_mesh->f_array[i].fi_array[j].v->x,
				m_mesh->f_array[i].fi_array[j].v->y,
				m_mesh->f_array[i].fi_array[j].v->z);
		}
		glEnd();
	};
};

class SphereRender : public Render{
public:
	float m_radius;
	GLUquadricObj* m_quad;

	SphereRender(float r, float g, float b, float radius) : 
		Render(r, g, b),
		m_radius(radius)
	{
		m_quad = gluNewQuadric();
	};

	virtual ~SphereRender()
	{
		gluDeleteQuadric(m_quad);
	};

	virtual void render(float mat[])
	{
		//std::cout << " test " << m_radius << std::endl;
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		glColor3f(m_r, m_g, m_b);
		gluSphere(m_quad, m_radius, 20, 20);
		glColor4f(1.f, 1.f, 1.f, 1.f);
		glPopMatrix();
	};
};

class BoxRender : public Render{
public:
	Vector3<float> m_extent;

	BoxRender(float r, float g, float b, Vector3<float> extent) : 
		Render(r, g, b),
		m_extent(extent)
	{

	};

	virtual void render(float mat[])
	{
		
		glColor3f(m_r, m_g, m_b);
		
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation
		glBegin(GL_QUADS);
		glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
		glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
		glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
		glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
		glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
		glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
		glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
		glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
		glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glEnd();
		glPopMatrix();
	};
};

class PlaineRender : public Render{
public:

	PlaineRender(float r, float g, float b) :
		Render(r, g, b)
	{

	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);
		
		glPushMatrix();
		//glMultMatrixf(mat);     //translation,rotation
		glBegin(GL_QUADS);
		glVertex3f(-1000, 0, 1000);
		glVertex3f(-1000, 0, -1000);
		glVertex3f(1000, 0, -1000);
		glVertex3f(1000, 0, 1000);
		glEnd();
		glPopMatrix();
	};

};

class BoneRender : public Render{
public:
	Vector3<float> m_extent;

	BoneRender(float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b),
		m_extent(extent)
	{

	};

	virtual void render(float mat[])
	{
		

		glPushMatrix();

		glMultMatrixf(mat);     //translation,rotation

		glLineWidth(2.5);
		glColor3f(m_r, m_g, m_b);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glEnd();

		glPointSize(10.0);
		glBegin(GL_POINTS);
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();


		glPopMatrix();
	};

};


class CoordinatesRender : public Render{
public:
	int max_fild;

	CoordinatesRender(int max) :
		Render(1, 1, 1),
		max_fild(max)
	{
	
	};

	virtual void render()
	{

		glPushMatrix();
		glLineWidth(2.5);
		//Red is X-axis red
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		glEnd();

		//Blue is Y-axis green
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		glEnd();

		// Green is Z axis blue
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
		glEnd();

		glLineWidth(1);
		glColor3f(m_r, m_g, m_b);
		for (int i = 0; i <= max_fild; i++)
		{
			//draw line by -x axes
			glBegin(GL_LINES);
			glVertex3f((i*-1), 0, (max_fild*-1));
			glVertex3f((i*-1), 0, max_fild);
			glEnd();
			//draw line by +x axes
			glBegin(GL_LINES);
			glVertex3f(i, 0, (max_fild*-1));
			glVertex3f(i, 0, max_fild);
			glEnd();
			//draw line by -z axes
			glBegin(GL_LINES);
			glVertex3f((max_fild*-1), 0, (i*-1));
			glVertex3f(max_fild, 0, (i*-1));
			glEnd();
			//draw line by +z axes
			glBegin(GL_LINES);
			glVertex3f((max_fild*-1), 0, i);
			glVertex3f(max_fild, 0, i);
			glEnd();
		}

		

		glPopMatrix();
	};

};

class PictureRender : public Render{
public:
	GLuint textureId;
	Vector3<float> position;
	Vector3<float> size;


	PictureRender(const char * texpath, Vector3<float> p, Vector3<float> s) : Render(),
		position(p), size(s)
	{
		textureId = GLoader::LoadTexture(texpath);
		std::cout << "texture " << texpath << std::endl;
		if (textureId == -1)
		{
			std::cout << "texture does not load " << texpath << std::endl;
			assert(false);
		}
		
	};

	virtual void render()
	{
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPushMatrix();
		//glMultMatrixf(mat);     //translation,rotation
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex3f(position.x - size.x, position.y - size.y, 0);
		
		glTexCoord2f(0, 1);
		glVertex3f(position.x - size.x, position.y + size.y, 0);
		
		glTexCoord2f(1, 1);
		glVertex3f(position.x + size.x, position.y + size.y, 0);
		
		glTexCoord2f(1, 0);
		glVertex3f(position.x + size.x, position.y - size.y, 0);
		
		glEnd();
		glPopMatrix();
	};

};


class TextRender : public Render{
public:
	
	std::string m_init_text;
	std::string m_render_text;
	int m_x, m_y;


	TextRender(std::string text, int x, int y) : Render(),
		m_init_text(text), m_render_text(text), m_x(x), m_y(y)
	{

	};

	virtual void render()
	{
		const char * text = m_render_text.data();
		int length = m_render_text.size();
		
		// change the current matrix to PROJECTION
		glMatrixMode(GL_PROJECTION);
		// 16 doubles in stack memory
		double matrix[16];
		// get the values from PROJECTION matrix to local variable
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
		// reset PROJECTION matrix to identity matrix
		glLoadIdentity();
		// orthographic perspective
		glOrtho(0, 800, 0, 600, -5, 5);
		// change current matrix to MODELVIEW matrix again
		glMatrixMode(GL_MODELVIEW);
		// reset it to identity matrix
		glLoadIdentity();
		// push current state of MODELVIEW matrix to stack
		glPushMatrix();
		// reset it again. (may not be required, but it my convention)
		glLoadIdentity();
		// raster position in 2D
		glRasterPos2i(m_x, m_y);
		for (int i = 0; i<length; i++){
			// generation of characters in our text with 9 by 15 GLU font
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
		}
		// get MODELVIEW matrix value from stack
		glPopMatrix();
		// change current matrix mode to PROJECTION
		glMatrixMode(GL_PROJECTION);
		// reset
		glLoadMatrixd(matrix);
		// change current matrix mode to MODELVIEW
		glMatrixMode(GL_MODELVIEW);
	};

};

#endif /* RENDER_H_ */