set(SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp)

add_library(b2d_core SHARED ${SOURCE})
target_link_libraries(b2d_core -lsfml-graphics)