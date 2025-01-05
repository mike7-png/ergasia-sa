#include "gamestate.h"
#include <thread>
#include <chrono>
#include <iostream>

GameState* GameState::m_unique_instance = nullptr;

GameState::GameState()
    : m_intro_active(true), m_intro(nullptr), m_current_level(nullptr), m_player(nullptr) {
}

void GameState::init() {

        m_current_level = new Level("1.lvl");
        m_current_level->init();

        m_player = new Player("Player");
        m_player->init();

        graphics::preloadBitmaps(getAssetDir());
        graphics::setFont(m_asset_path + "OpenSans_Regular.ttf");
}

void GameState::draw() {

    if (m_current_level) {
        m_current_level->draw();
    }
}

void GameState::update(float dt) {
    if (dt > 500)
        return;

    float sleep_time = std::max(0.0f, 17.0f - dt);
    std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

   
    if (m_current_level) {
        m_current_level->update(dt);
        m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
    }
}

GameState* GameState::getInstance() {
    if (m_unique_instance == nullptr) {
        m_unique_instance = new GameState();
    }
    return m_unique_instance;
}

GameState::~GameState() {

    if (m_current_level) {
        delete m_current_level;
        m_current_level = nullptr;
    }

    if (m_player) {
        delete m_player;
        m_player = nullptr;
    }
}

std::string GameState::getAssetDir() {
    return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset) {
    return m_asset_path + asset;
}













