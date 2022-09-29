/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include "../Graphics/InitSfml.hpp"

class GameClient {
    public:
        GameClient();
        ~GameClient() = default;

        void gameLoop();
        void handleEvents(const sf::Event &event);

    protected:
    private:
        std::shared_ptr<InitSfml> _graphical;
};

#endif /* !GAMECLIENT_HPP_ */
