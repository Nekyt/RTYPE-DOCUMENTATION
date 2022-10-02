/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "GraphicSystem.hpp"

/**
 * It clears the window and then for each entity, it checks if it's a valid entity, and if it is, it
 * sets the texture and the size of the entity
 */
void ECS::Graphic::preUpdate()
{
    window.clear();

    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        auto &rotation = _componentManager->getComponent(entity, ComponentType::ROTATION);
        auto &size = _componentManager->getComponent(entity, ComponentType::SIZE);
        auto &texture = _componentManager->getComponent(entity, ComponentType::TEXTURE);

        if (entity.getType() == EntityType::PLAYER)
            texture->setTexture("assets/entities/r-typesheet1-0.png");
            size->setSizeTexture_x(10);
            size->setSizeTexture_Y(10);
        if (entity.getType() == EntityType::ENNEMY)
            texture->setTexture("assets/entities/r-typesheet1-40.png");
            size->setSize_x(10);
            size->setSize_Y(10);
        rotation->setRotate(0);
        size->setSize(10);
    }
}

/**
 * It gets all the entities, checks if they have all the components needed to be drawn, and then draws
 * them
 */
void ECS::Graphic::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
         if (!checkIsValidEntity(entity))
            continue;
        auto &position = _componentManager->getComponent(entity, ComponentType::POSITION);
        auto &rotation = _componentManager->getComponent(entity, ComponentType::ROTATION);
        auto &size = _componentManager->getComponent(entity, ComponentType::SIZE);
        auto &textures = _componentManager->getComponent(entity, ComponentType::TEXTURE);
        sf::Texture texture;
        texture.loadFromFile(textures->getTexture);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(textures->getSizeTexture_x(), textures->getSizeTexture_y()));
        sprite.setPosition(position->getPosition_x(), position->getPosition_y());
        sprite.setRotation(rotation->getRotate());
        m_window.draw(sprite);
    }
}

/**
 * It draws the sprite to the screen
 */
void Graphic::postupdate()
{
    m_window->display();
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