#ifndef _BOMBERMAN_SCENES_GAME_OVER_SCENE_H_
#define _BOMBERMAN_SCENES_GAME_OVER_SCENE_H_

#include <SDL.h>
#include <memory>
#include "../Entities/Music.h"
#include "../Entities/Text.h"
#include "../Scenes/Scene.h"

/**
    * @brief GameManager Over Scene
    *
    */

 enum class MenuItemCO
{
    None,
    ConfigurationWASD_space,
    ConfigurationTFGH_b,
    ConfigurationIJKL_m,
    Exit,
    Last
};
class GameOverScene : public Scene
{

    

    public:
    /**
        * @brief Construct a new GameManager Over Scene
        *
        * @param game
        */
    GameOverScene(GameManager* _gameManager);

    virtual void onEvent(const SDL_Event& event) override;
   
    /**
        * @brief Trigger on update if scene is active
        *
        * @param delta - time in milliseconds
        */
    virtual void update(const unsigned int delta) override;

    private:

        void onMenuItemSelect();

        void onMenuItemPress();

    // timer until switch to next menu
    int untilNextSceneTimer = 0;
    // const
    const int sceneTimer = 90000000;

    std::shared_ptr<Text> starConfiAWSDtText = nullptr;
    std::shared_ptr<Text> starConfiTFGHText = nullptr;
    std::shared_ptr<Text> starConfiIJKLText = nullptr;
    std::shared_ptr<Text> starExitText = nullptr;
    std::shared_ptr<Music> menuMusic = nullptr;
    MenuItemCO currentSelectedMenu = MenuItemCO::ConfigurationWASD_space;
    // const colors for menu selection
    const SDL_Color colorStandard = { 255, 255, 255, 255 };
    const SDL_Color colorPressed = { 224, 30, 55, 255 };
    
};

#endif // _BOMBERMAN_SCENES_GAME_OVER_SCENE_H_
