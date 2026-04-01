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

# python3 -m unittest discover -s tests
