#pragma once
#define LOGO_STATE_SHOW_TIME 3.0

//#define SPLASH_STATE_BACKGROUND_FILEPATH "Ressources/res/SplashBackground.png"

#define PLAYER_SPRITESHEET_FILEPATH "Ressources/res/SUS_Player_Sheet.png"

#define PLAYER_HEALTH_FILEPATH "Ressources/res/SUS_Player_healthbar.png"

enum gameStates {
	ready,
	playing,
	gameOver
};

enum directionEnumHB {
	nohb,
	haut,
	bas
};

enum directionEnumGD {
	nogd,
	gauche,
	droite
};

#define MAP_TILESET_FILEPATH "Ressources/tileset/Sus_Tileset_Flooring.png"
#define MAP_TILESET_SIZE 32		//grandeur carrée des textures
#define MAP_MAIN_FILEPATH "Ressources/maps/map_2.txt"
#define MAIN_BACKGROUND_FILEPATH "Ressources/SUS_Background.png"
