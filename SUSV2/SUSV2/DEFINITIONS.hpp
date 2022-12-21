#pragma once
#define LOGO_STATE_SHOW_TIME 3.0

//#define SPLASH_STATE_BACKGROUND_FILEPATH "Ressources/res/SplashBackground.png"

#define PLAYER_SPRITESHEET_FILEPATH "Ressources/res/SUS_Player_Sheet.png"

#define PLAYER_HEALTH_FILEPATH "Ressources/res/SUS_Player_healthbar.png"

#define BOSS_SPRITESHEET_FILEPATH "Ressources/res/SUS_Boss_Spritesheet.png"
#define TRIGGER_FILEPATH "Ressources/res/SUS_Trigger.png"
enum gameStates {
	ready,
	playing,
	gameOver
};

enum tileType {
	sgp1,
	sgf1,
	sgp2,
	sgf2,
	mbh_,
	mbd_,
	mbg_,
	mbb_,
	mchg,
	mchd,
	mcbg,
	mcbd,
	mihd,
	mihg,
	mibd,
	mibg,
	mmh_,
	mmb_,
	fh__,
	fb__
};

#define MAP_TILESET_FILEPATH "Ressources/tileset/Sus_Tileset_Flooring.png"
#define MAP_TILESET_SIZE 32		//grandeur carrée des textures
#define MAP_MAIN_FILEPATH "Ressources/maps/map_2.txt"
#define MAIN_BACKGROUND_FILEPATH "Ressources/SUS_Background.png"
