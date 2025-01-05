#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>
#include <sgg/graphics.h>
#include "level.h"
#include "players.h"


using namespace std;

class GameState {
private:
    string m_asset_path = "assets\\";

    float m_canvas_width = 6.0f;
    float m_canvas_height = 6.0f;

    static GameState* m_unique_instance;

    GameState();

    class Player* m_player = nullptr;
    class Level* m_current_level = nullptr;



public:
    float m_global_offset_x = 0.0f;
    float m_global_offset_y = 0.0f;
    bool m_debugging = false;

    void init();
    void draw();
    void update(float dt);

    static GameState* getInstance();
    ~GameState();

    float getCanvasWidth() const { return m_canvas_width; }
    float getCanvasHeight() const { return m_canvas_height; }

    string getAssetDir();
    string getFullAssetPath(const string& asset);

    Player* getPlayer() const { return m_player; }

protected:
    int visits = 0;
};

#endif // GAMESTATE_H
