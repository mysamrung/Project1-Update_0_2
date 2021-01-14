#pragma once
#include "Map.h"
#include "Object.h"
extern Map test;

class Player : public Object
{
public:
    VECTOR2 speed;
    int state;
    int anime;
    int animeTimer;
    bool onGround;
    bool hitWind;
    void Initialize(GameLib::Sprite* sp, VECTOR2 p, VECTOR2 s, VECTOR2 tp, VECTOR2 ts) override;
    void Update() override;
};

void player_init();
void player_render();
void player_update();


