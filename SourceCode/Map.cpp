#include "Map.h"
#include <sstream>
#define CHIP_S 54
Map test;
WindMap WindM;
GameLib::Sprite* sprTest;
GameLib::Sprite* sprWind;
std::vector<Fan>fans;
std::vector<Fan>wind;
std::vector<Fan>dist;
void wind_init(WindMap *wM);
void wind_update();
void LoadCSV(std::string file_path, int arr[MAP_Y][MAP_X]) 
{
    std::ifstream data(file_path);
    if (!data)
        assert(!"File Doesn't exist");
    std::string str{};
    int col = 0, row = 0;
    while (std::getline(data, str)) 
    {
        std::stringstream ss(str);
        std::string cell;
        col = 0;
        while (std::getline(ss, cell, ',')) 
        {
            arr[row][col] = atoi(cell.c_str());
            col++;
        }
        row++;
    }
}
void Map::Draw()
{
    for (int y = 0; y < MAP_Y; ++y)
    {
        for (int x = 0; x < MAP_X; ++x)
        {
            if (chip[y][x] == 0)
                continue;
            DrawChip({ x * size.x, y * size.y },  (chip[y][x] - 1)% 8 * size.x, chip[y][x] / 8 * size.y );
        }
    }
}
int Map::getChip(VECTOR2 pos)
{
    int a = (int)pos.x / 54;
    int b = (int)pos.y / 54;
    return chip[b][a];
}
bool HoriChipCheck(Object* obj, Map *map)
{
    if (map->getChip({ obj->pos.x + 1 + obj->pivot.x + 27, obj->pos.y }) != 0 || map->getChip({ obj->pos.x - 1 - obj->pivot.x + 27, obj->pos.y }) != 0)
        return true;
    return false;
}
bool VertiChipCheck(Object* obj, Map *map)
{
    if (map->getChip({ obj->pos.x - obj->pivot.x - 1, obj->pos.y + 1 + 54 / 2 }) != 0 || map->getChip({ obj->pos.x + obj->pivot.x + 1, obj->pos.y + 1 + 54 / 2 }) != 0)
    {
        return true;
    }
    return false;
}
bool TopChipCheck(Object* obj, Map* map)
{
    if (map->getChip({ obj->pos.x, obj->pos.y - 1 - obj->pivot.y }))
        return true;
    return false;
}

void map_init()
{
    sprTest = GameLib::sprite_load(L"./Data/Map/back_chip.png");
    sprWind = GameLib::sprite_load(L"./Data/Map/terrain_chip.png");
    WindM.mapSpr.reset(sprWind);
    WindM.fileN = "./Data/Map/test2.txt";
    WindM.Set();
    WindM.size = { 54, 54 };
    test.mapSpr.reset(sprTest);
    test.fileN = "./Data/Map/Map1.txt";
    test.Set();
    test.size.x = 54;
    test.size.y = 54;
    wind_init(&WindM);
}

void WindMap::Update()
{
    //for (int y = 0; y < MAP_Y; ++y)
    //{
    //    for (int x = 0; x < MAP_X; ++x)
    //    {
    //        if (!chip[y][x])
    //            continue;
    //        //if (chip[y][x])
    //        setWind(chip, x, y);
    //    }
    //}
}

void WindMap::setWind(int chip[MAP_Y][MAP_X], int x, int y)
{
    if (chip[y][x] == 4)
    {
        for (int alpha = 0; alpha < 5; ++alpha)
        {
            if (!chip[y][x + alpha])
                chip[y][x + alpha] = 1;
        }
    }
    if (chip[y][x] == 3)
    {
        for (int alpha = 0; alpha < 5; ++alpha)
        {
            if (!chip[y][x - alpha])
                chip[y][x - alpha] = 2;
            if (chip[y][x - alpha] == 1)
            {
                
            }
        }
    }
}

void map_update()
{
    WindM.Update();
    wind_update();
}
using namespace GameLib::primitive;
void map_render()
{
    test.Draw();
    WindM.Draw();
    for (int alpha = 0; alpha < wind.size(); ++alpha)
        circle(
            VECTOR2((wind[alpha].x) * 54, (wind[alpha].y) * 54),
            5.0f,
            {1.0f, 1.0f},
            0.0f,
            { 1, 0, 0, 1 }
    );
        
}
void wind_init(WindMap *wM)
{
    for (int alpha = 0; alpha < MAP_Y; ++alpha)
    {
        for (int beta = 0; beta < MAP_X; ++beta)
        {
            if (wM->chip[alpha][beta] == 4)
                fans.push_back({ beta, alpha, Fan::Direction::RIGHT });
            if (wM->chip[alpha][beta] == 3)
                fans.push_back({ beta, alpha, Fan::Direction::LEFT });
        }
    }
}

void wind_update()
{
    VECTOR2 temp{0, 0};
    VECTOR2 pos;
    wind.clear();
    dist.clear();
    for (int alpha = 0; alpha < fans.size(); ++alpha)
    {
        int distance{};
        for (int beta = 0; beta < fans.size(); ++beta)
        {
            if (fans[alpha].y == fans[beta].y)
            {
                distance = abs(fans[alpha].x - fans[beta].x);
                int center = fans[alpha].x + distance / 2;
                if (center && center < 10)
                    dist.push_back({ center, fans[alpha].y, Fan::Direction::UP });
            }
        }
    }
    for (int alpha = 0; alpha < fans.size(); ++alpha)
    {
        pos = VECTOR2((float)fans[alpha].x, (float)fans[alpha].y);
        
        if (fans[alpha].dir == Fan::Direction::LEFT)
            temp = { -1, 0 };
        if (fans[alpha].dir == Fan::Direction::RIGHT)
            temp = { 1, 0 };
        for (int beta = 0; beta < 5; ++beta)
        {
            pos += temp;
            for (int gamma = 0; gamma < dist.size(); ++gamma)
            {
                if (pos == VECTOR2{ (float)dist[gamma].x, (float)dist[gamma].y })
                {
                    if (dist[gamma].dir == Fan::Direction::UP)
                        temp = { 0, -1 };
                }
            }

            Fan::Direction dir = Fan::Direction::UP;
            if (temp == VECTOR2{ -1, 0 })
                dir = Fan::Direction::LEFT;
            else if (temp == VECTOR2{ 1, 0 })
                dir = Fan::Direction::RIGHT;
            else if (temp == VECTOR2{ 0, -1 })
                dir == Fan::Direction::UP;
            wind.push_back({ (int)pos.x, (int)pos.y, dir });
        }
    }
}