#include <iostream>

///////////////////////////////////////////////
void print1()
{
    std::cout << "\n";
}

template<typename F, typename... Args>
void print1(F first, Args... args)
{
    std::cout << first << ' ';
    print1(args...);
}

///////////////////////////////////////////////
template<typename... Args>
void print2(Args... args)
{
    std::initializer_list<int>{
        ([](const auto& t){std::cout << t << ' ';}(std::forward<Args>(args)),0)...
    };
    std::cout << std::endl;
}

// fold expression
template<typename... Args>
void print3(Args... args)
{
    // ( pack op ... )
    // Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
    ((std::cout << std::forward<Args>(args) << ' '),...);
    std::cout << std::endl;
}

template<typename... Args>
void print4(Args... args)
{
    // ( ... op pack )
    // Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
    (std::cout << ... << std::forward<Args>(args));
    std::cout << std::endl;
}

template<typename ...Args>
void print5(Args... args)
{
    auto space = [](const auto& arg) {
        std::cout << arg << ' ';
    };
    (...,space(args));
    std::cout << std::endl;
}

template<typename ...Args>
auto sum(Args... args)
{
    return (0 + ... + args);
}

template <typename... Args>
void print_even(Args... args)
{
    auto is_even = [](int arg) { return arg % 2 == 0; };
    ((is_even(args) && (std::cout << args << ' ')), ...);
    std::cout << std::endl;
}

/////////////////////////////////////
template<typename... Bases>
struct Foo: Bases...
{
    static void print() {
        (...,Bases::print());
    }
};

struct A {
    static void print() { std::cout << "A::print()" << std::endl;}
};

struct B {
    static void print() { std::cout << "B::print()" << std::endl;}
};

struct C {
    static void print() { std::cout << "C::print()" << std::endl;}
};

int main()
{
    print1("a", 1, true);
    print2("a", 1, true);
    print3("a", 1, true);
    print4("a", 1, true);
    print5("a", 1, sum("hello", std::string{}, "world"));
    print_even(1,2,3,4,5,6,7);
    Foo<A,B,C>::print();
}