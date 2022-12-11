#pragma once
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024
#define LOGO_STATE_SHOW_TIME 3.0

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
#define MAP_TILESET_COUNT 20	//nombre de tiles utilisable, 
								//j'utilise ca pour la génération
								//du vertex
#define MAP_TILESET_SIZE 32		//grandeur carrée des textures
#define MAP_MAIN_FILEPATH "Ressources/maps/map_2.txt"
