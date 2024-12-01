cmake_minimum_required(VERSION 3.10)

project(AdventOfCode-2022)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${PROJECT_SOURCE_DIR})

FOREACH(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
ENDFOREACH()