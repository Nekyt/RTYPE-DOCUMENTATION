#include "../include/id.hpp"

ECS::ID::ID(int id) noexcept : _id(id) {}
ECS::ID::ID(const ID& id) noexcept : _id(id.getID()){}

int ECS::ID::getID() const noexcept {return _id;}

void ECS::ID::setID(int id) noexcept {_id = id;}