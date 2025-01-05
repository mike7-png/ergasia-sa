/* GroundEnemies.cpp
#include "GroundEnemies.h"
#include <algorithm>

void GroundEnemies::init() {
    m_width /= 2.0f;

    m_brush_enemy.fill_opacity = 1.0f;
    m_brush_enemy.outline_opacity = 0.0f;

    m_sprites_enemy.push_back(m_state->getFullAssetPath("ninja_walking1.png"));
    m_sprites_enemy.push_back(m_state->getFullAssetPath("ninja_walking2.png"));
    m_sprites_enemy.push_back(m_state->getFullAssetPath("ninja_walking3.png"));
    m_sprites_enemy.push_back(m_state->getFullAssetPath("ninja_walking4.png"));
    m_sprites_enemy.push_back(m_state->getFullAssetPath("ninja_walking5.png"));
}

void GroundEnemies::update(float dt) {
    moveEnemy(dt);
    GameObject::update(dt);
}

void GroundEnemies::moveEnemy(float dt) {
    float delta_time = dt / 1000.0f;
    e_vx = e_max_velocity; 
    e_pos_x += delta_time * e_vx;

    
    if (e_pos_x <= 0.0f || e_pos_x >= m_state->getCanvasWidth()) {
        e_vx = -e_vx;  
    }
    e_vy += delta_time * e_gravity; 
    e_vy = std::min(e_vy, e_max_velocity); 
    e_pos_y += e_vy * delta_time;
    if (e_pos_y >= 5.0f) {
        e_pos_y = 5.0f;  
        e_vy = 0.0f;     
    }
}


void GroundEnemies::draw() {
    int sprite_index = static_cast<int>(fmod(e_pos_x * 0.1f, m_sprites_enemy.size()));
    m_brush_enemy.texture = m_sprites_enemy[sprite_index];

    graphics::drawRect(
        e_pos_x - m_state->e_global_offset_x,
        e_pos_y - m_state->e_global_offset_y,
        1.0f, 1.0f,
        m_brush_enemy
    );

    if (m_state->m_debugging) {
        debugDraw();
    }
}

void GroundEnemies::debugDraw() {
    graphics::Brush brush;
    brush.outline_opacity = 1.0f;
    graphics::drawRect(m_pos_x, m_pos_y, 1.0f, 1.0f, brush);
}

/*void GroundEnemies::spawnEnemies(std::vector<GroundEnemies>& enemies) {
    std::vector<std::pair<float, float>> spawnPoints = {
        {40.0f, 2.0f},
        {10.0f, 2.0f},
        {30.0f, 3.0f},
        {45.0f, 5.0f},
        {13.0f, 3.0f}
    };

    for (const auto& point : spawnPoints) {
        GroundEnemies enemy("Enemy");
        enemy.e_pos_x = point.first;
        enemy.e_pos_y = point.second;
        enemy.init();
    }
}*/