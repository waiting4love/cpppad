#include <iostream>
#include <coroutine>

template<typename T> struct generator final {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    //我们的 int_generator 类就扮演了“钥匙”的角色，它只保存当前协程的句柄
    //而真正存储 co_yield 的返回值的“箱子”其实是这个 promise_type
    struct promise_type final {
        // 作为协程的承诺类型，promise_type 需要具备 get_return_object 函数；
        // 要对我们的 int_generator::promise_type 使用 co_yield 的话，
        // promise_type 需要具备 yield_value 函数。
        // get_return_object 函数即是返回当前 promise_type 的这个“箱子”所对应的 int_generator “钥匙”。
        generator get_return_object() {
            return generator{ handle_type::from_promise(*this) };
        }

        // co_yield x; 相当于 co_await promise.yield_value(x);
        // 那么这里显然 yield_value 函数要接受一个 int 作为参数。
        // 另一方面 co_await 运算符如果直接在 cppreference 上面看可以看到很长的一段说明，
        // 关于如何获得可等待体和等待器对象之类的，并且它们还跟当前协程需不需要挂起有关。
        // 反过来来看我们的应用场景，每次 co_yield 返回值之后我们都希望控制转回调用方，也就是这里 co_await 的东西要总让协程挂起。
        // 这里标准库为我们提供了这样的一个基础类，那就是 suspend_always，名字可以说是非常直观了。
        std::suspend_always yield_value(const T value) {
            value_ = value;
            return {};
        }

        T get_value() const {
            return value_;
        }
        
        // C++ 的协程在刚被调用和结束整个协程体的时候可以选择是否要挂起，
        // 控制这个行为的函数就是 initial_suspend 和 final_suspend 了。
        // 这里我们要实现的类作为一个生成器，我们希望刚调用的时候我们只是获得一个协程的关联对象之后再选择何时开始生成值，
        // 所以这里面 initial_suspend 也需要返回 suspend_always；类似的理由 final_suspend 也是如此。
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        // “return_value”或“return_void”。这两个函数与在协程中使用 co_return 相关，
        // 因为这里并不需要在协程结束时返回任何值所以这里需要实现 return_void。
        void return_void() {}


        // unhandled_exception 函数，用于在协程内部出现异常时选择异常的处理方案。
        void unhandled_exception() { throw; }

    private:
        // 前面还说过返回值都是存储在承诺对象里面的，那这里就给承诺对象添加一个成员变量记录这个返回值，
        // 并且增加一个函数来让外面可以获取到这个值：
        T value_;

    };

    //下一步就是给我们的 int_generator 类加上范围 for 循环的支持了
    class sentinel final {};
    class iterator final {
    private:
        handle_type handle_;
    public:    
        explicit iterator(const handle_type handle)
            :handle_(handle)
        {
            handle_.resume();   
        }

        iterator& operator++() {
            handle_.resume();
            return *this;
        }

        T operator*() const { return handle_.promise().get_value();}

        friend bool operator==(const iterator it, sentinel) {
            return it.handle_.done();
        }
    };

    explicit generator(const handle_type handle)
        :handle_(handle) {}
    ~generator() { if(handle_) handle_.destroy(); }

    iterator begin() {
        return iterator{handle_};
    }
    sentinel end() {
        return {};
    }
private:
    handle_type handle_;
};

generator<int> f(int max) {
    int x = 1, y = 0;
    while (y < max)
    {
        const int next = x + y;
        x = y;
        y = next;
        co_yield next;
    }
}

int main() {
    auto g = f(100);
    for(auto i : g)
    {
        std::cout << i << std::endl;
    }
}