 cmake_minimum_required(VERSION 3.13)
 project(datemanager)
 include_directories(include)#
 set(CMAKE_C_STANDARD 11)
 add_subdirectory(src)
 set(CMAKE_INSTALL_BINDIR "${CMAKE_SOURCE_DIR}/bin")
 set(CMAKE_INSTALL_LIBDIR "${CMAKE_SOURCE_DIR}/lib")
 install(TARGETS datemanager MyLibrary
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

