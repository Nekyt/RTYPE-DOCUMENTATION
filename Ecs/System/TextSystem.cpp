/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** TextSystem
*/

#include "TextSystem.hpp"

/**
 * It's a constructor for the TextSystem class
 *
 * @param componentsManager The ComponentManager that the system will use to get
 * components.
 * @param entityManager The entity manager that the system will use to get
 * entities.
 */
ECS::TextSystem::TextSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

/**
 * It draws the text on the screen
 */
void ECS::TextSystem::update()
{
    const auto& entities = _entityManager->getEntities();
    for (const auto& entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        ECS::Position* position = dynamic_cast<ECS::Position*>(_componentManager->getComponent(entity, ComponentType::POSITION));
        ECS::Text* text = dynamic_cast<ECS::Text*>(_componentManager->getComponent(entity, ComponentType::TEXT));
        text->setFont(*_sfml->getFont("origintech"));
        text->setSentence(text->getSentence());
        text->setSizeText(text->getTextSize());
        text->setPosition(position->getPosition_x(), position->getPosition_y());
        _window->draw(text->getText());
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
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::TEXT);
    } catch (const std::exception& e) {
        return false;
    }
}