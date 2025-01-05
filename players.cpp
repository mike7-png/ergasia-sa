#include "players.h"
#include "gamestate.h"
#include <sgg/graphics.h>
#include <iostream>


void Player::init() {
    m_pos_x = 0.0f;
    m_pos_y = 5.0f;
    m_width /= 2.0f;

    m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
    m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

    m_brush_player.fill_opacity = 1.0f;
    m_brush_player.outline_opacity = 0.0f;
    m_brush_player.texture = m_state->getFullAssetPath("Boing-back.png");

    m_sprites.push_back(m_state->getFullAssetPath("Boing-left0.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left1.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left2.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left3.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left4.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left5.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left6.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left7.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left8.png"));
    m_sprites.push_back(m_state->getFullAssetPath("Boing-left9.png"));

    m_money = 0;
}

void Player::update(float dt) {
    movePlayer(dt);
    m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
    m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

    GameObject::update(dt);
}

void Player::movePlayer(float dt) {
    float delta_time = dt / 1000.0f;
    float move = 0.0f;

    if (graphics::getKeyState(graphics::SCANCODE_A)) move -= 1.0f;
    if (graphics::getKeyState(graphics::SCANCODE_D)) move += 1.0f;

    m_vx = std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
    m_vx = std::max(-m_max_velocity, m_vx);
    m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));
    if (fabs(m_vx) < 0.01f) m_vx = 0.0f;
    m_pos_x += delta_time * m_vx;

    if (graphics::getKeyState(graphics::SCANCODE_W) && m_vy == 0.0f) {
        m_vy = -m_accel_vertical;
    }

    m_vy += delta_time * m_gravity;
    m_vy = std::min(m_vy, m_max_velocity);
    m_pos_y += m_vy * delta_time;

    if (m_pos_y >= 5.0f) {
        m_pos_y = 5.0f;
        m_vy = 0.0f;
    }
}

void Player::draw() {
    int s = (int)fmodf(1000.0f - m_pos_x * 8.0f, m_sprites.size());
    m_brush_player.texture = m_sprites[s];

    graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);

    //displayMoney(m_pos_x, m_pos_y);

    if (m_state->m_debugging)
        debugDraw();
}

void Player::debugDraw() {
    
}

void Player::addMoney(int amount) {
    m_money += amount;  
}

int Player::getMoney() const {
    return m_money; 
}

void Player::addMoneyForBlock(const std::string& blockName) {
    if (blockName == "20-euroes.png") {
        addMoney(20);  
    }
    else if (blockName == "50-euroes.png") {
        addMoney(50);  
    }
    else if (blockName == "100-euroes.png") {
        addMoney(100); 
    }
    else if (blockName == "10-euroes.png") {
        addMoney(10);  
    }
}

float Player::getPosX() const {
    return m_pos_x;  
}

float Player::getPosY() const {
    return m_pos_y;  
}

/*
void Player::displayMoney(float m_pos_x, float m_pos_y) {
    std::string moneyText = "Money: " + std::to_string(m_money);
    float x_pos = m_pos_x;
    float y_pos = m_pos_y + 0.5f;

    graphics::Brush brush_money;
    brush_money.fill_color[0] = 1.0f;

    graphics::drawText(x_pos, y_pos, 30.0f, moneyText, brush_money);
}*/




