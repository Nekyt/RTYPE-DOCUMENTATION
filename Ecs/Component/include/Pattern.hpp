#ifndef _PATTERN
#define _PATTERN

#include "IComp.hpp"

namespace ECS {

    class Pattern : public IComp {
        public:
            explicit Pattern() noexcept = default;
            Pattern(const Pattern& bonus) noexcept = default;
            explicit Pattern(Pattern&&) noexcept = delete;
            ~Pattern() noexcept override = default;

            Pattern &operator=(const Pattern&) const noexcept = delete;
            Pattern &operator=(Pattern&&) const noexcept = delete;
    };

};

#endif