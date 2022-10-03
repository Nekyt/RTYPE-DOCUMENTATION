/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#ifndef GRAPHICSYSTEM_HPP_
#define GRAPHICSYSTEM_HPP_

#include "./System.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ECS
{
    class Graphic : public System{
        public:
            Graphic(const std::shared_ptr<ComponentManager> &componentsManager, const std::shared_ptr<EntityManager> &entityManager);
            ~Graphic() = default;

            void preUpdate();
            void update();
            void postUpdate();
            bool checkIsValidEntity(Entity entity);

        protected:
        private:
            sf::RenderWindow window;
    };
}

#endif /* !SYSTEM_HPP_ */
