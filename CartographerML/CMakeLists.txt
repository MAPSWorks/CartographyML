set(MAPNIKML_SRCS
  EditorView.cpp
  Feature.cpp
  initialise.cpp
  sources/OgrFeaturesSource.cpp
  mapnik/datasource.cpp
  )

add_library(CartographerML SHARED ${MAPNIKML_SRCS})
target_link_libraries(CartographerML MapnikML)
