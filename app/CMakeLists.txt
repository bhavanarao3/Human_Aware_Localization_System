# Any C++ source files needed to build this target (shell-app).
add_executable(shell-app
  # list of source cpp files:
  main.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(shell-app PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/libs/human_tracker
  ${CMAKE_SOURCE_DIR}/libs/human_detector
  ${OpenCV_INCLUDE_DIRS}  # Add OpenCV include directories
)

# Any dependent libraires needed to build this target.
target_link_libraries(shell-app PUBLIC 
  # list of libraries
  myHumanDetector
  myHumanTracker
  ${OpenCV_LIBS}
  )

  
