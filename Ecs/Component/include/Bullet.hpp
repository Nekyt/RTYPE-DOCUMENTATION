/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "IComp.hpp"

namespace ECS {
class Bullet : public IComp {
    public:
    explicit Bullet(bool isFriend) noexcept;
    Bullet(const Bullet& bonus) noexcept = default;
    explicit Bullet(Bullet&&) noexcept = delete;
    ~Bullet() noexcept override = default;

    Bullet& operator=(Bullet&&) const noexcept = delete;
    Bullet& operator=(const Bullet&) const noexcept = delete;

    void setBullet(const bool& isFriend) noexcept;
    [[nodiscard]] bool getBullet() const noexcept;
    protected:
    private:
        bool _isFriend;
};
};

#endif /* !BULLET_HPP_ */
