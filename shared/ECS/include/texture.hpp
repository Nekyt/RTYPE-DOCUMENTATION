#include "IComp.hpp"

namespace ECS {

    class Texture : public IComp {
        public:
            explicit Texture() noexcept = default;
            Texture(const Texture& bonus) noexcept = default;
            explicit Texture(Texture&&) noexcept = delete;
            ~Texture() noexcept override = default;

            Texture &operator=(const Texture&) const noexcept = delete;
            Texture &operator=(Texture&&) const noexcept = delete;
    };

};