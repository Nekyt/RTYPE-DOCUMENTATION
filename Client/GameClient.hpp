/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include "../Graphics/InitSfml.hpp"
#include "../Graphics/Events.hpp"
#include "../Ecs/Manager.hpp"

enum GameState
{
    Menu,
    Game,
    Options,
};

class GameClient {
    public:
        GameClient();
        ~GameClient() = default;

        void setSfml();

        void loadComponents();
        void loadSystems();
        void gameLoop();
        void handleEvents(const sf::Event &event);
        void handleEventsMouse();
        void handleEventsKey(Button eventKey);
        void handleEventsTextEntered(const sf::Event &event);

        void eventKeyMenu(Button eventKey);

        void selectMode();

        void manageMenu();
        void manageGame();

    protected:
    private:
        GameState _state;
        Manager _manager;

        Events _events;
        std::shared_ptr<InitSfml> _graphical;
        sf::Sprite _sprite;
};

#endif /* !GAMECLIENT_HPP_ */
