#include "level.h"
#include <sgg/graphics.h>
#include "players.h"
//#include "GroundEnemies.h"
#include "util.h"
#include "gamestate.h"
#include <iostream>

void Level::drawBlock(int i) {
    Box& box = m_blocks[i];
    float x = box.m_pos_x + m_state->m_global_offset_x;
    float y = box.m_pos_y + m_state->m_global_offset_y;
    m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);

    graphics::drawRect(x, y, 1.8f * m_block_size, 1.8f * m_block_size, m_block_brush);

    // Αν το debugging είναι ενεργό, θα τα σχεδιάσουμε με περιγράμματα
    if (m_state->m_debugging) {
        graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
    }
}

void Level::drawBlockinvisible(int i) {
    Box& box = m_blocks_invisible[i];
    float x = box.m_pos_x + m_state->m_global_offset_x;
    float y = box.m_pos_y + m_state->m_global_offset_y;
    m_block_brush_invisible.texture = m_state->getFullAssetPath(m_block_names_invisible[i]);


    // Αν το debugging είναι ενεργό, θα τα σχεδιάσουμε με περιγράμματα
    if (m_state->m_debugging) {
        graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_invisible_debug);
    }
}

void Level::drawBlockMoney(int i) {
    Box& box = m_blocks_money[i];
    float x = box.m_pos_x + m_state->m_global_offset_x;
    float y = box.m_pos_y + m_state->m_global_offset_y;
    m_block_brush_money.texture = m_state->getFullAssetPath(m_blocks_names_money[i]);
    graphics::drawRect(x, y, 1.8f * m_block_size, 1.8f * m_block_size, m_block_brush_money);

    if (m_state->m_debugging) {
        graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_money_debug);
    }

}




void Level::checkCollisions()
{
    for (auto& box : m_blocks) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(box)) {
            m_state->getPlayer()->m_pos_y += offset;

            if (m_state->getPlayer()->m_vy > 1.0f)            // Να ακούγεται ήχος μετά από κάποια ταχύτητα
                graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);

            m_state->getPlayer()->m_vy = 0.0f;
            break;
        }
    }

    for (auto& box : m_blocks) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(box)) {
            m_state->getPlayer()->m_pos_x += offset;

            if (m_state->getPlayer()->m_vx > 1.0f)            // Να ακούγεται ήχος μετά από κάποια ταχύτητα
                graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);

            m_state->getPlayer()->m_vx = 0.0f;
            break;
        }
    }
    //----------------------------------------------INVISIBLE---------------------------------------------


    for (auto& box : m_blocks_invisible) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(box)) {
            m_state->getPlayer()->m_pos_y += offset;

            if (m_state->getPlayer()->m_vy > 1.0f)            // Να ακούγεται ήχος μετά από κάποια ταχύτητα
                graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);

            m_state->getPlayer()->m_vy = 0.0f;
            break;
        }
    }

    for (auto& box : m_blocks_invisible) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(box)) {
            m_state->getPlayer()->m_pos_x += offset;

            if (m_state->getPlayer()->m_vx > 1.0f)            // Να ακούγεται ήχος μετά από κάποια ταχύτητα
                graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);

            m_state->getPlayer()->m_vx = 0.0f;
            break;
        }
    }

    //-----------------money-------------------------------------------------------------------------

    for (size_t i = 0; i < m_blocks_money.size(); i++) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(m_blocks_money[i])) {
            m_state->getPlayer()->m_pos_y += offset;

            
            graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);
            m_state->getPlayer()->m_vy = 0.0f;

    
            m_state->getPlayer()->addMoneyForBlock(m_blocks_names_money[i]);

            std::cout << "Player received money from block: " << m_blocks_names_money[i] << std::endl;

      
            m_blocks_money.erase(m_blocks_money.begin() + i);
            m_blocks_names_money.erase(m_blocks_names_money.begin() + i);
            break;
        }
    }
    for (size_t i = 0; i < m_blocks_money.size(); i++) {
        float offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectDown(m_blocks_money[i])) {
            m_state->getPlayer()->m_pos_x += offset;


            graphics::playSound(m_state->getFullAssetPath("metal2.wav"), 0.5f);
            m_state->getPlayer()->m_vx = 0.0f;

          
            m_state->getPlayer()->addMoneyForBlock(m_blocks_names_money[i]);

            std::cout << "Player received money from block: " << m_blocks_names_money[i] << std::endl;

        
            m_blocks_money.erase(m_blocks_money.begin() + i);
            m_blocks_names_money.erase(m_blocks_names_money.begin() + i);
            break;
        }
    }
}

void Level::updateBackgrounds(float dt) {
   
    float playerPosX = m_state->getPlayer()->m_pos_x;
    float canvasWidth = m_state->getCanvasWidth();
    float moveThreshold = canvasWidth * 0.8f;  // Όταν ο παίκτης φτάσει στο 80% της οθόνης
    if (playerPosX > moveThreshold) {
        m_background_positions[0] = -canvasWidth;  // Κρύβουμε το τρέχον background
        m_background_positions[1] = m_background_positions[0] + canvasWidth;  // Προχωράμε στην επόμενη εικόνα
    }
}

void Level::init() {
    m_brush_background.outline_opacity = 0.0f;

   
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");
    m_background_images.push_back("background.png");


    float offset = 0.0f;
    for (size_t i = 0; i < m_background_images.size(); ++i) {
        m_background_positions.push_back(offset);
        offset += m_state->getCanvasWidth();
    }

    // Αρχικοποίηση static και dynamic antikeimenwn
    for (auto p_gob : m_static_objects)
        if (p_gob) p_gob->init();

    for (auto p_gob : m_dynamic_objects)
        if (p_gob) p_gob->init();

   
    m_blocks.push_back(Box(39 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(4 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(3 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(2 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(6 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(7 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(7 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(15 * m_block_size, 8 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(5 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks.push_back(Box(4 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));

    m_block_names.push_back("block2.png");
    m_block_names.push_back("block2.png");
    m_block_names.push_back("block2.png");
    m_block_names.push_back("block2.png");
    m_block_names.push_back("block2.png");
    m_block_names.push_back("block2.png");
    m_block_names.push_back("block2.png");
    m_block_names.push_back("block5.png");
    m_block_names.push_back("block3.png");

    m_block_brush.outline_opacity = 0.0f;
    m_block_brush_debug.fill_opacity = 0.1f;
    m_block_brush.fill_opacity = 1.0f;
    SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
    SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

    //------------------------------INVISIBLE---------------------------------------------------------

    m_blocks_invisible.push_back(Box(1 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(2 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(9 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(2 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(49 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(0 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(1 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
    m_blocks_invisible.push_back(Box(32 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));


    m_block_names_invisible.push_back("");
    m_block_names_invisible.push_back("");
    m_block_names_invisible.push_back("");
    m_block_names_invisible.push_back("");
    m_block_names_invisible.push_back("");
    m_block_names_invisible.push_back("");
    m_block_names_invisible.push_back("");

    m_block_brush_invisible.outline_opacity = 0.0f;
    m_block_brush_invisible_debug.fill_opacity = 1.0f;
    m_block_brush_invisible.fill_opacity = 0.0f;
    SETCOLOR(m_block_brush_invisible_debug.fill_color, 1.0f, 0.0f, 0.0f);  // Κόκκινο χρώμα για το fill
    SETCOLOR(m_block_brush_invisible_debug.outline_color, 1.0f, 0.2f, 0.2f);  // Κόκκινο outline με λίγο πιο ανοιχτό χρώμα

    //--------------------------------money----------------------------------------------

    m_blocks_money.push_back(Box(1 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
    m_blocks_money.push_back(Box(2 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
    m_blocks_money.push_back(Box(35 * m_block_size, 7 * m_block_size, m_block_size, m_block_size));


    m_blocks_names_money.push_back("money.png");
    m_blocks_names_money.push_back("money.png");
    m_blocks_names_money.push_back("20-euroes.png");

    m_block_brush_money.outline_opacity = 0.0f;  
    m_block_brush_money_debug.fill_opacity = 0.1f;  
    m_block_brush_money.fill_opacity = 1.0f;  

    
    SETCOLOR(m_block_brush_money_debug.fill_color, 0.0f, 0.0f, 1.0f);  
    SETCOLOR(m_block_brush_money_debug.outline_color, 0.2f, 0.2f, 1.0f);  



}

void Level::draw() {
    float w = m_state->getCanvasWidth();
    float h = m_state->getCanvasHeight();

    for (size_t i = 0; i < m_background_images.size(); ++i) {
        float offset_x = m_background_positions[i] + m_state->m_global_offset_x / 2.0f + w / 2.0f;
        float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

        m_brush_background.texture = m_state->getFullAssetPath(m_background_images[i]);
        graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);
    }

    if (m_state->getPlayer()->isActive()) {
        m_state->getPlayer()->draw();
    }

    //if (m_state->getEnemy()->isActive()) {
      //  m_state->getEnemy()->draw();
    //}

    size_t limit = std::min(m_blocks.size(), m_block_names.size());
    for (size_t i = 0; i < limit; i++) {
        drawBlock(i);
    }
    //----------------------invisible-------------------------------------------------

    size_t limit_inv = std::min(m_blocks_invisible.size(), m_block_names_invisible.size());
    for (size_t i = 0;  i < limit_inv; i++) {
        drawBlockinvisible(i);
    }

    //-------------------money-------------------------------------------

    size_t limit_money = std::min(m_blocks_money.size(), m_blocks_names_money.size());
    for (size_t i = 0; i < limit_money; i++) {
        drawBlockMoney(i);
    }
}

Level::Level(const std::string& name) {

}

Level::~Level() {
    for (auto p_gob : m_static_objects)
        if (p_gob) delete p_gob;

    for (auto p_gob : m_dynamic_objects)
        if (p_gob) delete p_gob;
}

void Level::drawStartScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasWidth();
    float h = m_state->getCanvasHeight();

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("intro_background.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);

}

void Level::drawHelpScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasWidth();
    float h = m_state->getCanvasHeight();

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("intro_background.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);
}

void Level::update(float dt) {

    if (status == STATUS_START) {
        updateStartScreen();
    }
    else if (status == STATUS_HELP) {
        updateHelpScreen();
    }
}

void Level::updateStartScreen() {

    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_SPACE)  || mouse.button_left_pressed) {

        status = STATUS_PLAYING;
    }
    else if (graphics::getKeyState(graphics::SCANCODE_H)) {

        status = STATUS_HELP;
    }
}

void Level::updateHelpScreen() {
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_T)  || mouse.button_left_pressed) {

        status = STATUS_START;
    }
    else {
        status = STATUS_HELP;
    }
}




