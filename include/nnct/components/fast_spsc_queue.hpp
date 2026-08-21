#pragma once

#include <cstddef>
#include <atomic>
#include <vector>

namespace nnct::components {
    
template<typename T>
class FastSpscQueue {
    public:
        explicit FastSpscQueue(std::size_t size_exp);
        ~FastSpscQueue() = default;
        
        bool enqueue(T item);
        bool dequeue();
        
        const T& latest() const;
        
    private:     
        const std::size_t INDEX_MASK_;
        
        std::vector<T> items_;
        
        T latest_;

        alignas(64) std::atomic<std::size_t> head_ { 0 };
        volatile char pad[64];
        alignas(64) std::atomic<std::size_t> tail_ { 0 };
};

}

#include <nnct/components/fast_spsc_queue.ipp>
