
#ifndef MODELTYPES_H_
#define MODELTYPES_H_

/*
* http://web.cse.ohio-state.edu/~hwshen/581/Site/Lab3_files/Labhelp_Obj_parser.htm
*/

#include <GL/glut.h>

/*
Materials
*/
typedef struct {
	GLuint TexID;
	//newmtl Start a definition of a new material
	std::string newmtl;
	//Ka ambient color(r, g, b)
	double kar, kag, kab;
	//Kd diffuse color(r, g, b)
	double kdr, kdg, kdb;
	//Ks specular color(r, g, b)
	double ksr, ksg, ksb;
	//illum Define the illumination model : 
	//illum = 1 a flat material with no specular highlights, 
	//illum = 2 denotes the presence of specular highlights
	int illum;
	//Ns shininess of the material
	double ns;
	//d or Tr the transparency of the material
	double d;
	//map_Ka names a file containing a texture map, which should just be an ASCII dump of RGB values
	std::string map_kd;

	int index;
} mat_struct;

/*
Coordinats of Verticies
*/
typedef struct {
	double ox, oy, oz, ow;
	double x, y, z, w;
	int index;
} v_struct;

/*
Coordinats of textures
*/
typedef struct {
	double u, v, w;
	int index;
} vt_struct;

/*
Coordinats of Normals
*/
typedef struct {
	long double x, y, z;
	int index;
} vn_struct;

/*
Point of Polygon
*/
typedef struct {
	v_struct *v;
	vt_struct *vt;
	vn_struct *vn;
} f_item;

typedef struct {
	float r;
	float b;
	float g;
	int index;
} collor_struct;

/*
Poligons
*/
typedef struct {
	std::string group;
	std::string m_name;
	mat_struct* material;
	collor_struct *collor;

	f_item* fi_array;
	int fi_num;
} f_struct;



#endif /* MODELTYPES_H_ */