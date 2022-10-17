#include <iostream>
#include "Testy1/sayings.hpp"

int main()
{
    Sayings say;

    std::cout << "Everything below is printed from a submodule:" << std::endl;
    say.say_hello();
    say.say_team();
    say.say_update();
    say.say_goodbye();
    say.say_goodbye();
}
