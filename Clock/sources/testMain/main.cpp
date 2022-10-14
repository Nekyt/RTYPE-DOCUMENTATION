#include "../../include/Clock.hpp"
#include <iostream>
#include <unistd.h>

int main()
{
    Clock clock;
    std::vector<std::pair<size_t, std::vector<ECS::ComponentType>>> enti;

// SET CLOCKS TEST

    clock.addClockComponent(0, ECS::ComponentType::ACCELERATION, 200);
    clock.addClockComponent(0, ECS::ComponentType::POSITION, 200);
    clock.addClockComponent(0, ECS::ComponentType::SPEED, 200);
    clock.addClockComponent(0, ECS::ComponentType::HEALTH, 200);
    clock.addClockComponent(0, ECS::ComponentType::HITBOX, 200);
    clock.addClockComponent(1, ECS::ComponentType::ACCELERATION, 25);
    clock.addClockComponent(2, ECS::ComponentType::ACCELERATION, 180);
    clock.addClockComponent(3, ECS::ComponentType::ACCELERATION, 200);

// SLEEP 2 SECONDS

    sleep(2);

// TEST COMPONENT UPDATE NUMBER FUNCTION

    std::cout << "Entity 0, component Acceleration : " << clock.componentUpdateNumber(0, ECS::ComponentType::ACCELERATION) << " iterations" << std::endl;
    std::cout << "Entity 0, component Position : " << clock.componentUpdateNumber(0, ECS::ComponentType::POSITION) << " iterations" << std::endl;
    std::cout << "Entity 0, component Speed : " << clock.componentUpdateNumber(0, ECS::ComponentType::SPEED) << " iterations" << std::endl;
    std::cout << "Entity 0, component Health : " << clock.componentUpdateNumber(0, ECS::ComponentType::HEALTH) << " iterations" << std::endl;
    std::cout << "Entity 0, component Hitbox : " << clock.componentUpdateNumber(0, ECS::ComponentType::HITBOX) << " iterations" << std::endl;
    std::cout << "Entity 1, component Acceleration : " << clock.componentUpdateNumber(1, ECS::ComponentType::ACCELERATION) << " iterations" << std::endl;
    std::cout << "Entity 2, component Acceleration : " << clock.componentUpdateNumber(2, ECS::ComponentType::ACCELERATION) << " iterations" << std::endl;
    std::cout << "Entity 3, component Acceleration : " << clock.componentUpdateNumber(3, ECS::ComponentType::ACCELERATION) << " iterations" << std::endl;

// SLEEP 2 SECONDS

    sleep(2);
    std::cout << std::endl << std::endl;

// TEST GET ENTITIES FUNCTION

    enti = clock.getEntitiesToUpdate();
    for (size_t i = 0; i < enti.size(); ++i)
        std::cout << "Entity id " << enti[i].first << std::endl;

// SLEEP 2 SECONDS

    sleep(2);
    std::cout << std::endl << std::endl;

// TEST ERASE CLOCK COMPONENT FUNCTION FOR MULTIPLE CLOCK

    clock.eraseClockComponent(0, ECS::ComponentType::ACCELERATION, true);

// TEST ERASE CLOCK FUNCTION

    clock.eraseClock(0);
    enti = clock.getEntitiesToUpdate();
    for (size_t i = 0; i < enti.size(); ++i)
        std::cout << "Entity id " << enti[i].first << std::endl;
    std::cout << std::endl << std::endl;

// TEST ERASE CLOCK COMPONENT FUNCTION FOR SINGLE CLOCK

    clock.eraseClockComponent(2, ECS::ComponentType::ACCELERATION, true);
    enti = clock.getEntitiesToUpdate();
    for (size_t i = 0; i < enti.size(); ++i)
        std::cout << "Entity id " << enti[i].first << std::endl;
}