#include <iostream>
#include <coroutine>

struct ReturnObject{
    struct promise_type{
        std::suspend_never initial_suspend() {
            std::cout << "promise_type::initial_suspend()" << std::endl;
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            std::cout << "promise_type::final_suspend()" << std::endl;
            return {};
        }
        void unhandled_exception() {
            std::cout << "promise_type::unhandled_exception()" << std::endl;
        }
        ReturnObject get_return_object() {
            std::cout << "promise_type::get_return_object()" << std::endl;
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }
    };

    ReturnObject(std::coroutine_handle<> handle)
        :_handle(handle)
    {
        std::cout << "ReturnObject::ReturnObject()" << std::endl;
    }

    ~ReturnObject()
    {
        std::cout << "ReturnObject::~ReturnObject()" << std::endl;
        _handle.destroy();
    }

    void stepIt()
    {
        _handle.resume();
    }
private:
    std::coroutine_handle<> _handle;
};

ReturnObject foo() {
    std::cout << "1. from coroutine" << std::endl;
    co_await std::suspend_never();
    std::cout << "2. from coroutine" << std::endl;
    co_await std::suspend_always();
    std::cout << "3. from coroutine" << std::endl;
}

int main() {
    std::cout << "1. main" << std::endl;
    auto coro = foo();
    std::cout << "2. main" << std::endl;
    coro.stepIt();
    std::cout << "3. main" << std::endl;
}