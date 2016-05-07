#ifndef STATICMODELLOADER_H_
#define STATICMODELLOADER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include <GL/glut.h>

#include "ModelTypes.h"

using namespace std;

class StaticModelLoader {
private:
	/* 
		coordinates of vertices
	*/
	int v_num;
	v_struct* v_array;
	/* 
		coordinates of textures
	*/
	int vt_num;
	vt_struct* vt_array;
	/* 
		coordinates of normals 
	*/
	int vn_num;
	vn_struct* vn_array;
	/*
		polygons
	*/
	int f_num;
	f_struct* f_array;
	/*
		materials
	*/
	int mat_num;
	mat_struct* mat_array;
	/*
		models
	*/
	//int mod_num;
	//mod_struct* mod_array;

	/*
		cursor to the file of models (obj)
	*/
	std::ifstream infile;
	std::streampos prev_pos;
	/*
		cursor to the file of materials
	*/
	std::ifstream m_infile;
	std::streampos m_prev_pos;

	/*
		radius of object for the collision definition
	*/
	float rx = 0, ry = 0, rz = 0;

	void vload();
	void mload();
	void fload();

public:
	
	StaticModelLoader(char* path, char *mpath);
	~StaticModelLoader();

	v_struct* get_v() { return v_array; }
	int get_v_num() { return v_num; }

	vt_struct* get_vt() { return vt_array; }
	int get_vt_num() { return vt_num; }

	vn_struct* get_vn() { return vn_array; }
	int get_vn_num() { return vn_num; }

	f_struct* get_f() { return f_array; }
	int get_f_num() { return f_num; }

	mat_struct* get_mat() { return mat_array; }
	int get_mat_num() { return mat_num; }

	//mod_struct* get_mod() {
	//	return mod_array;
	//}

	virtual float get_rx() { return rx; }
	virtual float get_ry() { return ry; }
	virtual float get_rz() { return rz; }
	
	void load_texture(const char * dir_name);
	void render();
};


struct ModelsStruct
{
	int v_num = 0;
	v_struct *v_array;

	int vt_num;
	vt_struct* vt_array;

	int vn_num;
	vn_struct* vn_array;

	int f_num = 0;
	f_struct *f_array;

	int m_num = 0;
	mat_struct *m_array;

	float irx = 0, iry = 0, irz = 0; //initial radius
	float rx = 0, ry = 0, rz = 0; //radius	

	StaticModelLoader * loader;

	bool current = false;
};

ModelsStruct *CopyModel(StaticModelLoader* model);

#endif /* STATICMODELLOADER_H_ */