/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** BonusSystem
*/

#include "BonusSystem.hpp"

/**
 * It's the constructor for the BonusSystem class.
 * 
 * @param componentsManager The ComponentManager that will be used to get the
 * components of the entities.
 * @param entityManager The entity manager that the system will use to get
 * entities.
 */
ECS::BonusSystem::BonusSystem(const std::shared_ptr<ComponentManager>& componentsManager, const std::shared_ptr<EntityManager>& entityManager) : System(componentsManager, entityManager)
{
}

/**
 * It creates a bonus entity if there are less than 3 bonus entities on the screen
 */
void ECS::BonusSystem::update()
{
    const auto& entities = _entityManager->getEntities();
    std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> enti = _clock->getEntitiesToUpdate();
    int nbrBonus = 0;

    for (const auto& entity : entities) {
        if (!checkIsValidEntity(entity))
            continue;
        nbrBonus++;
        if (nbrBonus > 0) {
            for (size_t i = 0; i < enti.size(); ++i) {
                if (entity.getId() != enti.at(i).first)
                    continue;
                for (size_t j = 0; j < enti.at(i).second.size(); ++j)
                    if (enti.at(i).second.at(j) != ECS::ComponentType::BONUS)
                        continue;
            }
        }
    }
    if (nbrBonus < 3) {
        ECS::Entity entityBonus = _entityManager->createEntity(ECS::EntityType::BONUSENTITY);
        double pourcentage = rand() % 100;
        ECS::BonusType type;
        std::string texture;
        if (pourcentage < 40) {
            type = ECS::BonusType::DAMAGEBONUS;
            texture = "damage-bonus";
        }
        if (40 < pourcentage && pourcentage < 80) {
            type = ECS::BonusType::SPEEDBONUS;
            texture = "speed-bonus";
        }
        if (80 < pourcentage && pourcentage < 100) {
            type = ECS::BonusType::HEALTHBONUS;
            texture = "health-bonus";
        }
        _componentManager->addComponent(entityBonus, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(84, 84));
        std::shared_ptr<ECS::Hitbox> hitboxBonus = std::dynamic_pointer_cast<ECS::Hitbox>(_componentManager->getComponent(entityBonus, ECS::ComponentType::HITBOX));
        int heightWindow = _sfml->getHeightWindow();
        short posBonus_y = (heightWindow / 100) * (rand() % 100);
        if (posBonus_y < 0)
            posBonus_y = 0;
        else if (posBonus_y > heightWindow)
            posBonus_y = heightWindow - hitboxBonus->getHeight();
        _componentManager->addComponent(entityBonus, ECS::ComponentType::BONUS, std::make_shared<ECS::Bonus>(type));
        _componentManager->addComponent(entityBonus, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(_sfml->getWidthWindow(), posBonus_y));
        _componentManager->addComponent(entityBonus, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_sfml->getTexture(texture), sf::Vector2f(1, 1), sf::IntRect(0, 0, 0, 0), sf::Vector2f(_sfml->getWidthWindow(), posBonus_y)));
        _componentManager->addComponent(entityBonus, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(3));
        _componentManager->addComponent(entityBonus, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(-1, 0));
        _clock->addClockComponent(entityBonus.getId(), ECS::ComponentType::POSITION, 400);
        _clock->addClockComponent(entityBonus.getId(), ECS::ComponentType::BONUS, (nbrBonus * 1000) + 3000);
    }
}

/**
 * It sets the _sfml variable to the sfml variable
 * 
 * @param sfml The sfml object that will be used to draw the bonus.
 */
void ECS::BonusSystem::setSfml(std::shared_ptr<InitSfml> sfml)
{
    _sfml = sfml;
}

/**
 * This function sets the clock for the bonus system.
 * 
 * @param clock The clock that will be used to determine when the bonus should be
 * removed.
 */
void ECS::BonusSystem::setClock(std::shared_ptr<Clock> clock)
{
    _clock = clock;
}

/**
 * If the entity has a bonus component, then it's a valid entity
 * 
 * @param entity The entity to check
 * 
 * @return A boolean value.
 */
bool ECS::BonusSystem::checkIsValidEntity(Entity entity)
{
    auto& components = _componentManager->getComponentList(entity);

    try {
        components.at(ComponentType::BONUS);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}
