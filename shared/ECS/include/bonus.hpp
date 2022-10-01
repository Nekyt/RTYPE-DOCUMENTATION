#ifndef _BONUS
#define _BONUS

#include "IComp.hpp"

namespace ECS {

    class Bonus : public IComp {
        public:
            explicit Bonus() noexcept = default;
            Bonus(const Bonus& bonus) noexcept = default;
            explicit Bonus(Bonus&&) noexcept = delete;
            ~Bonus() noexcept override = default;

            Bonus &operator=(const Bonus&) const noexcept = delete;
            Bonus &operator=(Bonus&&) const noexcept = delete;
    };

};

#endif