# Create a library called "myHumanDetector" (in Linux, this library is created
# with the name of either libmyLib1.a or myLib1.so).
add_library (myHumanTracker
  # list of cpp source files:
  tracker.cpp
  )

# Indicate what directories should be added to the include file search
# path when using this library.
target_include_directories(myHumanTracker PUBLIC
  # list of directories:
  .
  )
