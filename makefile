TARGET = allTests
CXX = g++
CXXFLAGS = -Wall -Wpedantic -std=c++20
LIB_DIR = -Lcpputest/cpputest_build/src/CppUTest -Lcpputest/cpputest_build/src/CppUTestExt
LIBS = -lCppUTest -lCppUTestExt
SOURCES = tests/allTests.cpp core/src/m28w160ect.c tests/m28w160ectTest.cpp tests/mocks/mock_m28w160ectTest.c
INCLUDE_DIR = -Icpputest/include -Icpputest/include/CppUTestExt -Itests/mocks -Icore/inc

all:
	$(CXX) $(SOURCES) $(CXXFLAGS) $(INCLUDE_DIR) $(LIB_DIR) $(LIBS) -o $(TARGET)
	./$(TARGET).exe -v

static:
	"C:/Program Files/Cppcheck/cppcheck.exe" --addon=misra --enable=all core/src/m28w160ect.c