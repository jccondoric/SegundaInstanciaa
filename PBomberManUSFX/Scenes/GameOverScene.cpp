#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/MenuScene.h"

MenuItemCO& operator++(MenuItemCO& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItemCO>(static_cast<type>(c) + 1);
    if (c == MenuItemCO::Last)
        c = static_cast<MenuItemCO>(static_cast<type>(MenuItemCO::None) + 1);
    return c;
}

// --decrement for menu id
MenuItemCO& operator--(MenuItemCO& c)
{
    using type = typename std::underlying_type<MenuItemCO>::type;
    c = static_cast<MenuItemCO>(static_cast<type>(c) - 1);
    if (c == MenuItemCO::None)
        c = static_cast<MenuItemCO>(static_cast<type>(MenuItemCO::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItemCO operator++(MenuItemCO& c, int)
{
    MenuItemCO result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItemCO operator--(MenuItemCO& c, int)
{
    MenuItemCO result = c;
    --c;
    return result;
}
GameOverScene::GameOverScene(GameManager* _gameManager) : Scene(_gameManager)
{
    //// gameManager over text
    //auto gameOverText =
    //    std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CONFIGURACION");
    //gameOverText->setSize(static_cast<int>(gameManager->getWindowWidth() / 1.5f),
    //                        static_cast<int>(gameManager->getWindowHeight() / 12.0f));
    //gameOverText->setPosition(
    //    static_cast<int>(gameManager->getWindowWidth() / 2.0f - gameOverText->getWidth() / 2.0f),
    //    static_cast<int>(gameManager->getWindowHeight() / 9.0f - gameOverText->getHeight() / 2.0f));
    //addObject(gameOverText);

    
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::MenuConfiguration), gameManager->getRenderer());

    background->setPosition(0, 0);

    background->setSize(gameManager->getWindowWidth() - 60, static_cast<int>(gameManager->getWindowHeight() / 1.5f) - 20);
    addObject(background);

    starConfiAWSDtText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CONFIGURACION_WASD_SPACE");
    starConfiAWSDtText->setColor(colorPressed);
    starConfiAWSDtText->setSize(static_cast<int>(gameManager->getWindowWidth() / 1.99f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    starConfiAWSDtText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - starConfiAWSDtText->getWidth() / 2.0f), background->getHeight() + 25);
    addObject(starConfiAWSDtText);

    starConfiTFGHText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CONFIGURATION_TFGH_B");
    starConfiTFGHText->setColor(colorStandard);
    starConfiTFGHText->setSize(static_cast<int>(gameManager->getWindowWidth() / 2.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    starConfiTFGHText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - starConfiTFGHText->getWidth() / 2.0f), background->getHeight() + 80);
    addObject(starConfiTFGHText);

    starConfiIJKLText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CONFIGURATION_IJKL_M");
    starConfiIJKLText->setColor(colorStandard);
    starConfiIJKLText->setSize(static_cast<int>(gameManager->getWindowWidth() / 2.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    starConfiIJKLText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - starConfiIJKLText->getWidth() / 2.0f), background->getHeight() + 130);
    addObject(starConfiIJKLText);

    starExitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "EXIT");
    starExitText->setColor(colorStandard);
    starExitText->setSize(102, 29);
    starExitText->setPosition(340, 565);
    addObject(starExitText);

    //
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::MenuConfiguration));

    // gameManager over text
    auto gameOverText =
        std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CONFIGURACION");
    gameOverText->setSize(static_cast<int>(gameManager->getWindowWidth() / 1.5f),
        static_cast<int>(gameManager->getWindowHeight() / 12.0f));
    gameOverText->setPosition(
        static_cast<int>(gameManager->getWindowWidth() / 2.0f - gameOverText->getWidth() / 2.0f),
        static_cast<int>(gameManager->getWindowHeight() / 9.0f - gameOverText->getHeight() / 2.0f));
    addObject(gameOverText);

}

void GameOverScene::update(const unsigned int delta)
{
    untilNextSceneTimer += delta;
    if(untilNextSceneTimer >= sceneTimer)
    {
        untilNextSceneTimer = 0;
        gameManager->getSceneManager()->activateScene("inicio");
    }
}

void GameOverScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.scancode)
        {
            // we should select next menu item
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            currentSelectedMenu++;
            onMenuItemSelect();
            break;
            // we should select prev menu item
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            currentSelectedMenu--;
            onMenuItemSelect();
            break;
            // enter in menu item
        case SDL_SCANCODE_SPACE:
        case SDL_SCANCODE_RETURN:
            onMenuItemPress();
            break;
        default:
            break;
        }
    }
}

void GameOverScene::onMenuItemSelect()
{
    // reset menu items color
    starConfiAWSDtText->setColor(colorStandard);
    starConfiTFGHText->setColor(colorStandard);
    starConfiIJKLText->setColor(colorStandard);
    starExitText->setColor(colorStandard);
    // change color of selected menu item
    switch (currentSelectedMenu)
    {
    case MenuItemCO::ConfigurationWASD_space:
        starConfiAWSDtText->setColor(colorPressed);
        break;
    case MenuItemCO::ConfigurationTFGH_b:
        starConfiTFGHText->setColor(colorPressed);
        break;
    case MenuItemCO::ConfigurationIJKL_m:
        starConfiIJKLText->setColor(colorPressed);
        break;
    case MenuItemCO::Exit:
        starExitText->setColor(colorPressed);
        break;
    default:
        break;
    }
    
}

void GameOverScene::onMenuItemPress() {

    switch (currentSelectedMenu)
    {
    case MenuItemCO::ConfigurationWASD_space:
        
        
        break;
    case MenuItemCO::Exit:
        // go to level scene

        gameManager->getSceneManager()->activateScene("inicio");
        break;

    default:
        break;
    }
}

