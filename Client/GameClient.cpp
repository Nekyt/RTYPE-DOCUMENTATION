/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#include "GameClient.hpp"
#include "../Network/PacketOperatorSurcharge.hpp"
#include <unistd.h>

/**
 * It initializes the random number generator, creates a graphical interface, sets
 * the state to Menu, sets the isInGame variable to false, sets the SFML interface,
 * and loads the systems.
 */
GameClient::GameClient(const char* ip, unsigned short port) : _cli(ip, port)
{
    srand(time(NULL));
    _playerID = -1;
    _graphical = std::make_shared<InitSfml>();
    _networkClock = std::make_shared<Clock>();
    _networkClock->addClockComponent(0, ECS::ComponentType::NETWORK, 50);
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
    _graphical->setTexture("player", "Assets/entities/r-typesheet1-35.png");
    _graphical->setTexture("enemy", "Assets/entities/r-typesheet1-0.png");
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

void GameClient::waitEnumTCP(Network::Networking net)
{
    int networkType = -1;

    while (networkType != net) {
        if (!_retrievedPacketsTCP.empty() && _retrievedPacketsTCP[0].getDataSize()) {
            _retrievedPacketsTCP[0] >> networkType;
            _retrievedPacketsTCP.erase(_retrievedPacketsTCP.begin());
        }
    }
    std::cout << "Enum : " << net << " aquired" << std::endl;
}

void GameClient::waitConnected()
{
    int networkType = -1;

    std::cout << "WAIT CONNECTED" << std::endl;
    while (_playerID == -1) {
        if (!_retrievedPacketsTCP.empty() && _retrievedPacketsTCP[0].getDataSize()) {
            _retrievedPacketsTCP[0] >> networkType;
            if (networkType == Network::Networking::CONNECTED)
                _retrievedPacketsTCP[0] >> _playerID;
            else if (networkType != Network::Networking::ERROR)
                std::cout << "ENUM RETRIEVED : " << networkType << std::endl;
            _retrievedPacketsTCP.erase(_retrievedPacketsTCP.begin());
        }
    }
    std::cout << "Enum : " << networkType << " aquired" << std::endl;
}

void GameClient::waitEnumUDP(Network::Networking net)
{
    int networkType = -1;

    while (networkType != net) {
        if (!_retrievedPacketsUDP.empty() && _retrievedPacketsUDP[0].getDataSize()) {
            _retrievedPacketsUDP[0] >> networkType;
            _retrievedPacketsUDP.pop_front();
        }
    }
    std::cout << "Enum : " << net << " aquired" << std::endl;
}

/**
 * It takes a Network::Networking enum as a parameter, and depending on the value of the enum, it will
 * add the appropriate data to the packet
 *
 * @param net The enum that will be used to identify the packet.
 */
void GameClient::empacketing(Network::Networking net)
{
    sf::Packet pack;

    pack << net;
    std::cout << "empacketing enum : " << net << std::endl;
    if (net == Network::Networking::PLAYERUPDATE) {
        pack << _gameCommandsList;
        _gameCommandsList.clear();
    }
    _sendingPacketsUDP.push_back(pack);
}

void GameClient::sendReady()
{
    sf::Packet pack;

    std::cout << "Sending roomid: " << _roomId << std::endl;
    pack << Network::Networking::READY << _roomId << _playerID;
    // _cli.sendPacketTCP(pack);
    _sendingPacketsTCP.push_back(pack);
}

/**
 * It's a game loop that handles the events, displays the game, and retrieves the packets
 */
void GameClient::gameLoop()
{
    //Thread TCP
    sf::Thread tcp(&GameClient::retrievePacketsTCP, this);
    sf::Thread thread(&GameClient::retrievePacketsUDP, this);

    //launching thread tcp std::deque<std::pair<size_t, std::pair<int, int>>>
    std::deque<std::pair<size_t, std::pair<int, int>>> rooms = _cli.roomAskingList();
    _retrievingTCP = true;
    tcp.launch();
    std::cout << "ASKING FOR ROOMS LIST" << std::endl;
    while (rooms.empty()) {
        _cli.roomCreation(2);
        std::cout << "CREATE A ROOM" << std::endl;
        rooms = _cli.roomAskingList();
        std::cout << "ASKING FOR ROOMS LIST" << std::endl;
    }
    for (auto r : rooms) {
        if (r.second.first != r.second.second) {
            _roomId = r.first;
            break;
        }
    }
    while (_graphical->getWindow()->isOpen()) {
        while (_graphical->getWindow()->pollEvent(_graphical->getEvent())) {
            const sf::Event& event = _graphical->getEvent();
            handleEvents(event);
        }
        _graphical->clear();
        selectMode();
        _graphical->display();
        if (!_retrievingUDP && _state == GameState::Game) {
            _graphEntitiesCount = static_cast<int>(_manager.getEntities().size());
            _retrievingUDP = true;
            thread.launch();
            sf::Packet pack;
            pack << Network::Networking::ROOMCONNECT << 0 << _cli.getUdpAddress();
            _sendingPacketsTCP.push_back(pack);
            std::cout << "JOINING ROOM" << std::endl;
            waitConnected();
            // start UDP here
            waitEnumTCP(Network::Networking::READY);
            sendReady();
            waitEnumUDP(Network::Networking::LAUNCHING);
        } else if (_retrievingUDP && _state != GameState::Game) {
            thread.terminate();
            _retrievingUDP = false;
            _sendingPacketsUDP.clear();
            _retrievedPacketsUDP.clear();
        }
    }
    _networkClock->eraseClock(0);
    if (_retrievingUDP == true)
        thread.terminate();
}

/**
 * It handles the events
 *
 * @param event The event to handle.
 */
void GameClient::handleEvents(const sf::Event& event)
{
    std::deque<Button> eventKey = _events.getEventType(event);

    if (event.type == sf::Event::Closed)
        _graphical->getWindow()->close();
    else if (event.type == sf::Event::MouseButtonReleased)
        handleEventsMouse(event);
    else if (event.type == sf::Event::KeyPressed && !eventKey.empty())
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
    sf::Packet packet;

    if (eventMouse == Mouse::Left) {
        sf::Vector2i position = sf::Mouse::getPosition(*_graphical->getWindow());
        for (const auto& entity : entities) {
            if (entity.getType() == ECS::EntityType::BUTTONS) {
                std::shared_ptr<ECS::Position> positionEntity = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(entity, ECS::ComponentType::POSITION));
                std::shared_ptr<ECS::Hitbox> hitboxEntity = std::dynamic_pointer_cast<ECS::Hitbox>(_manager.getComponent(entity, ECS::ComponentType::HITBOX));
                if (position.x > positionEntity->getPosition_x() && position.x < positionEntity->getPosition_x() + hitboxEntity->getWidth() && position.y > positionEntity->getPosition_y() && position.y < positionEntity->getPosition_y() + hitboxEntity->getHeight()) {
                    _isInGame = true;
                    //packet << Network::Networking::READY;
                    //_sendingPackets.push_back(packet);
                }
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
void GameClient::handleEventsKey(std::deque<Button> eventKey)
{
    switch (_state) {
    case GameState::Game:
        for (size_t i = 0; i < eventKey.size(); ++i)
            if (std::find(_gameCommandsList.begin(), _gameCommandsList.end(), eventKey[i]) ==_gameCommandsList.end())
                _gameCommandsList.push_back(eventKey[i]);
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
    _clock->addClockComponent(entityBg.getId(), ECS::ComponentType::POSITION, 40);

    ECS::Entity entityBg2 = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityBg2, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(1920, 0));
    _manager.addComponent(entityBg2, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(3));
    _manager.addComponent(entityBg2, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityBg2, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("bg-game-2"), sf::Vector2f(1.9, 1.9), sf::IntRect(0, 0, 0, 0), sf::Vector2f(1920, 0)));
    _clock->addClockComponent(entityBg2.getId(), ECS::ComponentType::POSITION, 40);

    ECS::Entity entityStars = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityStars, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(0, 0));
    _manager.addComponent(entityStars, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(5));
    _manager.addComponent(entityStars, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityStars, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("stars"), sf::Vector2f(0.6, 0.6)));
    _clock->addClockComponent(entityStars.getId(), ECS::ComponentType::POSITION, 40);

    ECS::Entity entityStars2 = _manager.createEntity(ECS::EntityType::PARALLAX);
    _manager.addComponent(entityStars2, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(1920, 0));
    _manager.addComponent(entityStars2, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(5));
    _manager.addComponent(entityStars2, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
    _manager.addComponent(entityStars2, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("stars"), sf::Vector2f(0.6, 0.6), sf::IntRect(0, 0, 0, 0), sf::Vector2f(1920, 0)));
    _clock->addClockComponent(entityStars2.getId(), ECS::ComponentType::POSITION, 40);
}

/**
 * It retrieves packets from the client and puts them in a deque
 */
void GameClient::retrievePacketsUDP()
{
    sf::Packet pack;
    //_cli.connectUDP();

    std::cout << std::boolalpha << "_retrievingUDP is " << _retrievingUDP << std::endl;
    while (_retrievingUDP) {
        pack = _cli.retrievePacketUDP();
        if (pack.getDataSize()) {
            _retrievedPacketsUDP.push_back(pack);
            pack.clear();
        }
        if (!_sendingPacketsUDP.empty()) {
            if (!_cli.sendPacketUDP(_sendingPacketsUDP[0]))
                _sendingPacketsUDP.erase(_sendingPacketsUDP.begin());
        }
    }
}

/**
 * It retrieves packets from the client and puts them in a deque
 */
void GameClient::retrievePacketsTCP()
{
    sf::Packet pack;

    while (_retrievingTCP) {
        pack = _cli.retrievePacketTCP();
        if (pack.getDataSize()) {
            _retrievedPacketsTCP.push_back(pack);
            pack.clear();
        }
        if (!_sendingPacketsTCP.empty()) {
            if (!_cli.sendPacketTCP(_sendingPacketsTCP[0]))
                _sendingPacketsTCP.erase(_sendingPacketsTCP.begin());
        }
    }
}

/**
 * It updates the game
 */
void GameClient::manageGame()
{
    int netw;
    sf::Packet pack;
    std::deque<std::pair<ECS::Entity, ECS::Position>> entitiesUpdate;
    std::shared_ptr<ECS::Position> pos;
    std::shared_ptr<ECS::Sprite> sprite;
    std::deque<ECS::Entity> entities;
    int playerID;
    std::shared_ptr<sf::Texture> texture;

    if (!_retrievedPacketsUDP.empty()) {
        pack = _retrievedPacketsUDP[0];
        _retrievedPacketsUDP.erase(_retrievedPacketsUDP.begin());
        pack >> netw;
        if (netw == Network::Networking::GAMEUPDATE) {
            pack >> entitiesUpdate;
            if (_manager.getEntities().size() == _graphEntitiesCount) {
                for (auto entity : entitiesUpdate) {
                    std::cout << "RIGHT HERE : " << entity.first.getId() << std::endl;
                    _manager.createEntity(entity.first.getType());
                    _manager.addComponent(_manager.getEntityById(entity.first.getId() + _graphEntitiesCount), ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(entity.second));
                    if (entity.first.getType() == ECS::EntityType::PLAYER)
                        _manager.addComponent(_manager.getEntityById(entity.first.getId() + _graphEntitiesCount), ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("player"), 3, 3, 1, 3, 31, 13, sf::Vector2f(entity.second.getPosition_x(), entity.second.getPosition_y())));
                    else if (entity.first.getType() == ECS::EntityType::ENEMY)
                        _manager.addComponent(_manager.getEntityById(entity.first.getId() + _graphEntitiesCount), ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("enemy"), 3, 3, 333, 3, 31, 11, sf::Vector2f(entity.second.getPosition_x(), entity.second.getPosition_y())));
                }
            } else {
                for (auto entity : entitiesUpdate) {
                    pos = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(_manager.getEntityById(entity.first.getId() + _graphEntitiesCount), ECS::ComponentType::POSITION));
                    pos->setPosition_x(entity.second.getPosition_x());
                    pos->setPosition_y(entity.second.getPosition_y());
                    sprite = std::dynamic_pointer_cast<ECS::Sprite>(_manager.getComponent(_manager.getEntityById(entity.first.getId() + _graphEntitiesCount), ECS::ComponentType::SPRITE));
                    sprite->setPosition(sf::Vector2f(pos->getPosition_x(), pos->getPosition_y()));
                    //std::cout << entity.first.getId() + _graphEntitiesCount << " pos : x=" << pos->getPosition_x() << " y=" << pos->getPosition_y() << std::endl;
                }
                //std::cout << std::endl;
            }
        } else if (netw == Network::Networking::PLAYERDEATH || netw == Network::Networking::PLAYERDISCONNECTED) {
            pack >> playerID;
            if (playerID == _playerID) {
                entities = _manager.getEntities();
                for (size_t i = _graphEntitiesCount; i < entities.size(); ++i)
                    _manager.destroyEntity(_manager.getEntityById(i));
                _isInGame = false;
                _state = Menu;
            } else
                _manager.destroyEntity(_manager.getEntityById(playerID + _graphEntitiesCount));
        }
    }
    try {
        _manager.getSystem<ECS::MoveSystem>().update();
        _manager.getSystem<ECS::GraphicSystem>().update();
        _manager.getSystem<ECS::TextSystem>().update();
        if (_networkClock->componentUpdateNumber(0, ECS::ComponentType::NETWORK) && !_gameCommandsList.empty())
            empacketing(Network::Networking::PLAYERUPDATE);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}