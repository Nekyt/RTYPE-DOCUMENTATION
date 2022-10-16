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
    _clock = std::make_shared<Clock>();
    _state = Menu;
    _isInGame = false;
    _nbrPlayersInGameReached = false;
    setSfml();
    loadSystems();
    loadMenu();
    loadGame();
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
    _graphical->setTexture("player", "Assets/entities/r-typesheet1-0.png");
    _graphical->setTexture("enemy", "Assets/entities/r-typesheet1-1.png");
    _graphical->setFont("origintech", "Assets/font/origintech.ttf");
    // _graphical->setMusic("menu", "space_oddity-menu.ogg");
}

/**
 * It loads the systems
 */
void GameClient::loadSystems()
{
    auto& graphic = _manager.addSystem<ECS::GraphicSystem>();
    graphic.setSfml(_graphical);
    graphic.setClock(_clock);
    auto& text = _manager.addSystem<ECS::TextSystem>();
    text.setSfml(_graphical);
    auto& move = _manager.addSystem<ECS::MoveSystem>();
    move.setClock(_clock);
}

/**
 * It's a loop that handles events and draws the game
 */
void GameClient::gameLoop()
{
    while (_graphical->getWindow()->isOpen()) {
        while (_graphical->getWindow()->pollEvent(_graphical->getEvent())) {
            const sf::Event& event = _graphical->getEvent();
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
void GameClient::handleEvents(const sf::Event& event)
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
void GameClient::mouseMenu(const sf::Event& event)
{
    const auto& entities = _manager.getEntities();
    Mouse eventMouse = _events.getEventTypeMouse(event);

    if (eventMouse == Mouse::Left) {
        sf::Vector2i position = sf::Mouse::getPosition(*_graphical->getWindow());
        for (const auto& entity : entities) {
            if (entity.getType() == ECS::EntityType::BUTTONS) {
                std::shared_ptr<ECS::Position> positionEntity = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(entity, ECS::ComponentType::POSITION));
                std::shared_ptr<ECS::Hitbox> hitboxEntity = std::dynamic_pointer_cast<ECS::Hitbox>(_manager.getComponent(entity, ECS::ComponentType::HITBOX));
                if (position.x > positionEntity->getPosition_x() && position.x < positionEntity->getPosition_x() + hitboxEntity->getWidth() && position.y > positionEntity->getPosition_y() && position.y < positionEntity->getPosition_y() + hitboxEntity->getHeight())
                    _isInGame = true; // send client click to ready
            }
        }
    }
}

/**
 * It handles mouse events based on the current game state
 *
 * @param event The event that was triggered.
 */
void GameClient::handleEventsMouse(const sf::Event& event)
{
    switch (_state) {
    case GameState::Menu:
        mouseMenu(event);
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
        _gameCommandsList.push_back(eventKey);
        break;
    default:
        break;
    }
}

/**
 * Send commands to the server.
 */
void GameClient::sendCommandsToServer()
{
    // network send commands (_gameCommandsList)
    _gameCommandsList.clear();
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

/* It creates the entities and components needed to display the menu. */
void GameClient::loadMenu()
{
    ECS::Entity entityBg = _manager.createEntity(ECS::EntityType::MENU);
    _manager.addComponent(entityBg, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("bg-menu"), sf::Vector2f(1.9, 1.9)));
    std::shared_ptr<ECS::Sprite> spriteBg = std::dynamic_pointer_cast<ECS::Sprite>(_manager.getComponent(entityBg, ECS::ComponentType::SPRITE));
    _spriteMenu.push_back(spriteBg);
    ECS::Entity entityLogo = _manager.createEntity(ECS::EntityType::MENU);
    _manager.addComponent(entityLogo, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("logo"), 1, 1, 0, 0, 0, 0, sf::Vector2f(610, 310)));
    std::shared_ptr<ECS::Sprite> spriteLogo = std::dynamic_pointer_cast<ECS::Sprite>(_manager.getComponent(entityLogo, ECS::ComponentType::SPRITE));
    _spriteMenu.push_back(spriteLogo);
    // if (_nbrPlayersInGameReached == false) {
    //     ECS::Entity entityLoading = _manager.createEntity(ECS::EntityType::MENU);
    //     _manager.addComponent(entityLoading, ECS::ComponentType::TEXT, std::make_shared<ECS::Text>(*_graphical->getFont("origintech"), "Loading ...", 70, sf::Vector2f(800, 800)));
    //     std::shared_ptr<ECS::Text> textLoading = std::dynamic_pointer_cast<ECS::Text>(_manager.getComponent(entityLoading, ECS::ComponentType::TEXT));
    //     _textMenu.push_back(textLoading);
    // } else {
    ECS::Entity entityStart = _manager.createEntity(ECS::EntityType::BUTTONS);
    _manager.addComponent(entityStart, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("start"), sf::Vector2f(0.7, 0.7), sf::IntRect(0, 0, 1135, 345), sf::Vector2f(540, 800)));
    std::shared_ptr<ECS::Sprite> spriteStart = std::dynamic_pointer_cast<ECS::Sprite>(_manager.getComponent(entityStart, ECS::ComponentType::SPRITE));
    _spriteMenu.push_back(spriteStart);
    _manager.addComponent(entityStart, ECS::ComponentType::TEXT, std::make_shared<ECS::Text>(*_graphical->getFont("origintech"), "Ready", 70, sf::Vector2f(870, 880)));
    std::shared_ptr<ECS::Text> textStart = std::dynamic_pointer_cast<ECS::Text>(_manager.getComponent(entityStart, ECS::ComponentType::TEXT));
    _textMenu.push_back(textStart);
    _manager.addComponent(entityStart, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(540, 800));
    std::shared_ptr<ECS::Position> PositionStart = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(entityStart, ECS::ComponentType::POSITION));
    _manager.addComponent(entityStart, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(345, 1135));
    std::shared_ptr<ECS::Hitbox> hitboxStart = std::dynamic_pointer_cast<ECS::Hitbox>(_manager.getComponent(entityStart, ECS::ComponentType::HITBOX));
    //}
}

/**
 * It draws the menu
 */
void GameClient::manageMenu()
{
    for (auto& sprite : _spriteMenu)
        _graphical->getWindow()->draw(*sprite->getSprite());
    for (auto& text : _textMenu)
        _graphical->getWindow()->draw(text->getText());
    if (_isInGame)
        _state = Game;
}

/**
 * It creates two entities, one for the background and one for the stars, and adds
 * the components needed to make them move
 */
void GameClient::loadGame()
{
    ECS::Entity entityBg = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityBg, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(0, 0));
    _manager.addComponent(entityBg, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(3));
    _manager.addComponent(entityBg, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityBg, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("bg-game-2"), sf::Vector2f(1.9, 1.9)));
    _clock->addClockComponent(entityBg.getId(), ECS::ComponentType::POSITION, 400);

    ECS::Entity entityBg2 = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityBg2, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(1920, 0));
    _manager.addComponent(entityBg2, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(3));
    _manager.addComponent(entityBg2, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityBg2, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("bg-game-2"), sf::Vector2f(1.9, 1.9), sf::IntRect(0, 0, 0, 0), sf::Vector2f(1920, 0)));
    _clock->addClockComponent(entityBg2.getId(), ECS::ComponentType::POSITION, 400);

    ECS::Entity entityStars = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityStars, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(0, 0));
    _manager.addComponent(entityStars, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(5));
    _manager.addComponent(entityStars, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityStars, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("stars"), sf::Vector2f(0.6, 0.6)));
    _clock->addClockComponent(entityStars.getId(), ECS::ComponentType::POSITION, 400);

    ECS::Entity entityStars2 = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityStars2, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(1920, 0));
    _manager.addComponent(entityStars2, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(5));
    _manager.addComponent(entityStars2, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityStars2, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("stars"), sf::Vector2f(0.6, 0.6), sf::IntRect(0, 0, 0, 0), sf::Vector2f(1920, 0)));
    _clock->addClockComponent(entityStars2.getId(), ECS::ComponentType::POSITION, 400);
}

/**
 * It updates the game
 */
void GameClient::manageGame()
{
    try {
        _manager.getSystem<ECS::MoveSystem>().update();
        _manager.getSystem<ECS::GraphicSystem>().update();
        _manager.getSystem<ECS::TextSystem>().update();
        sendCommandsToServer();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
