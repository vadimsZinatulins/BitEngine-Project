# BitEngine 
Base Engine library

## Build
Open the project in Visual Studio 2019, choose the Platform and Configuration and hit Build.

The output goes to `bin/BitEngine/{Platform}/{Configuration}/` and it will contain two directories:
- include\: Contains all __header__ files
- lib\: Contains all the __.lib__ files and __.dll__ files required to use BitEngine

# GameTest
Project that implements BitEngine library for testing purpose

## Build
Open the project in Visual Studio 2019, choose the Platform and Configuration and hit Build. Make sure BitEngine library is built first
and then this project (do not build both at the same, i.e. don't use CTRL+SHIFT+B or CTRL+F5 which triggers the solution build).

The output goes to `bin/GameTest/{Platform}/{Configuration}/` and it will contain the __.exe__ file.