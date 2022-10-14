/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#include "GameClient.hpp"

/**
 * It initializes the random number generator, creates a graphical interface, sets
 * the state to Menu, sets the isInGame variable to false, sets the SFML interface,
 * and loads the systems.
 */
GameClient::GameClient()
{
    srand(time(NULL));
    _graphical = std::make_shared<InitSfml>();
    _state = Menu;
    _isInGame = false;
    setSfml();
    loadSystems();
}

/**
 * It sets the textures and fonts for the game
 */
void GameClient::setSfml()
{
    _graphical->setTexture("bg-menu", "Assets/menu/bg-menu.jpeg");
    _graphical->setTexture("logo", "Assets/menu/logo.png");
    _graphical->setTexture("bg-game-2", "Assets/game/bg-game-2.jpeg");
    _graphical->setTexture("stars", "Assets/game/stars.png");
    _graphical->setTexture("heart", "Assets/game/heart.png");
    _graphical->setTexture("start", "Assets/menu/startButtons.png");
    _graphical->setFont("origintech", "Assets/font/origintech.ttf");
    // _graphical->setMusic("menu", "space_oddity-menu.ogg");
}

/**
 * It adds all the systems to the ECS manager
 */
void GameClient::loadSystems()
{
    _manager.addSystem<ECS::MoveSystem>();
    _manager.addSystem<ECS::CollisionSystem>();
    _manager.addSystem<ECS::TextSystem>();
    _manager.addSystem<ECS::GraphicSystem>();
}

/**
 * It's a loop that handles events and draws the game
 */
void GameClient::gameLoop()
{
    while (_graphical->getWindow()->isOpen()) {
        while (_graphical->getWindow()->pollEvent(_graphical->getEvent())) {
            const sf::Event &event = _graphical->getEvent();
            handleEvents(event);
        }
        _graphical->clear();
        selectMode();
        _graphical->display();
    }
}

/**
 * It handles the events
 * 
 * @param event The event to handle.
 */
void GameClient::handleEvents(const sf::Event &event)
{
    Button eventKey = _events.getEventType(event);

    if (event.type == sf::Event::Closed)
        _graphical->getWindow()->close();
    else if (event.type == sf::Event::MouseButtonReleased)
        handleEventsMouse(event);
    else if (event.type == sf::Event::KeyPressed && eventKey != Button::None)
        handleEventsKey(eventKey);
}

/**
 * It checks if the mouse is on a button, and if it is, it sets the _isInGame
 * variable to true
 * 
 * @param event The event that was triggered.
 */
void GameClient::mouseMenu(const sf::Event &event)
{
    const auto &entities = _manager.getEntities();
    Mouse eventMouse = _events.getEventTypeMouse(event);

    if (eventMouse == Mouse::Left) {
        sf::Vector2i position = sf::Mouse::getPosition(*_graphical->getWindow());
        for (const auto &entity : entities) {
            if (entity.getType() == ECS::EntityType::BUTTONS) {
                auto *positionEntity = dynamic_cast<ECS::Position*>(_manager.getComponent(entity, ECS::ComponentType::POSITION));
                auto *hitboxEntity = dynamic_cast<ECS::Hitbox*>(_manager.getComponent(entity, ECS::ComponentType::HITBOX));
                if (position.x > positionEntity->getPosition_x() && position.x < positionEntity->getPosition_x() + hitboxEntity->getWidth() &&
                    position.y > positionEntity->getPosition_y() && position.y < positionEntity->getPosition_y() + hitboxEntity->getHeight())
                    _isInGame = true;
            }
        }
    }
}

/**
 * It handles mouse events based on the current game state
 * 
 * @param event The event that was triggered.
 */
void GameClient::handleEventsMouse(const sf::Event &event)
{
    switch (_state) {
        case GameState::Menu:
            mouseMenu(event);
            break;
        case GameState::Game:
            //handle game
            break;
        default:
            break;
    }
}

/**
 * > This function handles the events that are triggered by the keyboard
 * 
 * @param eventKey The key that was pressed.
 */
void GameClient::handleEventsKey(Button eventKey)
{
    switch (_state) {
        case GameState::Game:
            //handle game
            break;
        default:
            break;
    }
}

/**
 * It calls the right function depending on the current state of the game
 */
void GameClient::selectMode()
{
    switch (_state) {
        case GameState::Menu:
            manageMenu();
            break;
        case GameState::Game:
            manageGame();
            break;
        default:
            break;
    }
}

void GameClient::loadMenu()
{
    ECS::Entity entityLogo = _manager.createEntity(ECS::EntityType::GRAPHICS);
    _manager.addComponent(entityLogo, ECS::ComponentType::SPRITE);
    ECS::IComp *compLogo = _manager.getComponent(entityLogo, ECS::ComponentType::SPRITE);
    ECS::Sprite *spriteLogo = dynamic_cast<ECS::Sprite*>(compLogo);
    sf::Sprite spriteLogoTmp;
    spriteLogoTmp.setTexture(*_graphical->getTexture("logo"));
    spriteLogo->setSprite(&spriteLogoTmp);
    spriteLogo->setPosition(sf::Vector2f(610, 310));

    ECS::Entity entityBg = _manager.createEntity(ECS::EntityType::GRAPHICS);
    _manager.addComponent(entityBg, ECS::ComponentType::SPRITE);
    ECS::Sprite *spriteBg = dynamic_cast<ECS::Sprite*>(_manager.getComponent(entityBg, ECS::ComponentType::SPRITE));
    sf::Sprite spriteBgTmp;
    spriteBgTmp.setTexture(*_graphical->getTexture("bg-menu"));
    spriteBg->setSprite(&spriteBgTmp);
    spriteBg->setScale(sf::Vector2f(1.9, 1.9));

    ECS::Entity entityStart = _manager.createEntity(ECS::EntityType::BUTTONS);
    _manager.addComponent(entityStart, ECS::ComponentType::SPRITE);
    ECS::Sprite *spriteStart = dynamic_cast<ECS::Sprite*>(_manager.getComponent(entityStart, ECS::ComponentType::SPRITE));
    sf::Sprite spriteStartTmp;
    spriteStartTmp.setTexture(*_graphical->getTexture("start"));
    spriteStart->setSprite(&spriteStartTmp);
    spriteStart->setIntRect(sf::IntRect(0, 0, 1135, 345));
    spriteStart->setPosition(sf::Vector2f(540, 800));
    spriteStart->setScale(sf::Vector2f(0.7, 0.7));
    _manager.addComponent(entityStart, ECS::ComponentType::TEXT);
    ECS::Text *textStart = dynamic_cast<ECS::Text*>(_manager.getComponent(entityStart, ECS::ComponentType::TEXT));
    textStart->setFont(*_graphical->getFont("origintech"));
    textStart->setSentence("Start");
    textStart->setSizeText(70);
    textStart->setPosition(sf::Vector2f(870, 880));
    _manager.addComponent(entityStart, ECS::ComponentType::POSITION);
    ECS::Position *PositionStart = dynamic_cast<ECS::Position*>(_manager.getComponent(entityStart, ECS::ComponentType::POSITION));
    PositionStart->setPosition_x(540);
    PositionStart->setPosition_y(800);
    _manager.addComponent(entityStart, ECS::ComponentType::HITBOX);
    ECS::Hitbox *hitboxStart = dynamic_cast<ECS::Hitbox*>(_manager.getComponent(entityStart, ECS::ComponentType::HITBOX));
    hitboxStart->setHeight(345);
    hitboxStart->setWidth(1135);

    _graphical->getWindow()->draw(*spriteBg->getSprite());
    _graphical->getWindow()->draw(*spriteLogo->getSprite());
    _graphical->getWindow()->draw(*spriteStart->getSprite());
    _graphical->getWindow()->draw(textStart->getText());
}

/**
 * It loads the menu
 */
void GameClient::manageMenu()
{
    loadMenu();
    if (_isInGame)
        _state = Game;
}

void GameClient::loadGame()
{
    ECS::Entity entityBg = _manager.createEntity(ECS::EntityType::GRAPHICS);
    _manager.addComponent(entityBg, ECS::ComponentType::SPRITE);
    ECS::Sprite *spriteBg = dynamic_cast<ECS::Sprite*>(_manager.getComponent(entityBg, ECS::ComponentType::SPRITE));
    sf::Sprite spriteBgTmp;
    spriteBgTmp.setTexture(*_graphical->getTexture("bg-game-2"));
    spriteBg->setSprite(&spriteBgTmp);
    spriteBg->setScale(sf::Vector2f(1.9, 1.9));

    ECS::Entity entityStars = _manager.createEntity(ECS::EntityType::GRAPHICS);
    _manager.addComponent(entityStars, ECS::ComponentType::SPRITE);
    ECS::Sprite *spriteStars = dynamic_cast<ECS::Sprite*>(_manager.getComponent(entityStars, ECS::ComponentType::SPRITE));
    sf::Sprite spriteStarsTmp;
    spriteStarsTmp.setTexture(*_graphical->getTexture("stars"));
    spriteStars->setSprite(&spriteStarsTmp);
    spriteStars->setScale(sf::Vector2f(1, 1));

    _graphical->getWindow()->draw(*spriteBg->getSprite());
    _graphical->getWindow()->draw(*spriteStars->getSprite());
}

/**
 * It loads the game
 */
void GameClient::manageGame()
{
    loadGame();
}
