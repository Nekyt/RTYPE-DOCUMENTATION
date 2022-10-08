/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "GraphicSystem.hpp"

/**
 * It gets all the entities, checks if they are valid, and then sets the texture and rotation of the
 * entity
 */
void ECS::Graphic::preUpdate()
{
    _window->clear(sf::Color::Black);

    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        ECS::Rotate *rotation = dynamic_cast<ECS::Rotate*>(_componentManager->getComponent(entity, ComponentType::ROTATION));
        ECS::Sprite *sprite = dynamic_cast<ECS::Sprite*>(_componentManager->getComponent(entity, ComponentType::SPRITE));
        std::shared_ptr<sf::Texture> sfmlTexture;

        if (entity.getType() == EntityType::PLAYER) {
            sfmlTexture = _sfml->getTexture("logo");
            sprite->setTexture(*sfmlTexture);
            sprite->setRectSizeX(10);
            sprite->setRectSizeY(10);
            sprite->setRectPosX(0);
            sprite->setRectPosY(0);
        }
        if (entity.getType() == EntityType::ENEMY) {
            sfmlTexture = _sfml->getTexture("bg-menu");
            sprite->setTexture(*sfmlTexture);
            sprite->setRectSizeX(10);
            sprite->setRectSizeY(10);
            sprite->setRectPosX(0);
            sprite->setRectPosY(0);
        }
        rotation->setRotate(0);
    }
}

/**
 * It takes all the entities that have a graphic component, and draws them on the screen
 */
void ECS::Graphic::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        ECS::Position *position = dynamic_cast<ECS::Position*>(_componentManager->getComponent(entity, ComponentType::POSITION));
        ECS::Rotate *rotation = dynamic_cast<ECS::Rotate*>(_componentManager->getComponent(entity, ComponentType::ROTATION));
        ECS::Sprite *sprite = dynamic_cast<ECS::Sprite*>(_componentManager->getComponent(entity, ComponentType::SPRITE));

        _window->draw(*sprite->getSprite());
    }
}

/**
 * It draws the sprite to the screen
 */
void ECS::Graphic::postUpdate()
{
    _window->display();
}

/**
 * It sets the sfml pointer to the one passed in
 *
 * @param sfml The InitSfml class that is used to initialize the SFML library.
 */
void ECS::Graphic::setSfml(std::shared_ptr<InitSfml> sfml)
{
    _sfml = sfml;
    _window = sfml->getWindow();
}

/**
 * If the entity has a position, rotation, and texture component, then it's a valid entity
 *
 * @param entity The entity to check
 *
 * @return A boolean value.
 */
bool ECS::Graphic::checkIsValidEntity(Entity entity)
{
    auto &components = _componentManager->getComponentList(entity);

    try
    {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::ROTATION);
        components.at(ComponentType::SPRITE);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}