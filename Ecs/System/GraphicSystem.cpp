/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "GraphicSystem.hpp"


/**
 * It clears the window, then it checks if the entity is valid, then it checks if the entity is a
 * player or an ennemy, then it sets the texture and the size of the entity
 */
void ECS::Graphic::preUpdate()
{
    window.clear(sf::Color::Black);

    const auto &entities = _entityManager->getEntities();

    for (const auto &entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        ECS::Rotate &rotation = dynamic_cast<ECS::Rotate&>(getComponent(entity, ComponentType::ROTATION));
        ECS::Size &size = dynamic_cast<ECS::Size&>(entity, ComponentType::SIZE);
        ECS::Texture &texture = dynamic_cast<ECS::Texture&>(entity, ComponentType::TEXTURE);

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
 * It takes all the entities that have a position, rotation, size and texture component, and draws them
 * to the screen
 */
void ECS::Graphic::update()
{
    const auto &entities = _entityManager->getEntities();
    for (const auto &entity : entities) {
         if (!checkIsValidEntity(entity))
            continue;
        ECS::Position &position = dynamic_cast<ECS::Position&>(entity, ComponentType::POSITION);
        ECS::Rotate &rotation = dynamic_cast<ECS::Rotate&>(getComponent(entity, ComponentType::ROTATION));
        ECS::Size &size = dynamic_cast<ECS::Size&>(entity, ComponentType::SIZE);
        ECS::Texture &textures = dynamic_cast<ECS::Texture&>(entity, ComponentType::TEXTURE);
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
    ECS::Component &component = dynamic_cast<ECS::Component&>(getComponentList());

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