#include "StaticModelLoader.h"
#include "gloader.h"

StaticModelLoader::StaticModelLoader(char* path, char *mpath)
{
	m_infile.open(mpath);
	if (!m_infile) {
		cout << "Cannot open material file!\n";
		throw 1;
	}

	infile.open(path); //"res/car.obj"
	if (!infile) {
		cout << "Cannot open file!\n";
		throw 1;
	}

	mload();

	vload();

	infile.clear();
	infile.seekg(0, ios::beg);

	fload();

	infile.close();
	m_infile.close();

	//debug models
	std::cout << " verticies " << v_num
		<< " textures " << vt_num
		<< " normals " << vn_num
		<< " polygones " << f_num
		<< std::endl;
}

StaticModelLoader::~StaticModelLoader()
{
	delete[] v_array;
	delete[] vt_array;
	delete[] vn_array;
	delete[] f_array;

	delete[] mat_array;
	//delete[] mod_array;
}

void StaticModelLoader::render()
{
	for (int i = 0; i < f_num; i++) {
		if (f_array[i].material->map_kd.size() > 0)
			glBindTexture(GL_TEXTURE_2D, f_array[i].material->TexID);

		glBegin(GL_POLYGON);
		for (int j = 0; j < f_array[i].fi_num; j++) {

			glTexCoord2f(
				f_array[i].fi_array[j].vt->u,
				f_array[i].fi_array[j].vt->v);

			glVertex3f(
				f_array[i].fi_array[j].v->x,
				f_array[i].fi_array[j].v->y,
				f_array[i].fi_array[j].v->z);
		}

		glEnd();
	}
}

void StaticModelLoader::vload()
{
	v_num = 0, vt_num = 0, vn_num = 0;

	std::string marker;
	std::string marker1("v"), marker2("vt"), marker3("vn");

	double u, v;
	double x, y, z;

	std::string line;
	/*
	count number of vertices
	*/
	while (std::getline(infile, line)) {

		std::istringstream iss(line);
		iss >> marker;

		if (marker.compare(marker1) == 0) {
			v_num++;
			continue;
		}

		if (marker.compare(marker2) == 0) {
			vt_num++;
			continue;
		}

		if (marker.compare(marker3) == 0) {
			vn_num++;
			continue;
		}
	}


	/*
	return cursor to the beginning  of the file
	*/
	infile.clear();
	infile.seekg(0, ios::beg);

	/*
	allocate memory
	*/
	v_array = (v_struct*)calloc(v_num, sizeof(v_struct));
	vt_array = (vt_struct*)calloc(vt_num, sizeof(vt_struct));
	vn_array = (vn_struct*)calloc(vn_num, sizeof(vn_struct));

	int iv = 0, ivt = 0, ivn = 0;
	while (std::getline(infile, line)) {

		std::istringstream iss(line);
		iss >> marker;

		/*
		save coordinates of vertices
		*/
		if (marker.compare(marker1) == 0) {
			iss >> x >> y >> z;

			v_array[iv].ox = x, v_array[iv].x = x;
			v_array[iv].oy = y, v_array[iv].y = y;
			v_array[iv].oz = z, v_array[iv].z = z;
			v_array[iv].ow = 1, v_array[iv].w = 1;
			v_array[iv].index = iv;

			if (fabs(x) > rx) rx = fabs(x);
			if (fabs(y) > ry) ry = fabs(y);
			if (fabs(z) > rz) rz = fabs(z);

			iv++;
			continue;
		}
		/*
		save coordinates of textures
		*/
		if (marker.compare(marker2) == 0) {
			iss >> u >> v;

			vt_array[ivt].u = u;
			vt_array[ivt].v = v;
			vt_array[ivt].w = 1;
			vt_array[ivt].index = ivt;

			ivt++;
			continue;
		}
		/*
		save coordinates of normals
		*/
		if (marker.compare(marker3) == 0) {
			iss >> x >> y >> z;

			vn_array[ivn].x = x;
			vn_array[ivn].y = y;
			vn_array[ivn].z = z;
			vn_array[ivn].index = ivn;

			ivn++;
			continue;
		}
	}
}

void StaticModelLoader::mload()
{
	mat_num = 0;

	std::string marker, material_name;
	std::string marker1("Kd"), marker2("Ks"), marker3("Ns");
	std::string marker4("d"), marker5("illum");
	std::string marker6("map_Kd"), marker7("newmtl");

	std::string line;
	/*
	count number of materials
	*/
	while (std::getline(m_infile, line)) {
		std::istringstream iss(line);
		if ((iss >> marker >> material_name) && (marker.compare(marker7) == 0)) {
			mat_num++;
			//cout << "v " << dot_num << " x " << x << " y " << y << " z " << z << "\n";
		}
	}

	/*
	return cursor to the beginning  of the file
	*/
	m_infile.clear();
	m_infile.seekg(0, ios::beg);

	/*
	allocate memory
	*/
	mat_array = (mat_struct*)calloc(mat_num, sizeof(mat_struct));

	int i = 0; bool p_flag = false;
	while (std::getline(m_infile, line)) {

		std::istringstream iss(line);
		iss >> marker;

		if (marker.compare(marker7) == 0) {
			/*
			increase only if the first material is already parsed
			*/
			if (p_flag)
				i++;
			/*
			save the material name
			*/
			iss >> mat_array[i].newmtl;
			mat_array[i].index = i;
			/*
			set up that the first material have parsed
			*/
			p_flag = true;
			continue;
		}

		if (marker.compare(marker1) == 0) {
			/*
			set ub ambient collor
			*/
			iss >> mat_array[i].kdr >> mat_array[i].kdg >> mat_array[i].kdb;
			continue;
		}

		if (marker.compare(marker2) == 0) {
			/*
			set up specular collor
			*/
			iss >> mat_array[i].ksr >> mat_array[i].ksg >> mat_array[i].ksb;
			continue;
		}

		if (marker.compare(marker3) == 0) {
			/*
			set up the shininess of the material
			*/
			iss >> mat_array[i].ns;
			continue;
		}

		if (marker.compare(marker4) == 0) {
			/*
			set up the transparency of the material
			*/
			iss >> mat_array[i].d;
			continue;
		}

		if (marker.compare(marker5) == 0) {
			/*
			set up the illumination of the model
			*/
			iss >> mat_array[i].illum;
			continue;
		}

		if (marker.compare(marker6) == 0) {
			/*
			set up the name a file containing a texture map
			*/
			iss >> mat_array[i].map_kd;
			continue;
		}
	}
}

void StaticModelLoader::fload()
{
	f_num = 0;
	//mod_num = 0;

	std::string marker;
	std::string marker1("f"), marker2("g");
	std::string marker3("usemtl");

	std::string line;
	/*
	count numbers
	*/
	while (std::getline(infile, line)) {

		std::istringstream iss(line);
		iss >> marker;

		if (marker.compare(marker1) == 0) {
			f_num++;
			continue;
		}

		/*if (marker.compare(marker2) == 0) {
		mod_num++;
		continue;
		}
		*/
	}

	/*
	return cursor to the beginning  of the file
	*/
	infile.clear();
	infile.seekg(0, ios::beg);

	/*
	allocate memory
	*/
	//mod_array = (mod_struct*)calloc(mod_num, sizeof(mod_struct));
	f_array = (f_struct*)calloc(f_num, sizeof(f_struct));

	/*
	material name
	*/
	std::string mat_name, group_name;
	f_item* i_array;

	int i_face = 0;
	while (std::getline(infile, line)) {
		//cout << "line " << line << endl;

		std::istringstream iss_f(line); // for parsing values
		std::istringstream iss_n(line); // for parsing count

		iss_f >> marker;

		if (marker.compare(marker2) == 0) {
			/*
			new group (model)
			*/
			//iss_f >> mod_array[i_group].name;
			iss_f >> group_name;
			continue;
		}

		if (marker.compare(marker3) == 0) {
			/*
			new material
			*/
			iss_f >> mat_name;
			continue;
		}


		if (marker.compare(marker1) == 0) {

			std::string f1;



			/*
			get number of points for polygon (exclude f)
			*/
			int i_num = -1;
			while (!(iss_n >> f1).fail()) {
				i_num++;
			}

			/*
			new Polygon
			*/
			f_array[i_face].m_name = mat_name;
			f_array[i_face].group = group_name;
			/*
			find material and refer to it
			*/
			for (int imat = 0; imat < mat_num; imat++) {
				if (mat_name.compare(mat_array[imat].newmtl) == 0) {
					f_array[i_face].material = &mat_array[imat];
					break;
				}
			}

			/*
			points of polygon
			*/
			f_array[i_face].fi_num = i_num;

			/*cout << " m_name " << f_array[i_face].m_name
			<< " group " << f_array[i_face].group
			<< " material " << f_array[i_face].material
			<< " i_num " << f_array[i_face].fi_num
			<< endl;
			*/
			/*
			allocate memory for the array of points for polygon
			*/
			i_array = (f_item*)calloc(i_num, sizeof(f_item));

			i_num = 0;
			while (!(iss_f >> f1).fail()) {

				std::string f_item1;
				int vf1, vnf1, vtf1;
				int n_item1 = 0;

				std::istringstream iss_f1(f1);
				while (std::getline(iss_f1, f_item1, '/')) {

					if (n_item1 == 0)
						istringstream(f_item1) >> vf1;

					if (n_item1 == 1)
						istringstream(f_item1) >> vtf1;

					if (n_item1 == 2)
						istringstream(f_item1) >> vnf1;

					n_item1++;
				}

				if (n_item1 > 0)
					i_array[i_num].v = &v_array[(vf1 - 1)];
				if (n_item1 > 1)
					i_array[i_num].vt = &vt_array[(vtf1 - 1)];
				if (n_item1 > 2)
					i_array[i_num].vn = &vn_array[(vnf1 - 1)];

				i_num++;
			}

			f_array[i_face].fi_array = i_array;
			i_face++;
			continue;
		}
	}
	/*
	refer last array of polygones to group
	*/
	//mod_array[i_group].f_array = f_array;
}

void StaticModelLoader::load_texture(const char * dir_name)
{
	std::cout << " GameObject::load_texture " << std::endl;

	//mat_struct* mat = mat_array;
	//int mat_num = get_m_num();

	for (int i = 0; i < mat_num; i++) {
		if (mat_array[i].map_kd.size() > 0) {
			const char * file_name = mat_array[i].map_kd.c_str();

			int bufferSize = strlen(dir_name) + strlen(file_name) + 1;
			// allocate enough memory for the concatenated string:
			char* path = new char[bufferSize];
			// copy strings one and two over to the new buffer:
			strcpy(path, dir_name);
			strcat(path, file_name);

			GLuint texture = GLoader::LoadTexture(path);
			if (texture == -1) {
				std::cout << " Texture loading error: "
					<< mat_array[i].newmtl << " " << mat_array[i].map_kd << " "
					<< std::endl;
				continue;
			}
			mat_array[i].TexID = texture;
			// delete buffer:
			delete[] path;
		}
	}
}

ModelsStruct *CopyModel(StaticModelLoader* sml)
{
	ModelsStruct *model = new ModelsStruct;
	model->v_num = sml->get_v_num();
	model->vt_num = sml->get_vt_num();
	model->vn_num = sml->get_vn_num();
	model->m_num = sml->get_mat_num();
	model->f_num = sml->get_f_num();

	model->v_array = (v_struct*)calloc(model->v_num, sizeof(v_struct));
	model->vt_array = (vt_struct*)calloc(model->vt_num, sizeof(vt_struct));
	model->vn_array = (vn_struct*)calloc(model->vn_num, sizeof(vn_struct));
	model->m_array = (mat_struct*)calloc(model->m_num, sizeof(mat_struct));
	model->f_array = (f_struct*)calloc(model->f_num, sizeof(f_struct));


	v_struct* v_temp = sml->get_v();
	vt_struct* vt_temp = sml->get_vt();
	vn_struct* vn_temp = sml->get_vn();
	mat_struct* m_temp = sml->get_mat();
	f_struct* f_temp = sml->get_f();

	for (int i = 0; i < model->v_num; i++)
	{
		model->v_array[i].ox = v_temp[i].ox, model->v_array[i].x = v_temp[i].x;
		model->v_array[i].oy = v_temp[i].oy, model->v_array[i].y = v_temp[i].y;
		model->v_array[i].oz = v_temp[i].oz, model->v_array[i].z = v_temp[i].z;
		model->v_array[i].ow = v_temp[i].ow, model->v_array[i].w = v_temp[i].w;
		model->v_array[i].index = i;
	}

	for (int i = 0; i < model->vt_num; i++)
	{
		model->vt_array[i].u = vt_temp[i].u;
		model->vt_array[i].v = vt_temp[i].v;
		model->vt_array[i].w = vt_temp[i].w;
		model->vt_array[i].index = i;
	}

	for (int i = 0; i < model->vn_num; i++)
	{
		model->vn_array[i].x = vn_temp[i].x;
		model->vn_array[i].y = vn_temp[i].y;
		model->vn_array[i].z = vn_temp[i].z;
		model->vn_array[i].index = i;
	}

	for (int i = 0; i < model->m_num; i++)
	{
		std::cout << " Copy materialsl "
			<< m_temp[i].TexID << " " << m_temp[i].newmtl << " "
			<< std::endl;

		model->m_array[i].TexID = m_temp[i].TexID;
		model->m_array[i].newmtl = m_temp[i].newmtl;

		model->m_array[i].kar = m_temp[i].kar;
		model->m_array[i].kag = m_temp[i].kag;
		model->m_array[i].kab = m_temp[i].kab;

		model->m_array[i].kdr = m_temp[i].kdr;
		model->m_array[i].kdg = m_temp[i].kdg;
		model->m_array[i].kdb = m_temp[i].kdb;

		model->m_array[i].ksr = m_temp[i].ksr;
		model->m_array[i].ksg = m_temp[i].ksg;
		model->m_array[i].ksb = m_temp[i].ksb;

		model->m_array[i].illum = m_temp[i].illum;
		model->m_array[i].ns = m_temp[i].ns;
		model->m_array[i].d = m_temp[i].d;
		model->m_array[i].map_kd = m_temp[i].map_kd;
		model->m_array[i].index = m_temp[i].index;
	}

	for (int i = 0; i < model->f_num; i++)
	{
		model->f_array[i].group = f_temp[i].group;
		model->f_array[i].m_name = f_temp[i].m_name;

		model->f_array[i].material = &model->m_array[f_temp[i].material->index];

		model->f_array[i].fi_num = f_temp[i].fi_num;

		if (f_temp[i].fi_num > 0)
			model->f_array[i].fi_array = (f_item*)calloc(f_temp[i].fi_num, sizeof(f_item));

		for (int j = 0; j < f_temp[i].fi_num; j++)
		{
			if (model->v_num > 0)
				model->f_array[i].fi_array[j].v = &model->v_array[f_temp[i].fi_array[j].v->index];

			if (model->vt_num > 0)
				model->f_array[i].fi_array[j].vt = &model->vt_array[f_temp[i].fi_array[j].vt->index];

			if (model->vn_num > 0)
				model->f_array[i].fi_array[j].vn = &model->vn_array[f_temp[i].fi_array[j].vn->index];
		}
	}

	model->irx = model->rx = sml->get_rx();
	model->iry = model->ry = sml->get_ry();
	model->irz = model->rz = sml->get_rz();

	model->loader = sml;
	return model;
}
