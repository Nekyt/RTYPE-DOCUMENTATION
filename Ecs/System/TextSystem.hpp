/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** TextSystem
*/

#ifndef TEXTSYSTEM_HPP_
#define TEXTSYSTEM_HPP_

#include "./System.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Texte.hpp>

namespace ECS
{
    class TextSystem {
        public:
            TextSystem(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager);
            ~TextSystem() = default;
            void preUpdate();
            void update();
            bool checkIsValidEntity(Entity entity);
        protected:
        private:
            sf::RenderWindow window;
    };
}

#endif /* !TEXTSYSTEM_HPP_ */
