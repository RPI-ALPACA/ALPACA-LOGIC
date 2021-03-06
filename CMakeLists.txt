cmake_minimum_required(VERSION 3.10)
project(logic)

set(CMAKE_CXX_STANDARD 14)
set(COMPILE_FLAGS    "-Wextra -Werror -g")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

set(expressionparser_files
        expressionparser.cpp
        expressionparser.h)

add_executable(logic
        ${expressionparser_files}
        main.cpp
        LogicGate.cpp
        LogicGate.h
        statement.cpp
        statement.h
        statementevaluator.cpp
        statementevaluator.h
        Tree.cpp
        Tree.h)

add_executable(logic-test
        ${expressionparser_files}
        LogicTest.cpp
        LogicGate.cpp
        LogicGate.h
        statement.cpp
        statement.h
        statementevaluator.cpp
        statementevaluator.h
        Tree.cpp
        Tree.h)
add_executable(logic-wasm
	${expressionparser_files}
        LogicGate.cpp
        LogicGate.h
        emscripten_wrap.cpp
        statement.cpp
        statement.h
        statementevaluator.cpp
        statementevaluator.h
        Tree.cpp
        Tree.h)

set_target_properties(logic-wasm PROPERTIES LINK_FLAGS "--bind")

