# Create a library called "myHumanDetector" (in Linux, this library is created
# with the name of either libmyLib1.a or myLib1.so).
add_library (myHumanDetector
  # list of cpp source files:
  detector.cpp
  )

# Indicate what directories should be added to the include file search
# path when using this library.
target_include_directories(myHumanDetector PUBLIC
  # list of directories:
  .
  )
