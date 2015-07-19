include(GResource)

set(SOURCE_FILES
    main.cc
    ui.cc
    ltsource.cc
    TorrentListWidget.cc
    TorrentListRow.cc
    util.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

include(FindPkgConfig)
pkg_search_module(gtkmm REQUIRED gtkmm-3.0)
pkg_search_module(libtorrent REQUIRED libtorrent-rasterbar)

glib_compile_resources(UI_FILES SOURCE ui/resources.xml)

add_definitions(${gtkmm_CFLAGS} ${libtorrent_CFLAGS})
link_libraries(${gtkmm_LIBRARIES} ${libtorrent_LIBRARIES})
link_directories(${gtkmm_LIBRARY_DIRS} ${libtorrent_LIBRARY_DIRS})
add_executable(gtorrent ${SOURCE_FILES} ${UI_FILES})
