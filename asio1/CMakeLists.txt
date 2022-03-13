set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-fcoroutines>")

set(BOOST_ROOT C:/opt/boost)
set(Boost_NO_SYSTEM_PATHS ON)
find_package(Boost REQUIRED COMPONENTS regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
    MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}")

    add_executable(asio1 main.cpp)
    #target_link_libraries (asio1 ${Boost_LIBRARIES})
    #target_include_directories(${Boost_INCLUDE_DIRS})
    #target_link_libraries (asio1 Boost::regex)
    target_link_libraries(asio1 PUBLIC ${Boost_LIBRARIES} wsock32 ws2_32)
endif()
