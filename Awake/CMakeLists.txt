add_executable(awake WIN32 main.cpp)
Set_Target_Properties(awake PROPERTIES LINK_FLAGS_RELEASE "/ENTRY:main /align:16 /merge:.data=.text /merge:.rdata=.text /manifest:no")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
target_compile_definitions(awake PRIVATE UNICODE _UNICODE)