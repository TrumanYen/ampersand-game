cmake_minimum_required(VERSION 3.28.3)

project(AmpersandGame)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

set(ExeName "ampersand_game")
add_executable(${ExeName})

set_target_properties(${ExeName} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
target_sources(${ExeName} PRIVATE

  main.cxx
  gameLogicContainer.cxx
  external/terminalPresenter.cxx
  external/ncursesStyleManager.cxx
  adapter/viewModel.cxx
  useCase/useCase.cxx
  useCase/ampersandStatus.cxx
  domain/ampersandSimulation.cxx
  domain/mapState.cxx
  domain/simulationDomain.cxx
)

target_include_directories(${ExeName} PRIVATE 
  ${CURSES_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${ExeName} PRIVATE ${CURSES_LIBRARIES})
