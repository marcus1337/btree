cmake_minimum_required(VERSION 3.17.4)
project(btree)
set (CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
"src/BehaviorTree.cpp"
"src/Composite.cpp"
"src/Task.cpp"
"src/Node.cpp" 
"src/BehaviorTreeBuilder.cpp" "src/BehaviorTreeMutater.cpp")

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
)



