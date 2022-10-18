#include "../include/Pattern.hpp"
#include <random>
#include <iostream>

/**
 * It initializes the pattern of the enemy.
 *
 * @param sizeMapX the width of the map
 * @param sizeMapY the height of the map
 * @param sizeEntityX the width of the entity
 * @param sizeEntityY The height of the entity
 * @param type The type of pattern the enemy will follow.
 */
ECS::Pattern::Pattern(int sizeMapX, int sizeMapY, int sizeEntityX, int sizeEntityY, PatternType type) noexcept
    : _sizeMap(std::make_pair(sizeMapX, sizeMapY))
    , _sizeEntity(std::make_pair(sizeEntityX, sizeEntityY))
    , _type(type)
    , _moving(0)
{
    if (type == PatternType::STRAIGHT)
        _pattern.push_back(std::make_pair(-1, 0));
    else if (type == PatternType::ZIGZAG) {
        _pattern.push_back(std::make_pair(-1, 1));
        _pattern.push_back(std::make_pair(-1, -1));
        _limit.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(-1, 0));
    } else if (type == PatternType::UPANDDOWN) {
        _pattern.push_back(std::make_pair(0, -1));
        _pattern.push_back(std::make_pair(-1, 0));
        _pattern.push_back(std::make_pair(0, 1));
        _pattern.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(sizeMapX / 10, -1));
        _limit.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(sizeMapX / 10, -1));
    } else {
        _pattern.push_back(std::make_pair(-1, -1));
        _pattern.push_back(std::make_pair(-1, 1));
        _pattern.push_back(std::make_pair(1, 1));
        _pattern.push_back(std::make_pair(0.5, -1));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
    }
}

/**
 * It changes the pattern of the enemy
 *
 * @param type The type of pattern to use.
 */
void ECS::Pattern::changePatternType(PatternType type) noexcept
{
    _pattern.clear();
    _limit.clear();
    _moving = 0;
    _type = type;
    if (type == PatternType::STRAIGHT)
        _pattern.push_back(std::make_pair(-1, 0));
    else if (type == PatternType::ZIGZAG) {
        _pattern.push_back(std::make_pair(-1, 1));
        _pattern.push_back(std::make_pair(-1, -1));
        _limit.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(-1, 0));
    } else if (type == PatternType::UPANDDOWN) {
        _pattern.push_back(std::make_pair(0, -1));
        _pattern.push_back(std::make_pair(-1, 0));
        _pattern.push_back(std::make_pair(0, 1));
        _pattern.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(_sizeMap.first / 10, -1));
        _limit.push_back(std::make_pair(-1, 0));
        _limit.push_back(std::make_pair(_sizeMap.first / 10, -1));
    } else {
        _pattern.push_back(std::make_pair(-1, -1));
        _pattern.push_back(std::make_pair(-1, 1));
        _pattern.push_back(std::make_pair(1, 1));
        _pattern.push_back(std::make_pair(0.5, -1));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
        _limit.push_back(std::make_pair(-1, _sizeMap.second / 4));
    }
}

/**
 * It returns the first position of the pattern
 *
 * @return The first position of the pattern.
 */
std::pair<int, int> ECS::Pattern::getFirstPosition() noexcept
{
    _moving = 0;
    if (_type == PatternType::MOVINGDIAMOND)
        _keepPosition = std::make_pair(_sizeMap.first + 10, (rand() + _sizeEntity.second + _sizeMap.second / 3) % (_sizeMap.second - (_sizeMap.second / 3)));
    else
        _keepPosition = std::make_pair(_sizeMap.first + 10, (rand() + _sizeEntity.second) % _sizeMap.second);
    return _keepPosition;
}

/**
 * It returns the next position of the entity according to the pattern
 *
 * @param speed the speed of the entity
 * @param pos the position of the entity
 *
 * @return A pair of int
 */
std::pair<int, int> ECS::Pattern::getNextPosition(std::shared_ptr<ECS::Speed> speed, std::shared_ptr<ECS::Position> pos) noexcept
{
    std::pair<int, int> nextPos = std::make_pair(pos->getPosition_x() + (speed->getSpeed() * _pattern[_moving].first), pos->getPosition_y() + (speed->getSpeed() * _pattern[_moving].second));

    if (_limit.empty()) {
        return std::make_pair(pos->getPosition_x() + (speed->getSpeed() * _pattern[0].first), pos->getPosition_y());
    }
    if ((_limit[_moving].first == -1 || _limit[_moving].first > abs(nextPos.first - _keepPosition.first)) && ((_limit[_moving].second == 0 && nextPos.second > 0 && nextPos.second < _sizeMap.second - _sizeEntity.second) || (_limit[_moving].second == -1 || _limit[_moving].second > abs(nextPos.second - _keepPosition.second))))
        return nextPos;
    ++_moving;
    if ((_limit[_moving].first != -1 && _limit[_moving].first > abs(nextPos.first - _keepPosition.first)))
        _keepPosition.first = pos->getPosition_x();
    else
        _keepPosition.second = pos->getPosition_y();
    if (_moving >= _pattern.size())
        _moving = 0;
    return this->getNextPosition(speed, pos);
}
