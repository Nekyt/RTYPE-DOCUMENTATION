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

        void loadComponents();
        void loadSystems();
        void gameLoop();
        void handleEvents(const sf::Event &event);
        void handleEventsKey(Button eventKey);
        void handleEventsTextEntered(const sf::Event &event);

        void selectMode();

    protected:
    private:
        GameState _state;

        Events _events;
        std::shared_ptr<InitSfml> _graphical;
};

#endif /* !GAMECLIENT_HPP_ */
