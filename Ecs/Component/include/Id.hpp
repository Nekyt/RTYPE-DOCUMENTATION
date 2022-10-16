#ifndef _ID
#define _ID

#include "IComp.hpp"

namespace ECS {

class ID : public IComp {
public:
    explicit ID(int id) noexcept;
    ID(const ID& id)
    noexcept;
    explicit ID(ID&&) noexcept = delete;
    ~ID() noexcept override = default;

    ID& operator=(const ID&) const noexcept = delete;
    ID& operator=(ID&&) const noexcept = delete;

    [[nodiscard]] int getID() const noexcept;
    void setID(int id) noexcept;

private:
    int _id;
};

};

#endif