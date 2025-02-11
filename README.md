Steps to build the code: 
1. Create a build directory and navigate into it:
   
   mkdir build
   
   cd build


3. Run CMake to generate the build files. If you're using MinGW, use:
   
   cmake -G "MinGW Makefiles" ..


3.If you're using Visual Studio, use:

   cmake -G "Visual Studio 17 2022" ..


4.Build the project:

  For MinGW:
  
  mingw32-make


5.Run the executable:

  For MinGW:
  
  ./ChessEngine.exe
