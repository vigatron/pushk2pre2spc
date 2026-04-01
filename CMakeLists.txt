cmake_minimum_required(VERSION 3.16)
project(MyQtProject LANGUAGES CXX)

set(PRJNAME pushk2pre2spc)

# Опции компиляции
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Источники
file(GLOB_RECURSE source_list
    src/*.cpp
    src/*.hpp
	src/mods/*
	src/misc/*
)

# Исполняемый файл
add_executable(${PRJNAME} ${source_list})

# Заголовочные файлы
target_include_directories(${PRJNAME}
    PRIVATE
        src
		src/mods
)

# Установка бинарника
install(TARGETS ${PRJNAME}
    RUNTIME DESTINATION bin
)


# cmake_minimum_required(VERSION 3.5)
# project(MyQtProject CXX)

# set(PRJNAME pushk2pre2spc)


# # set(CMAKE_BUILD_TYPE "Release")
# # set(CMAKE_BUILD_TYPE "MinSizeRel")


# include_directories(. src mods misc)

# file( GLOB_RECURSE source_list_mods 
#     src/*.cpp  src/*.hpp
#     mods/*.cpp mods/*.hpp
#     misc/*.cpp misc/*.hpp )

# add_executable(${PRJNAME} src/main.cpp ${source_list_mods} )
# add_custom_command(TARGET ${PRJNAME} POST_BUILD COMMAND cp "${PROJECT_BINARY_DIR}/${PRJNAME}"     "$ENV{HOME}/bin/${PRJNAME}"        )
# add_custom_command(TARGET ${PRJNAME} POST_BUILD COMMAND cp -r "${CMAKE_SOURCE_DIR}/examples"	 "/tmp/ramdisk/${PRJNAME}" )
