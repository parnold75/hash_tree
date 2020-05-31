cmake_minimum_required(VERSION 3.16)

set(This hash_tree_test)


FIND_PACKAGE(GTest REQUIRED)

FIND_LIBRARY(cryptopp crypto++ /usr/lib) ## location of libcryptopp.so or libcryptopp.a


include_directories(
	"../"
	#"/usr/include"
	#"C:/Daten/github/cryptopp"
)

set(Sources
    test.cpp
)

add_executable(${This} 
	${Sources}
)

target_link_libraries(${This} PUBLIC
	${GTEST_LIBRARIES}
    hash_tree_lib
    cryptopp
    pthread
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
