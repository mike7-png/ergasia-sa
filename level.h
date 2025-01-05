#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include <string>
#include <vector>
#include "players.h"
#include <list>

class Level : public GameObject {
private:
    graphics::Brush m_brush_background;
    const float m_block_size = 0.5f;
    float m_center_x = 5.0f;
    float m_center_y = 5.0f;

    //-------------------------------------------------------------
    graphics::Brush m_block_brush;
    graphics::Brush m_block_brush_debug;
                                                        //kanonika blocks
    std::vector<Box> m_blocks;
    std::vector<std::string> m_block_names;

    //-----------------------------------------------------------

    graphics::Brush m_block_brush_invisible;            //aorata
    graphics::Brush m_block_brush_invisible_debug;

    std::vector<Box> m_blocks_invisible;
    std::vector<std::string> m_block_names_invisible;

    //--------------------------------------------------------

    graphics::Brush m_block_brush_money;
    graphics::Brush m_block_brush_money_debug;
                                                        //lefta
    std::vector<Box> m_blocks_money;
    std::vector<string> m_blocks_names_money;


    //--------------------------------------------------------

    std::vector<std::string> m_background_images;  // Λίστα εικόνων background
    std::vector<float> m_background_positions; // Θέσεις για κάθε background

    //----------------------------------------------------------------------------------


    // Γενικές στατικές και δυναμικές οντότητες
    std::vector<GameObject*> m_static_objects;
    std::list<GameObject*> m_dynamic_objects;

    void drawBlock(int i);
    void drawBlockinvisible(int i);
    void drawBlockMoney(int i);
    void checkCollisions();

    typedef enum { STATUS_START, STATUS_PLAYING, STATUS_HELP } status_t;

    status_t status = STATUS_START;

public:
    void updateStartScreen();
    //void updateLevelScreen(float dt);
    void updateHelpScreen();

    void drawStartScreen();
   // void drawLevelScreen();
    void drawHelpScreen();

    void update(float dt) override;
    void init() override;
    void draw() override;
    Level(const std::string& name = "Level0");
    ~Level();

    // Μέθοδοι για την κίνηση των backgrounds
    void updateBackgrounds(float deltaTime);
};


