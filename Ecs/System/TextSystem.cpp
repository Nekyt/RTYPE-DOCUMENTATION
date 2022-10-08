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
        ECS::Text *text = dynamic_cast<ECS::Text*>(_componentManager->getComponent(entity, ComponentType::TEXT));
        text->setSizeText(24);
        text->setSentence("text de test");
    }
}

/**
 * It draws the text on the screen
 */
void ECS::TextSystem::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
         if (!checkIsValidEntity(entity))
            continue;
        ECS::Position *position = dynamic_cast<ECS::Position*>(_componentManager->getComponent(entity, ComponentType::POSITION));
        ECS::Text *texts = dynamic_cast<ECS::Text*>(_componentManager->getComponent(entity, ComponentType::TEXT));
        sf::Font font;
        sf::Text *text = &texts->getText();
        text->setFont(font);
        text->setString(texts->getSentence());
        text->setCharacterSize(texts->getTextSize());
        text->setPosition(position->getPosition_x(), position->getPosition_y());
        text->setFillColor(sf::Color::White);
        _window->draw(*text);
    }
}

/**
 * This function sets the sfml pointer to the sfml pointer passed in as a parameter
 *
 * @param sfml This is the InitSfml class that we created in the previous chapter.
 */
void ECS::TextSystem::setSfml(std::shared_ptr<InitSfml> sfml)
{
    _sfml = sfml;
    _window = sfml->getWindow();
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