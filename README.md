# README

This library contains useful functions for streamlining plotting data in ROOT and computing 
mathematical quantities (mean, std dev, allan dev, etc) on std::vector data types.  There are 
also classes dedicated to CSV file handling and miscellaneous algorithms. 

## Building the Library 

To build the library, create a build diretory in parallel to the `util_df` directory.  Change 
to the build directory.  Copy the build.sh script from the source directory to the build directory. 
Execute ./build.sh.   

## Loading the Library into ROOT 

To use the library in ROOT, you will need to load the `include` and `lib` files 
into your ROOT session.  This is done by writing a `.rootlogon.C` file that loads the library to 
your ROOT session. See the `~/examples/rootlogon.C` file for an example.  Write your own file 
in your home directory, and adjust the `utilPath` string as necessary.   

## Using the Library

Sample usage of the code is given in the `examples` directory. 
