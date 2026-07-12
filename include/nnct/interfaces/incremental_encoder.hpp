#pragma once

#include <cstdint>

namespace nnct::interfaces {

class IncrementalEncoder {
    public:
        virtual int32_t getCount()              = 0;
        virtual void    setCount(int32_t count) = 0;
        inline void     clear() { setCount(0); };
};

} // namespace nnct::interfaces
