namespace nnct::components {

template<typename T>
SpscQueue<T>::SpscQueue(std::size_t size_exp) : items_(std::vector<T>(1 << size_exp)), INDEX_MASK_((1 << size_exp) - 1) {}

template<typename T>
bool SpscQueue<T>::enqueue(T item) {
    auto head = head_.load(std::memory_order_acquire);
    auto tail = tail_.load(std::memory_order_acquire);

    if (head - tail >= items_.size()) return false;

    items_[head & INDEX_MASK_] = std::move(item);

    head_.store(head + 1, std::memory_order_release);
    return true;
}

template<typename T>
bool SpscQueue<T>::dequeue() {
    auto head = head_.load(std::memory_order_acquire);
    auto tail = tail_.load(std::memory_order_acquire);

    if (head - tail == 0) return false;

    latest_ = items_[tail & INDEX_MASK_];

    tail_.store(tail + 1, std::memory_order_release);
    return true;
}

template<typename T>
const T& SpscQueue<T>::latest() const {
    return latest_;
}

}
