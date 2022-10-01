#include "IComp.hpp"

namespace ECS {

class Size : public IComp {
    public:
        explicit Size(unsigned short x, unsigned short y) noexcept;
        Size(const Size& size) noexcept;
        explicit Size(Size&&) noexcept = delete;
        ~Size() noexcept override = default;

        Size &operator=(const Size&) const noexcept = delete;
        Size &operator=(Size&&) const noexcept = delete;

        [[nodiscard]] unsigned short getSize_x() const noexcept;
        [[nodiscard]] unsigned short getSize_y() const noexcept;
        void setSize_x(unsigned short x) noexcept;
        void setSize_y(unsigned short y) noexcept;

    private:
        unsigned short _x;
        unsigned short _y;
};
};