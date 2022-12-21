#pragma once

#define SCREEN_WIDTH sf::VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT sf::VideoMode::getDesktopMode().height
#define LOGO_STATE_SHOW_TIME 3.0

#define SPLASH_STATE_BACKGROUND_FILEPATH "ressources/images/SUS_Background1.png"

#define BULLET_FILEPATH "ressources/images/balle.png"
#define MAIN_MENU_STATE_BACKGROUND_FILEPATH "ressources/images/menu_principale.png"
#define MAIN_FONT_FILEPATH "ressources/fonts/Robota-NonCommercial.otf"
#define RANGE_BULLET 1200
#define SPEED_BULLET 300

#define COLOR_TEXT sf::Color::Black
#define COLOR_BUTTON sf::Color::White
#define COLOR_ACTUAL_BUTTON sf::Color::Cyan
#define SIZE_CARACTER_MENU 80

#define CREDIT_BACKGROUND_FILEPATH "ressources/images/credit.png"
#define COMMENT_JOUER_BACKGROUND_FILEPATH "ressources/images/comment.png"

#define PLAYER_SPRITESHEET_FILEPATH "Ressources/res/SUS_Player_Sheet.png"

#define PLAYER_HEALTH_FILEPATH "Ressources/res/SUS_Player_healthbar.png"

#define BOSS_SPRITESHEET_FILEPATH "Ressources/res/SUS_Boss_Spritesheet.png"
#define TRIGGER_FILEPATH "Ressources/res/SUS_Trigger.png"
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

