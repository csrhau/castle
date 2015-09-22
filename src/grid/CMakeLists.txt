file(GLOB Grid_SOURCES *.cc)
file(GLOB Grid_HEADERS *.h)

add_library(grid STATIC ${Grid_SOURCES} ${Grid_HEADERS})
