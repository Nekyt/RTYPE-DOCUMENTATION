/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <iostream>
#include <utility>

#define MAX_ENTITY 2000

namespace ECS
{
    enum EntityType {PLAYER, ENEMY, PROJECTILES, OBSTACLES, GRAPHICS, BUTTONS};

    class Entity {
        public:
            Entity(std::size_t id, EntityType type);
            ~Entity() = default;

            Entity(Entity const &) = default;
            Entity(Entity &&) noexcept = default;

            Entity &operator=(Entity const &) = default;
            Entity &operator=(Entity &&) noexcept = default;

            std::size_t getId() const;
            EntityType getType() const;
        private:
            std::size_t _id;
            EntityType _type;
    };
    inline bool operator==(const ECS::Entity &cur, const ECS::Entity &oth) {return cur.getId() == oth.getId();}
    inline bool operator>(const ECS::Entity &cur, const ECS::Entity &oth) {return cur.getId() > oth.getId();}
    inline bool operator<(const ECS::Entity &cur, const ECS::Entity &oth) {return cur.getId() < oth.getId();}
} // namespace ECS


#endif /* !ENTITY_HPP_ */