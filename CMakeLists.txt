cmake_minimum_required(VERSION 2.8.4)
project(Echecs)


set(SOURCE_FILES
    src/deplacement.c
    src/deplacement.h
    src/fichier.c
    src/fichier.h
    src/grille.c
    src/grille.h
    src/hash.c
    src/hash.h
    src/jeu.c
    src/jeu.h
    src/main.c
    src/option.c
    src/option.h
    src/structure.h
    src/ui.c
    src/ui.h
    src/cef/cef_gtk.h
    src/cef/cef_gtk.c
    src/cef/cef_base.h
    src/cef/cef_base.c
    src/cef/cef_client.c
    src/cef/cef_client.h
    src/cef/cef_app.c
    src/cef/cef_app.h
    src/piece.c
    src/piece.h
    src/ia.c
    src/ia.h)




add_definitions("-g -Wall -pedantic")
INCLUDE(FindPkgConfig)
add_executable(Echecs ${SOURCE_FILES})
pkg_check_modules(GLIB REQUIRED gtk+-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(SYSTEM "lib/fann")
include_directories(SYSTEM "lib")
target_link_libraries(Echecs ${GLIB_LIBRARIES} "cef" "fann")

