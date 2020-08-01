# README

This library contains useful functions for streamlining plotting data in ROOT and computing 
mathematical quantities (mean, std dev, allan dev, etc) on std::vector data types.  There are 
also classes dedicated to CSV file handling and miscellaneous algorithms. 

## Building the Library 

To build the library, create a build diretory in parallel to the `util_df` directory.  Change 
to the build directory.  Copy the build.sh script from the source directory to the build directory. 
Execute ./build.sh.   

## Loading the Library into ROOT 

To load the library into ROOT, you will need to load the `include` and `lib` files 
into ROOT.  This is done by writing a `.rootlogon.C` file that loads the library to your ROOT session. 
See the `~/examples/rootlogon.C` file as an example.  Write your own file in your 
home directory, and adjust the `utilPath` string as necessary.   

## Testing the Library

To test the library, you can write a simple ROOT script, and include the class/namespace 
as needed.  For instance, if you want to use the `util_df::Math` namespace, 
the top of your script should have the directive `#include UtilDFMath.h`.  The examples directory has 
some sample code. 
