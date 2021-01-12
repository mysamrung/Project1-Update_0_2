#include "Player.h"
GameLib::Sprite* playerSpr;
extern Map test;
Player player;
using namespace GameLib::input;
void Player::Initialize(GameLib::Sprite* sp, VECTOR2 p, VECTOR2 s, VECTOR2 tp, VECTOR2 ts)
{
    playerSpr = GameLib::sprite_load(L"./Data/Images/Player.png");
    Object::Initialize(playerSpr, p, s, tp, ts);
}

void Player::Update()
{
    speed.x = {};
    const VECTOR2 tpos{ pos };
    if (STATE(0) & PAD_LEFT)
        speed.x = -6;
    if (STATE(0) & PAD_RIGHT)
        speed.x = 6;
    if (TRG(0) & PAD_L1 && onGround)
    {
        speed.y = -25.0f;
        onGround = false;
    }
   
    if (TopChipCheck(&player, &test))
        speed.y = {};
    if (!onGround)
        speed.y += 1;
    else
        speed.y = 0;
    pos += speed;
    if (HoriChipCheck(&player, &test))
    {
        //speed.x = {};
        pos.x = tpos.x;
    }
    
    if (VertiChipCheck(&player, &test)) {
        pos.y = std::ceil(pos.y / 54) * 54 - 28;
        onGround = true;
    }
    else if (!VertiChipCheck(&player, &test))
    {
        onGround = false;
    }
}

void player_init()
{
    player.Initialize(playerSpr, { 300, 200 }, { 1, 1 }, { 0, 0 }, { 54, 108 });
    player.pivot = { 27, 108 };
}

void player_render()
{
    player.Draw();
    GameLib::primitive::circle(player.pos, 10.0f, { 1, 1 }, 0.0f, { 1, 0, 0, 1 });
}

void player_update()
{
    player.Update();
}

