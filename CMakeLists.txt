cmake_minimum_required(VERSION 3.16)
project(Swc3Chess VERSION 1.0.0 LANGUAGES C CXX)

# Sources
set(PROJECT_SOURCES
    src/chess/chessboard.h
    src/chess/chess_piece.h
        src/chess/standard_chess.cpp
        src/chess/standard_chess.h
        src/chess/chess_piece.cpp

        # Add your sources here!
)
set(PROJECT_RESOURCES
    src/chess/resources/bP.svg
    src/chess/resources/bR.svg
    src/chess/resources/bN.svg
    src/chess/resources/bB.svg
    src/chess/resources/bQ.svg
    src/chess/resources/bK.svg
    src/chess/resources/wP.svg
    src/chess/resources/wR.svg
    src/chess/resources/wN.svg
    src/chess/resources/wB.svg
    src/chess/resources/wQ.svg
    src/chess/resources/wK.svg

    # Add your pieces here!
)

# automatic Qt-Meta-Tools
set(CMAKE_AUTOMOC ON)

# configure C17
set(CMAKE_C_STANDARD 17)          # request C17
set(CMAKE_C_STANDARD_REQUIRED ON) # enforce requested standard
set(CMAKE_C_EXTENSIONS OFF)       # disable compiler specific extensions

# configure C++23
set(CMAKE_CXX_STANDARD 23)          # request C++23
set(CMAKE_CXX_STANDARD_REQUIRED ON) # enforce requested standard
set(CMAKE_CXX_EXTENSIONS OFF)       # disable compiler specific extensions

# --- Common compiler warning flags ---
set(COMMON_WARNINGS
    -Wall          # Enable all basic warnings; the standard baseline for most compilers.
    -Wextra        # Enable extra warnings not included in -Wall (often very helpful).
    -Wpedantic     # Enforce strict ISO C/C++ standard compliance; warn on non-standard extensions.
    -Wconversion   # Warn about implicit type conversions that may alter a value (e.g. int -> float, signed -> unsigned).
    -Wshadow       # Warn when a local variable or parameter hides (shadows) another variable with the same name.
    -Wvla          # Warn when Variable Length Arrays (VLAs) are used; they are non-standard in C++ and discouraged in C.
    -Werror=vla    # Treat any VLA warning as an error (i.e., forbid VLAs completely for portability and safety).
)

# Find Qt (Widgets and SVG is all we need)
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Svg)
find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)

set(GUI_SOURCES
    src/chess/private/ChessboardWidget.h
    src/chess/private/ChessboardWidget.cpp
    src/chess/private/MainWindow.h
    src/chess/private/MainWindow.cpp
        src/chess/main.cpp
        src/chess/main.cpp
        src/chess/main.cpp
        src/chess/pieces/king.cpp
        src/chess/pieces/king.h
        src/chess/pieces/bishop.cpp
        src/chess/pieces/bishop.h
        src/chess/pieces/queen.cpp
        src/chess/pieces/queen.h
        src/chess/pieces/knight.cpp
        src/chess/pieces/knight.h
        src/chess/pieces/rook.cpp
        src/chess/pieces/rook.h
        src/chess/chess_piece.cpp
        src/chess/pieces/pawn.cpp
        src/chess/pieces/pawn.h
)

set(CLI_SOURCES
    src/chess/private-cli/chess-cli.h
    src/chess/private-cli/chess-cli.cpp
)

# add add_executables
add_executable(swc3chess
		src/chess/main.cpp
		${PROJECT_SOURCES}
		${GUI_SOURCES}
        src/chess/main.cpp
        src/chess/main.cpp
        src/chess/main.cpp
        src/chess/main.cpp
        src/chess/chess_piece.cpp)
add_executable(swc3chess-cli
		src/chess/main-cli.cpp
		${PROJECT_SOURCES}
		${CLI_SOURCES})

qt_add_resources(swc3chess "pieces"
    PREFIX "/"
    FILES
        ${PROJECT_RESOURCES}
)

# version with console disabled
# add_executable(QtDraw MACOSX_BUNDLE WIN32 ${PROJECT_SOURCES})

# compile options
target_compile_options(swc3chess PRIVATE ${COMMON_WARNINGS})
target_compile_options(swc3chess-cli PRIVATE ${COMMON_WARNINGS})

# link against libraries
target_link_libraries(swc3chess PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)

if(MINGW)
	message(STATUS "Configuring static linking for MinGW")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif ()
