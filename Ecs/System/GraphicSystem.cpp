/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** system
*/

#include "GraphicSystem.hpp"

/**
 * It's a constructor for the GraphicSystem class
 *
 * @param componentsManager The ComponentManager that the system will use to get
 * components from.
 * @param entityManager The entity manager that the system will use to get
 * entities.
 */
ECS::GraphicSystem::GraphicSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager)
    : System(componentsManager, entityManager)
{
}

/**
 * It takes all the entities that have a graphic component, and draws them on the screen
 */
void ECS::GraphicSystem::update()
{
    const auto& entities = _entityManager->getEntities();
    //std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> enti = _clock->getEntitiesToUpdate();

    //for (size_t i = 0; i < enti.size(); ++i) {
        for (const auto& entity : entities) {
            // if (entity.getId() != enti[i].first)
            //     continue;
            if (!checkIsValidEntity(entity))
                continue;
            std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_componentManager->getComponent(entity, ComponentType::POSITION));
            //std::shared_ptr<ECS::Rotate> rotation = std::dynamic_pointer_cast<ECS::Rotate>(_componentManager->getComponent(entity, ComponentType::ROTATION));
            std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(_componentManager->getComponent(entity, ComponentType::SPRITE));

            // setIntRect clock
            // std::shared_ptr<sf::Texture> sfmlTexture = sprite->getTexture();
            // sprite->setTexture(*sfmlTexture);
            sprite->setPosition(position->getPosition_x(), position->getPosition_y());
            sprite->setScale(sprite->getScale());
            _window->draw(*sprite->getSprite());
        }
    //}
}

/**
 * It sets the sfml pointer to the one passed in
 *
 * @param sfml The InitSfml class that is used to initialize the SFML library.
 */
void ECS::GraphicSystem::setSfml(std::shared_ptr<InitSfml> sfml)
{
    _sfml = sfml;
    _window = sfml->getWindow();
}

void ECS::GraphicSystem::setClock(std::shared_ptr<Clock> clock)
{
    _clock = clock;
}

/**
 * If the entity has a position, rotation, and texture component, then it's a valid entity
 *
 * @param entity The entity to check
 *
 * @return A boolean value.
 */
bool ECS::GraphicSystem::checkIsValidEntity(Entity entity)
{
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::POSITION);
        components.at(ComponentType::SPRITE);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}