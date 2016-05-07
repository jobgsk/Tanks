#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <iostream>
#include <vector>

#include "scene/SceneLevel.h"
#include "scene/SceneMenu.h"
#include "scene/SceneLoading.h"
#include "scene/SceneSettings.h"
#include "scene/SceneHelp.h"
#include "scene/SceneAEditor.h"

#include "TankExeptions.h"

class SceneManager {

private:
	std::vector<Scene*> scenes;
	Scene::SceneType current_type;
	tanks::GameSettings * game_settings;

public:
	tanks::MoveControlls * moving;

	SceneManager()
	{
		game_settings = new tanks::GameSettings;
		game_settings->mMusic = new sf::Music;
		if (!game_settings->mMusic->openFromFile("3DModels/Music/MissionTheme.ogg"))
			std::cout << " MissionTheme file not found " << std::endl;

		sf::SoundBuffer * buffer1 = new sf::SoundBuffer;
		sf::SoundBuffer * buffer2 = new sf::SoundBuffer;

		// Load it from a file
		if (!buffer1->loadFromFile("3DModels/Sound/AlliedGunfire.wav"))
			std::cout << " AlliedGunfire file not found " << std::endl;

		if (!buffer2->loadFromFile("3DModels/Sound/EnemyGunfire.wav"))
			std::cout << " EnemyGunfire file not found " << std::endl;

		/*mSoundBuffers.load(SoundEffect::Explosion1, "Media/Sound/Explosion1.wav");
		mSoundBuffers.load(SoundEffect::Explosion2, "Media/Sound/Explosion2.wav");
		mSoundBuffers.load(SoundEffect::CollectPickup, "Media/Sound/CollectPickup.wav");
		mSoundBuffers.load(SoundEffect::Button, "Media/Sound/Button.wav");
		*/

		sf::Sound * sound1 = new sf::Sound;
		sf::Sound * sound2 = new sf::Sound;

		// Create a sound source and bind it to the buffer
		sound1->setBuffer(*buffer1);
		sound2->setBuffer(*buffer2);

		game_settings->sound1 = sound1;
		game_settings->sound2 = sound2;
		game_settings->bullet = tanks::BulletType::TYPE1;

		SceneMenu* menu = new SceneMenu(Scene::SceneType::MENU, game_settings);
		SceneLevel* level1 = new SceneLevel(Scene::SceneType::LEVEL1, game_settings);
		SceneLoading* loading = new SceneLoading(Scene::SceneType::LOADING, game_settings);
		SceneSettings* settings = new SceneSettings(Scene::SceneType::SETTINGS, game_settings);
		SceneHelp* help = new SceneHelp(Scene::SceneType::HELP, game_settings);
		SceneAEditor * aeditor = new SceneAEditor(Scene::SceneType::AEDITOR, game_settings);
			
		scenes.push_back(level1);
		scenes.push_back(menu);
		scenes.push_back(loading);
		scenes.push_back(settings);
		scenes.push_back(help);
		scenes.push_back(aeditor);

		current_type = Scene::SceneType::MENU;
	};
	
	Scene* getScene(Scene::SceneType type)
	{
		for (int i = 0; i < scenes.size(); i++)
		{
			if (scenes[i]->getType() == type)
				return scenes[i];
		}
		return NULL;
	};

	Scene* getCurrent()
	{
		Scene* current_scene = getScene(current_type);
		if (current_scene == NULL)
			return NULL;

		return current_scene;
	};

	void init_scene()
	{
		Scene* current_scene = getScene(current_type);
		if (current_scene == NULL)
			return;

		if (current_type == Scene::SceneType::LOADING && current_scene->inited)
		{
			current_type = Scene::SceneType::LEVEL1;
			current_scene = getScene(current_type);
		}
			
		if (!current_scene->inited)
			current_scene->init();
	};

	void redefine_scene(Scene::SceneType type)
	{
		Scene* current_scene = getScene(type);
		if (current_scene == NULL)
			return;

		if (current_type == Scene::SceneType::LEVEL1)
		{
			SceneLevel * level_scene = (SceneLevel *)current_scene;
			level_scene->redefine();
			return;
		}
	};

	void keyboard(tanks::ButtonControlls button)
	{
		Scene* current_scene = getCurrent();
		
		if (current_type == Scene::SceneType::LEVEL1)
		{
			if (button == tanks::ButtonControlls::ESCAPE)
			{
				redefine_scene(Scene::SceneType::LEVEL1);
				current_type = Scene::SceneType::MENU;
				return;
			}
		}

		if (current_type == Scene::SceneType::SETTINGS)
		{
			if (button == tanks::ButtonControlls::ESCAPE)
			{
				current_type = Scene::SceneType::MENU;
				return;
			}
		}

		if (current_type == Scene::SceneType::HELP)
		{
			if (button == tanks::ButtonControlls::ESCAPE)
			{
				current_type = Scene::SceneType::MENU;
				return;
			}
		}

		if (current_type == Scene::SceneType::AEDITOR)
		{
			if (button == tanks::ButtonControlls::ESCAPE)
			{
				current_type = Scene::SceneType::MENU;
				return;
			}
		}

		if (current_type == Scene::SceneType::MENU)
		{
			if (button == tanks::ButtonControlls::ESCAPE)
			{
				throw ExitException();
			}

			SceneMenu* menu_scene = (SceneMenu *)current_scene;
			if (button == tanks::ButtonControlls::ENTER) // enter key
			{
				if (menu_scene->get_current() == tanks::MenuType::PLAY)
				{
					current_type = Scene::SceneType::LOADING;
					return;
				}

				if (menu_scene->get_current() == tanks::MenuType::HELP)
				{
					current_type = Scene::SceneType::HELP;
					return;
				}

				if (menu_scene->get_current() == tanks::MenuType::SETTINGS)
				{
					current_type = Scene::SceneType::SETTINGS;
					return;
				}

				if (menu_scene->get_current() == tanks::MenuType::AEDITOR)
				{
					current_type = Scene::SceneType::AEDITOR;
					return;
				}

				if (menu_scene->get_current() == tanks::MenuType::QUIT) // quit
				{
					throw ExitException();
				}
			}
		}
		
		current_scene->keyboard(button);
	};

};

#endif /* SCENEMANAGER_H_ */