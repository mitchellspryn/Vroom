# Vroom
Vroom Vroom

# Before building
Copy Dependencies and Content from share provied by mspryn. Eventually, this will go into LFS.
Unzip dependencies into Dependencies/ folder, and unzip content folder into Content/ folder. 

You will need to add the following paths to your include directory:
* Dependencies/rapidjson
* Dependencies/opencv/build/include
* Dependencies/eigen

You will need to add the following paths to your library directory:
* Dependencies/opencv/build/x64/vc14/lib

This has been tested to build with Visual Studio 2015, x64. Make sure to set build configuration to "DebugGame Editor"