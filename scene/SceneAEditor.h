#ifndef ANIMATION_EDITOR_H_
#define ANIMATION_EDITOR_H_

#include "Scene.h"
//#include "../Settings.h"
#include "../model/AnimationModel.h"
#include "../model/TextAnimationEditor.h"
#include "../AnimationParser.h"

class SceneAEditor : public Scene {
public:

	//tanks::AxisType current_axis;

	std::vector<TextAnimationEditor*> tlist;
	std::vector<AnimationModel*> mlist;
	int current;

	TextRender * info1;
	CoordinatesRender * crender;
	bool camera_ctrl;

	Vector3<float> m_axis;

	SceneAEditor(SceneType level, tanks::GameSettings * settings)
		:Scene(level, settings)
	{
		
	};

	~SceneAEditor()
	{
		Scene::~Scene();
	};

	void init()
	{
		redispaly = true;
		if (inited)
			return;

		crender = new CoordinatesRender(10);
		info1 = new TextRender("Mode: ", 450, 570);

		AnimationParser aparser = AnimationParser("3DModels/animation/1.txt");
		mlist = aparser.load();

		for (int i = 0; i < mlist.size(); i++)
		{
			std::cout << "animation " << mlist[i]->m_id << " " << std::endl;
			mlist[i]->test();
		}
			
		
		//BoneRender * render1 = new BoneRender(1, 0, 0, Vector3<float>(2, 0, 2));
		

		
		
		//TextAnimationEditor * menu1 = new TextAnimationEditor("Bone 1:", 50, 550, body1, tanks::MenuType::EMPTY);
		//tlist.push_back(menu1);

		
		camera = new Camera(new GameObject(0, tanks::ModelType::CAMERA), 15.0);
		camera->set_behind();
		camera_ctrl = false;

		m_axis = Vector3<float>(0.0, 1.0, 0.0);

		current = 0;
		set_init();
	};

	void display()
	{
		crender->render();

		for (int i = 0; i < mlist.size(); i++)
		{
			mlist[i]->draw();
		}

		/*for (int i = 0; i < tlist.size(); i++)
		{
			tlist[i]->render();
		}
		
		AnimationBone * cbone = blist[current];
		std::stringstream sstm1;
		sstm1 << info1->m_init_text;
		if (m_axis.x > 0.0)
			sstm1 << "bone X ";
		if (m_axis.y > 0.0)
			sstm1 << "bone Y ";
		if (m_axis.z > 0.0)
			sstm1 << "bone Z ";

		if (camera_ctrl)
			sstm1 << " camera active";
		
		info1->m_render_text = sstm1.str();
		info1->render();
		*/

	};

	void play(float duration, tanks::MoveControlls * moving)
	{
		/*if (camera_ctrl)
		{	
			if (moving->move_left == true)
			{
				camera->m_y_angle_diff += 0.5;
				moving->move_left = false;
			}
			else if (moving->move_right == true)
			{
				camera->m_y_angle_diff -= 0.5;
				moving->move_right = false;
			}

			camera->play(duration);
			return;
		}
		*/
		if (camera_ctrl)
			camera->play(duration);

		//AnimationBone * cbone = blist[current];

		/*if (moving->move_forvard == true)
		{
			//cbone->m_body->m_position += 
			//cbone->sf->set_force(2.5);
			moving->move_forvard = false;
		}
		else if (moving->move_back == true)
		{
			//cbone->sf->set_force(-2.5);
			moving->move_back = false;
		}
		*/

		/*if (moving->move_left == true)
		{
			cbone->af->set_force(7.5);
			moving->move_left = false;
		}
		else if (moving->move_right == true)
		{
			cbone->af->set_force(-7.5);
			moving->move_right = false;
		}
		*/
		//cbone->play(duration);
		return;
	};

	void update()
	{
		/*for (int i = 0; i < blist.size(); i++)
		{
			GameObject * go = blist[i];
			if (go->state == GameObject::ObjectState::CHANGED)
			{
				go->update();
				go->state = GameObject::ObjectState::ACTIVE;
				redispaly = true;
			}
		}
		*/
	};

	void keyboard(tanks::ButtonControlls button)
	{
		if (camera_ctrl && button == tanks::ButtonControlls::MOVE_LEFT)
		{
			camera->m_y_angle_diff += 0.5;
			return;
		}

		if (camera_ctrl && button == tanks::ButtonControlls::MOVE_RIGHT)
		{
			camera->m_y_angle_diff -= 0.5;
			return;
		}

		/*AnimationBone * cbone = blist[current];

		if (button == tanks::ButtonControlls::MOVE_UP)
		{
			cbone->m_body->m_position += m_axis;
			return;
		}

		if (button == tanks::ButtonControlls::MOVE_DOWN)
		{
			cbone->m_body->m_position -= m_axis;
			return;
		}


		if (button == tanks::ButtonControlls::TURN_LEFT)
		{
			cbone->af->set_force(m_axis * tanks::grad_to_rad(7.5));
			return;
		}

		if (button == tanks::ButtonControlls::TURN_RIGHT)
		{
			cbone->af->set_force(m_axis  * -tanks::grad_to_rad(7.5));
			return;
		}
		*/

		if (button == tanks::ButtonControlls::X_AXIS)
		{
			m_axis = Vector3<float>(1.0, 0.0, 1.0);
			return;
		}
			
		if (button == tanks::ButtonControlls::Y_AXIS)
		{
			m_axis = Vector3<float>(0.0, 1.0, 0.0);
			return;
		}
			
		
		if (button == tanks::ButtonControlls::Z_AXIS)
		{
			m_axis = Vector3<float>(0.0, 0.0, 1.0);
			return;
		}
			
		
		if (button == tanks::ButtonControlls::CAMERA_CTRL)
		{
			camera_ctrl = camera_ctrl ? false : true;
			return;
		}
			

		if (button == tanks::ButtonControlls::SHOW_MAP)
		{
			camera->m_distance = 1;
			camera->set_ontop();
			return;
		}
		
		if (button == tanks::ButtonControlls::SHOW_GAME)
		{
			camera->m_distance = 5;
			camera->set_behind();
			return;
		}
			
	};
};

#endif /* ANIMATION_EDITOR_H_ */
