set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set( BIGINT_LIB 
    Base/BigInteger.cpp 
    Randoms/PcgRandomMinimal.cpp 
    Security/Random.cpp Security/SecureRandom.cpp 
    Rng/RandomNumberGenerator.cpp
)

add_executable(bigint main.cpp ${BIGINT_LIB})
