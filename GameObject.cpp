
#include "GameObject.h"

/*void GameObject::load_texture(const char * dir_name)
{
	std::cout << " GameObject::load_texture " << std::endl;

	mat_struct* mat = get_m_array();
	int mat_num = get_m_num();

	for (int i = 0; i < mat_num; i++) {
		if (mat[i].map_kd.size() > 0) {
			const char * file_name = mat[i].map_kd.c_str();
			
			int bufferSize = strlen(dir_name) + strlen(file_name) + 1;
			// allocate enough memory for the concatenated string:
			char* path = new char[bufferSize];
			// copy strings one and two over to the new buffer:
			strcpy(path, dir_name);
			strcat(path, file_name);

			GLuint texture = GLoader::LoadTexture(path);
			if (texture == -1) {
				std::cout << " Texture loading error: "
					<< mat[i].newmtl << " " << mat[i].map_kd << " "
					<< std::endl;
				continue;
			}
			mat[i].TexID = texture;
			// delete buffer:
			delete[] path;
		}
	}
}
*/
	

GameObject::~GameObject() {
	for (int i = 0; i < childs.size(); i++) {
		delete childs[i];
	}

	//delete[] model->v_array;

	//delete[] m_array;
	//for (int i = 0; i < f_num; i++) {
	//	delete[] f_array[i].fi_array;
	//}
	//delete[] f_array;
}




/*void GameObject::update() {

	matrix.init();

	matrix.translate(m_body.m_position.x, m_body.m_position.y, m_body.m_position.z);
	matrix.rotate(m_body.m_angle.x, m_body.m_angle.y, m_body.m_angle.z);

	for (int i = 0; i < childs.size(); i++) {
		childs[i]->update();
	}

	//std::cout << " position 2 x " << m_body.m_position.x << " y " << m_body.m_position.y << " z " << m_body.m_position.z << std::endl;
	//std::cout << " angle 2 x " << m_body.m_angle.x << " y " << m_body.m_angle.y << " z " << m_body.m_angle.z << std::endl;
	//std::cout << " direction 2 x " << m_body.m_direction.x << " y " << m_body.m_direction.y << " z " << m_body.m_direction.z << std::endl;

}
*/

/*void GameObject::draw_poligon(int i)
{
	glBegin(GL_POLYGON);

	//if (model->f_array[i].material->kdr) {
	//	std::cout << " Collor " << std::endl;
	//	glColor3f(
	//		model->f_array[i].material->kdr,
	//		model->f_array[i].material->kdg,
	//		model->f_array[i].material->kdb);
	//}
	
	for (int j = 0; j < model->f_array[i].fi_num; j++) {

		if (model->vn_num > 0)
			glNormal3f(
				model->f_array[i].fi_array[j].vn->x, 
				model->f_array[i].fi_array[j].vn->y, 
				model->f_array[i].fi_array[j].vn->z);

		if (model->vt_num > 0)
			glTexCoord2f(
				model->f_array[i].fi_array[j].vt->u,
				model->f_array[i].fi_array[j].vt->v);

		glVertex3f(
			model->f_array[i].fi_array[j].v->x,
			model->f_array[i].fi_array[j].v->y,
			model->f_array[i].fi_array[j].v->z);
	}

	glEnd();
}
*/

/*void GameObject::draw() {

	for (int i = 0; i < model->v_num; i++) {
		Vector3<float> new_coord = matrix.vProduct(model->v_array[i].ox, model->v_array[i].oy, model->v_array[i].oz);
		model->v_array[i].x = new_coord.x;
		model->v_array[i].y = new_coord.y;
		model->v_array[i].z = new_coord.z;
	}

	//debug
	//if (f_array[0].group.compare("obstacle") == 0)
	//for (int j = 0; j < f_array[0].fi_num; j++) {
	//cout << "p" << j
	//<< " x " << f_array[0].fi_array[j].v->x
	//<< " y " << f_array[0].fi_array[j].v->y
	//<< " z " << f_array[0].fi_array[j].v->z << endl;
	//}
	
	GLuint texture = -1;
	for (int i = 0; i < model->f_num; i++) 
	{

		if (texture == -1 || texture != model->f_array[i].material->TexID)
		{
			if (model->f_array[i].material->map_kd.size() > 0)
			{
				texture = model->f_array[i].material->TexID;
				//std::cout << " GL_TEXTURE_2D " << model->f_array[i].material->TexID << std::endl;
				glBindTexture(GL_TEXTURE_2D, texture);
			}
		}

		draw_poligon(i);
	}

	for (int i = 0; i < childs.size(); i++) {
		childs[i]->draw();
	}
}
*/