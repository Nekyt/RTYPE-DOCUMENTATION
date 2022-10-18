#include "Clock.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>

/**
 * It adds a component to the clock
 * 
 * @param entity The entity to which the component is attached.
 * @param type The type of the component you want to add to the clock.
 * @param updateTime The time in milliseconds between each update.
 */
void Clock::addClockComponent(size_t entity, ECS::ComponentType type, int updateTime)
{
    std::map<ECS::ComponentType, int> mapC;
    std::map<ECS::ComponentType, std::clock_t> mapT;
    std::clock_t time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    mapT.insert(std::pair<ECS::ComponentType, std::clock_t>(type, time));
    mapC.insert(std::pair<ECS::ComponentType, int>(type, updateTime));
    if (_timer.find(entity) == _timer.end()) {
        _entities.push_back(entity);
        _timer.insert(std::pair<size_t, std::map<ECS::ComponentType, int>>(entity, mapC));
        _previousIte.insert(std::pair<size_t, std::map<ECS::ComponentType, std::clock_t>>(entity, mapT));
        _timersList.insert(std::make_pair(entity, std::vector<ECS::ComponentType> { type }));
    } else {
        _timersList[entity].push_back(type);
        _timer[entity].insert(std::make_pair(type, updateTime));
        _previousIte[entity].insert(std::make_pair(type, time));
    }
}

/**
 * It returns a vector of pairs of entity IDs and component types that need to be
 * updated
 * 
 * @return A vector of pairs of size_t and vector of ComponentType.
 */
std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> Clock::getEntitiesToUpdate()
{
    std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> toUpdate;
    std::clock_t time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    for (size_t i = 0; i < _entities.size(); ++i) {
        for (size_t g = 0; g < _timersList[_entities[i]].size(); ++g) {
            if (_previousIte[_entities[i]][_timersList[_entities[i]][g]] + _timer[_entities[i]][_timersList[_entities[i]][g]] < time) {
                toUpdate.push_back(std::make_pair(_entities[i], _timersList[i]));
                break;
            }
        }
    }
    return toUpdate;
}

/**
 * "If the time since the last update is greater than the timer, then update the
 * entity and return the number of times the entity was updated."
 * 
 * The function is a bit more complicated than that, but that's the gist of it
 * 
 * @param entity The entity to check for updates.
 * @param type The type of the component you want to update.
 * 
 * @return The number of times the component has been updated.
 */
int Clock::componentUpdateNumber(size_t entity, ECS::ComponentType type)
{
    int updateOccurance = 0;
    std::clock_t time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    for (; _previousIte[entity][type] + _timer[entity][type] < time; ++updateOccurance, _previousIte[entity][type] += _timer[entity][type])
        ;
    return updateOccurance;
}

/**
 * It removes a component from the clock
 * 
 * @param entity The entity ID from where the component will be removed.
 * @param type The type of the component to be removed.
 * @param debug if true, the function will print some information about the removal
 * of the component.
 * 
 * @return A reference to the component of the entity.
 */
void Clock::eraseClockComponent(size_t entity, ECS::ComponentType type, bool debug)
{
    if (_timer[entity].size() == 1) {
        this->eraseClock(entity);
        return;
    }
    if (debug == true) {
        std::cout << std::endl
                  << "<<<<<<<<<<<< DEBUG : eraseClockComponent BEGIN <<<<<<<<<<<<" << std::endl;
        std::cout << "Entity ID from where the component will be removed : " << entity << std::endl
                  << "Number of components before removal : " << _timersList[entity].size() << std::endl;
        std::cout << std::endl
                  << "Removing component..." << std::endl
                  << std::endl;
    }
    _timer[entity].erase(type);
    _previousIte[entity].erase(type);
    _timersList[entity].erase(std::find(_timersList[entity].begin(), _timersList[entity].end(), type));
    if (debug == true) {
        std::cout << "Entity ID from where the component is supposed to be removed : " << entity << std::endl
                  << "Number of components after removal : " << _timersList[entity].size() << std::endl;
        std::cout << "<<<<<<<<<<<< DEBUG : eraseClockComponent END   <<<<<<<<<<<<" << std::endl
                  << std::endl;
    }
}

/**
 * It erases the clock of the entity passed in parameter
 * 
 * @param entity The entity you want to erase the clock of.
 */
void Clock::eraseClock(size_t entity)
{
    _timer[entity].erase(_timer[entity].begin(), _timer[entity].end());
    _timer.erase(entity);
    _previousIte[entity].erase(_previousIte[entity].begin(), _previousIte[entity].end());
    _previousIte.erase(entity);
    _timersList[entity].erase(_timersList[entity].begin(), _timersList[entity].end());
    _timersList.erase(entity);
    _entities.erase(std::find(_entities.begin(), _entities.end(), entity));
}