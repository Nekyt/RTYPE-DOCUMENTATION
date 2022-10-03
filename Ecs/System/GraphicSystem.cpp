/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "GraphicSystem.hpp"

/**
 * It checks if the entity is valid, then it sets the texture, the size and the rotation of the entity
 */
void ECS::Graphic::preUpdate()
{
    window.clear(sf::Color::Black);

    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        ECS::Rotate &rotation = dynamic_cast<ECS::Rotate&>(_componentManager->getComponent(entity, ComponentType::ROTATION));
        ECS::Size &size = dynamic_cast<ECS::Size&>(_componentManager->getComponent(entity, ComponentType::SIZE));
        ECS::Texture &texture = dynamic_cast<ECS::Texture&>(_componentManager->getComponent(entity, ComponentType::TEXTURE));

        if (entity.getType() == EntityType::PLAYER)
            texture.setTexture("assets/entities/r-typesheet1-0.png");
            texture.setSizeTexture_x(10);
            texture.setSizeTexture_Y(10);
        if (entity.getType() == EntityType::ENEMY)
            texture.setTexture("assets/entities/r-typesheet1-40.png");
            texture.setSizeTexture_x(10);
            texture.setSizeTexture_y(10);
        rotation.setRotate(0);
        size.setSize(10);
    }
}

/**
 * It takes all the entities that have a position, rotation, size and texture component, and draws them
 * to the screen
 */
void ECS::Graphic::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
         if (!checkIsValidEntity(entity))
            continue;
        ECS::Position &position = dynamic_cast<ECS::Position&>(_componentManager->getComponent(entity, ComponentType::POSITION));
        ECS::Rotate &rotation = dynamic_cast<ECS::Rotate&>(_componentManager->getComponent(entity, ComponentType::ROTATION));
        ECS::Size &size = dynamic_cast<ECS::Size&>(_componentManager->getComponent(entity, ComponentType::SIZE));
        ECS::Texture &textures = dynamic_cast<ECS::Texture&>(_componentManager->getComponent(entity, ComponentType::TEXTURE));
        sf::Texture texture;
        texture.loadFromFile(textures.getTexture());
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(textures.getSizeTexture_x(), textures.getSizeTexture_y()));
        sprite.setPosition(position.getPosition_x(), position.getPosition_y());
        sprite.setRotation(rotation.getRotate());
        window.draw(sprite);
    }
}

/**
 * It draws the sprite to the screen
 */
void ECS::Graphic::postUpdate()
{
    window.display();
}

/**
 * If the entity has all the components required to be drawn, return true
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
        components.at(ComponentType::SIZE);
        components.at(ComponentType::TEXTURE);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}