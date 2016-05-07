#ifndef IDENTIFIERS_H_
#define IDENTIFIERS_H_

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

namespace tanks {

	enum ModelType
	{
		CAMERA,
		PIC_MENU,
		TEXT_MENU,
		BULLET,
		PLAYER,
		PLAYER_TOWER,
		ENEMY,
		ENEMY_TOWER,
		OBSTACLE1,
		OBSTACLE2,
		OBSTACLE3,
		OBSTACLE4,
		TERRAIN,
		PATH_NODE,
		ANIMATION_BONE
	};

	enum BulletType
	{
		TYPE1 = 1,
		TYPE2 = 3,
		TYPE3 = 5,
	};

	enum MenuType
	{
		EMPTY,
		PLAY,
		HELP,
		SETTINGS,
		AEDITOR,
		QUIT,
	};

	enum AxisType
	{
		X, Y, Z
	};

	typedef struct GameSettings
	{
		sf::Music				* mMusic;
		sf::Sound				* sound1;
		sf::Sound				* sound2;

		tanks::BulletType		bullet;
	} GameSettings;


	/*enum GameControlls
	{
		NONE = 0, 
		MOVE_FORWARD = 1,
		MOVE_BACK = 2,
		MOVE_LEFT = 4,
		MOVE_RIGHT = 8,
		TURN_LEFT = 16,
		TURN_RIGHT = 32,
		FIRE = 64,
		SHOW_MAP = 128,
		SHOW_GAME = 256,
		ENTER = 512,
		ESCAPE = 1024
	};
	*/

	enum ButtonControlls
	{
		NONE,
		FIRE,
		SHOW_MAP,
		SHOW_GAME,
		ENTER,
		ESCAPE,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		TURN_LEFT,
		TURN_RIGHT,
		X_AXIS,
		Y_AXIS,
		Z_AXIS,
		CAMERA_CTRL
	};

	typedef struct MoveControlls
	{
		bool move_forvard;
		bool move_back;
		bool move_left;
		bool move_right;
		bool turn_left;
		bool turn_right;

		MoveControlls() :
			move_forvard(false),
			move_back(false),
			move_left(false),
			move_right(false),
			turn_left(false),
			turn_right(false) {}
	} MoveControlls;



};

#endif /* IDENTIFIERS_H_ */