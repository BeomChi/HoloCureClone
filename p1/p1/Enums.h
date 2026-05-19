#pragma once

enum class SceneType
{
	None,
	DevScene,
	GameScene,
	StartScene,
	EditScene,

	MenuScene,
	SceneEnd
};


enum class EntityType
{
	Player,
	Monster,
	Mineral,

	EntityTypeEnd
};

enum class ColliderType
{
	Box,
	Sphere,
};

enum Equip
{
	Weapon,
	Armor,
	None
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_AREAATTACK,
	LAYER_OBJECT,
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
};

enum enumAttack
{
	START,
	ATTACK,
	END
};

enum class DirState
{
	Left,
	Right,

	LaserStatEnd
};

enum class WeaponType
{
	Melee,
	Ranged,
	Multishot,
	None
};

enum class GameState
{
	None,
	Title,
	Playing,
	Paused,
	GameOver,
};