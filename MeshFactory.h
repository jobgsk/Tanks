#ifndef MESH_FACTORY_H_
#define MESH_FACTORY_H_

#include "render.h"

class MeshFactory {

	static MeshRender *obstacle1_render;
	static MeshRender *obstacle2_render;
	static MeshRender *obstacle3_render;
	static MeshRender *obstacle4_render;

	static MeshRender *grass_render;

	static MeshRender *tower_render;
	static MeshRender *tank_render;

public:

	static MeshRender* getObstacle1()
	{
		if (!obstacle1_render) {
			obstacle1_render = new MeshRender(
				"3DModels/buildings/1/b1.obj", "3DModels/buildings/1/b1.mtl", "3DModels/buildings/1/");
		}
		return obstacle1_render;
	};

	static MeshRender* getObstacle2()
	{
		if (!obstacle2_render) {
			obstacle2_render = new MeshRender(
				"3DModels/buildings/2/b2.obj", "3DModels/buildings/2/b2.mtl", "3DModels/buildings/2/");
		}
		return obstacle2_render;
	};

	static MeshRender* getObstacle3()
	{
		if (!obstacle3_render) {
			obstacle3_render = new MeshRender(
				"3DModels/buildings/3/b3.obj", "3DModels/buildings/3/b3.mtl", "3DModels/buildings/3/");
		}
		return obstacle3_render;
	};

	static MeshRender* getObstacle4()
	{
		if (!obstacle4_render) {
			obstacle4_render = new MeshRender(
				"3DModels/buildings/4/b4.obj", "3DModels/buildings/4/b4.mtl", "3DModels/buildings/4/");
		}
		return obstacle4_render;
	};

	static MeshRender* getTower()
	{
		if (!tower_render) {
			tower_render = new MeshRender(
				"3DModels/tank1/top/Tire.obj", "3DModels/tank1/top/Tire.mtl", "3DModels/tank1/top/");
		}
		return tower_render;
	};

	static MeshRender* getTank()
	{
		if (!tank_render) {
			tank_render = new MeshRender(
				"3DModels/tank1/buttom/Tire.obj", "3DModels/tank1/buttom/Tire.mtl",	"3DModels/tank1/buttom/");
		}
		return tank_render;
	};

	static MeshRender* getGrass()
	{
		if (!grass_render) {
			grass_render = new MeshRender(
				"3DModels/grass/grass.obj", "3DModels/grass/grass.mtl", "3DModels/grass/");
		}
		return grass_render;
	};

};
#endif /* MESH_FACTORY_H_ */