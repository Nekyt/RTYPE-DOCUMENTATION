#include <memory.h>

//valgrind --tool=cachegrind ./exec

namespace ECS {
    class IComp {
        public:
            virtual ~IComp() noexcept = default;
    };
};
