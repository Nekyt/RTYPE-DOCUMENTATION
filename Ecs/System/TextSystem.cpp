/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** TextSystem
*/

#include "TextSystem.hpp"

/**
 * It sets the text of all entities with a text component to "text de test"
 */
void ECS::TextSystem::preUpdate()
{
    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        auto &text = _componentManager->getComponent(entity, ComponentType::TEXT);

        text->setText("text de test");
    }
}

/**
 * For each entity, if the entity has a position and text component, then create a text object and set
 * its font, string, character size, and color
 */
void ECS::TextSystem::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
         if (!checkIsValidEntity(entity))
            continue;
        auto &position = _componentManager->getComponent(entity, ComponentType::POSITION);
        auto &texts = _componentManager->getComponent(entity, ComponentType::TEXT);
        sf::Text text;
        sf::Font font;
        font.loadFromFile("assets/font/origintech.ttf");
        text.setFont(font);
        text.setString(texts->getText());
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }
}

/**
 * If the entity has a position and text component, then it's a valid entity
 * 
 * @param entity The entity to check
 * 
 * @return A boolean value.
 */
bool ECS::TextSystem::checkIsValidEntity(Entity entity)
{
    auto &components = _componentManager->getComponentList(entity);

    try
    {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::TEXT);
    }
    catch(const std::exception& e)
    {
        return false;
    }
}