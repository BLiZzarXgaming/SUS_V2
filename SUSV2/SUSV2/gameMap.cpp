#include "gameMap.h"

gameMap::gameMap(gameDataRef data) : _data(data)
{
	matrice<int> mapLue;

	ifstream fichierMap(MAP_MAIN_FILEPATH); //ouverture du ficher
	int nbLine, nbCol;
	if (fichierMap.is_open())
	{
		mapLue.setName("glurp");
		fichierMap >> nbLine >> nbCol;
		mapLue.resize(nbLine, nbCol);
		fichierMap >> mapLue; //lecture de la matrice
		fichierMap.close();
	}

	cout << mapLue;

	int tile;

	Sprite sprite1(_data->assets.getTexture("mapTileSet"));
	IntRect rect(0, 0, MAP_TILESET_SIZE, MAP_TILESET_SIZE);

	for (int i = 0; i < mapLue.nbLine(); i++)
	{
		for (int j = 0; j < mapLue.nbCol(); j++)
		{
			tile = mapLue[i][j] - 1;
			rect.left = tile * MAP_TILESET_SIZE;
			sprite1.setTextureRect(rect);
			sprite1.setPosition(j * MAP_TILESET_SIZE, i * MAP_TILESET_SIZE);
			if (tile <= 4 || tile >= 21)
				_mapSpritesSol.push_back(sprite1);
			else
				_mapSpritesMur.push_back(sprite1);
		}
	}
}

void gameMap::draw()const
{
	for (int i = 0; i < _mapSpritesMur.size(); i++)
		_data->window.draw(_mapSpritesMur.at(i));

	for (int i = 0; i < _mapSpritesSol.size(); i++)
		_data->window.draw(_mapSpritesSol.at(i));
}