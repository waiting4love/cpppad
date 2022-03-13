#include <iostream>
#include <clocale>
#include <cstdlib>
#include <Windows.h>
// mingw运行有问题
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, ".utf8");
    std::locale locale{".utf8"};
    std::wcout.imbue(locale);
    auto mbstr = reinterpret_cast<const char *>(u8"zß水🍌");
    wchar_t wstr[10]={0};
    std::mbstowcs(wstr, mbstr, 5);
    std::wcout << "wide string: " << wstr << '\n';
    return 0;
}