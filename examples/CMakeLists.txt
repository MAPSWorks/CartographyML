# Look for optional Qt5Widgets (to get the proper style), and also non-crashing behavior with Qt5.6 on linux
find_package(Qt5Widgets)

if(Qt5Widgets_FOUND)
set(QT5_WIDGET_LIBRARIES Qt5::Widgets)
endif()

# Generate config.h
set(HAVE_QT5WIDGETS Qt5Widgets_FOUND)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_subdirectory(shape_viewer)
add_subdirectory(world_viewer)
add_subdirectory(shape_editor)
add_subdirectory(terrain_editor)
