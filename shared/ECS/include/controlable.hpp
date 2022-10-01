#include "IComp.hpp"

namespace ECS {

class Controlable : public IComp {
    public:
        explicit Controlable(bool con) noexcept;
        Controlable(const Controlable& con) noexcept;
        explicit Controlable(Controlable&&) noexcept = delete;
        ~Controlable() noexcept override = default;

        Controlable &operator=(const Controlable&) const noexcept = delete;
        Controlable &operator=(Controlable&&) const noexcept = delete;

        [[nodiscard]] bool getControlable() const noexcept;
        void changeControlable() noexcept;
    private:
        bool _controlable;
};

};