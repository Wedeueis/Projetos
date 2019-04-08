project(bDetect)

set(${PROJECT_NAME}_headers ../../inc/bDetect.hpp)
set(${PROJECT_NAME}_sources bDetect.cpp main.cpp)

add_executable( main.exe ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources} )
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources} )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${JSONCPP_LIBRARIES} )
target_link_libraries(main.exe ${OpenCV_LIBS} ${JSONCPP_LIBRARIES} )	

install( TARGETS main.exe ${PROJECT_NAME}
	 RUNTIME DESTINATION bin
	 LIBRARY DESTINATION lib
	 ARCHIVE DESTINATION lib)
