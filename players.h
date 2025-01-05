#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>
#include <vector>

class Player : public GameObject, public Box {

    graphics::Brush m_brush_player;
    std::vector<std::string> m_sprites;

    const float m_gravity = 10.0f;
    const float m_accel_vertical = 6.0f;
    const float m_accel_horizontal = 40.0f;
    const float m_max_velocity = 10.0f;

    void movePlayer(float dt);

public:
    float m_vx = 0.0f;
    float m_vy = 0.0f;
    int m_money = 0;

    Player(string name) : GameObject(name) {}

    void update(float dt) override;
    void init() override;
    void draw() override;

    
    void addMoney(int amount);
    int getMoney() const;

    void addMoneyForBlock(const std::string& blockName);  

    float getPosX() const;

    float getPosY() const;

    //void displayMoney(float m_pos_x, float m_pos_);


protected:
    void debugDraw();
};
