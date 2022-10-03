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
        ECS::Text &text = dynamic_cast<ECS::Text&>(_componentManager->getComponent(entity, ComponentType::TEXT));

        text->setText("text de test");
    }
}

/**
 * It gets all the entities, checks if they are valid, gets the position and text components, creates a
 * sf::Text object, sets the font, text, position, and color, and then draws it to the window
 */
void ECS::TextSystem::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
         if (!checkIsValidEntity(entity))
            continue;
        ECS::Position &position = dynamic_cast<ECS::Position&>(_componentManager->getComponent(entity, ComponentType::POSITION));
        ECS::Text &texts = dynamic_cast<ECS::Text&>(_componentManager->getComponent(entity, ComponentType::TEXT));
        sf::Text text;
        sf::Font font;
        font.loadFromFile("assets/font/origintech.ttf");
        text.setFont(font);
        text.setString(texts->getText());
        text.setCharacterSize(24);
        text.setPosition(position.getPosition_x(), position.getPosition_y());
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