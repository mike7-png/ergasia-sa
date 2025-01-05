
#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>
#include <vector>
#include "gamestate.h"

class GroundEnemies : public GameObject, public Box {
public:

    graphics::Brush m_brush_enemy;
    std::vector<std::string> m_sprites_enemy;
    std::vector<GroundEnemies> enemies;
    GroundEnemies(string name) : GameObject(name) {}


    const float m_gravity = 10.0f;
    float e_vx = 0.0f;
    float e_vy = 0.0f;
    const float e_accel_vertical = 6.0f;
    const float e_accel_horizontal = 40.0f;
    const float e_max_velocity = 10.0f;

    //void update(float dt) override;
    //void init() override;
    //void draw() override;
    //static void spawnEnemies(std::vector<GroundEnemies>& enemies);

protected:
    void debugDraw();
};
    //void moveEnemy(float dt);

    static void spawnEnemies(std::vector<GroundEnemies>& enemies);

