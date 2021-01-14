#pragma once
#include "../GameLib/game_lib.h"
#include <iomanip>
#include <string>
#include <fstream>
#include "Object.h"
#define MAP_X 38
#define MAP_Y 18
//extern Map test;
void LoadCSV(std::string file_path, int arr[MAP_Y][MAP_X]);
class Map
{
public:
    Map() {}
    std::unique_ptr<GameLib::Sprite>mapSpr;
    std::string fileN;
    int chip[MAP_Y][MAP_X];
    //char chip[MAP_Y][MAP_X];
    VECTOR2 size;
    void Draw();
    void Set()
    {
        LoadCSV(fileN, chip);
    }
    void DrawChip(VECTOR2 p, int tx, int ty)
    {
        GameLib::sprite_render(mapSpr.get(), p.x, p.y, 1, 1, tx, ty, 54, 54, 27, 27, 0, 1, 1, 1, 1);
    }
    int getChip(VECTOR2 pos);
};
bool HoriChipCheck(Object* obj, Map *map);
bool VertiChipCheck(Object* obj, Map *map);
bool TopChipCheck(Object* obj, Map* map);
//void test_init();
enum CHIP_TYPE
{
    // TODO : PLACE HOLDER FOR CHIP TYPES
};


class WindMap : public Map
{
public:

    
    void Update();
    void windRender();
    void setWind(int chip[MAP_Y][MAP_X], int x, int y);
    void WindDist();
};

class Fan
{
public:
    int x;
    int y;
    enum Direction
    {
        UP, DOWN, LEFT, RIGHT
    }dir;
};
void map_init();
void map_update();
void map_render();