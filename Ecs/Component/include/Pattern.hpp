#ifndef _PATTERN
#define _PATTERN

#include "IComp.hpp"
#include "Position.hpp"
#include "Speed.hpp"
#include <memory>
#include <vector>

namespace ECS {
enum PatternType {
    STRAIGHT, // MOVING IN A STRAIGHT LINE (default pattern)
    ZIGZAG, // MOVING UP AND DOWN AS WELL AS MOVING FORWARD
    MOVINGDIAMOND, // MOVING IN A DIAMOND SHAPE (Move more in -x than x to keep moving toward players)
    UPANDDOWN /* MOVING STRAIGHT TO THE TOP, THEN MOVING FORWARD FOR A BIT, STOP, MOVING STRAIGHT TO THE BOOTOM,
                 THEN MOVING FORWARD FOR A BIT AND KEEP GOING LIKE THAT */
};

class Pattern : public IComp {
public:
    explicit Pattern(int sizeMapX, int sizeMapY, int sizeEntityX, int sizeEntityY, PatternType type = STRAIGHT) noexcept;
    Pattern(const Pattern& pattern) noexcept = default;
    explicit Pattern(Pattern&&) noexcept = delete;
    ~Pattern() noexcept override = default;

    void changePatternType(PatternType pattern) noexcept;
    std::pair<int, int> getFirstPosition() noexcept;
    std::pair<int, int> getNextPosition(std::shared_ptr<ECS::Speed> speed, std::shared_ptr<ECS::Position> pos) noexcept;

    Pattern& operator=(const Pattern&) const noexcept = delete;
    Pattern& operator=(Pattern&&) const noexcept = delete;

private:
    std::pair<int, int> _sizeMap;
    std::pair<int, int> _sizeEntity;
    std::vector<std::pair<float, float>> _pattern;
    std::vector<std::pair<int, int>> _limit;
    std::pair<int, int> _keepPosition;
    PatternType _type;
    int _moving;
};

};

#endif