#ifndef _ICOMP
#define _ICOMP

//valgrind --tool=cachegrind ./exec

namespace ECS {
    class IComp {
        public:
            virtual ~IComp() noexcept = default;
    };
};

#endif