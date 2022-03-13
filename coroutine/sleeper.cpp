#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

struct Task {
    struct promise_type {
        static constexpr std::suspend_never initial_suspend() noexcept{return {};}
        static constexpr std::suspend_never final_suspend() noexcept{return {};}
        static void unhandled_exception() {throw;}
        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
    };

    explicit Task(std::coroutine_handle<promise_type> h)
        :Handle(h){}    

    std::coroutine_handle<promise_type> Handle;
};

struct Sleeper {
    constexpr bool await_ready() const noexcept { return false;}
    void await_suspend(std::coroutine_handle<> h) const {
        std::jthread{ [h, l=length] {
            std::this_thread::sleep_for(l);
            h.resume();
        } }.detach();
    }
    constexpr void await_resume() const noexcept{}
    const std::chrono::milliseconds length;
};

Task myCoroutine() {
    auto before = std::chrono::steady_clock::now();
    co_await Sleeper{2s};
    auto after = std::chrono::steady_clock::now();
    std::cout << "Slept for " << std::chrono::duration_cast<std::chrono::milliseconds>(after-before).count() << " ms" << std::endl;
}

int main()
{    
    myCoroutine();
    std::cout << "end of main" << std::endl;
    std::this_thread::sleep_for(5s);
}