#ifndef _SOUND
#define _SOUND

#include "IComp.hpp"

namespace ECS {

    class Sound : public IComp {
        public:
            explicit Sound() noexcept = default;
            Sound(const Sound& bonus) noexcept = default;
            explicit Sound(Sound&&) noexcept = delete;
            ~Sound() noexcept override = default;

            Sound &operator=(const Sound&) const noexcept = delete;
            Sound &operator=(Sound&&) const noexcept = delete;
    };

};

#endif