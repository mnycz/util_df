# README

This library contains useful functions for streamlining plotting data in the ROOT (CERN) framework 
and computing mathematical quantities (mean, std dev, allan dev, etc) on std::vector data types.  
There are also classes dedicated to CSV file handling and miscellaneous algorithms.

## Prerequisites 

In order to utilize the library, you must have the following installed: 

- ROOT (version 6 or later)  
- CMake (version 3.9 or later) 

## Building the Library 

To build the library, create `build` and `install` diretories in parallel to the `util_df` directory.  
Change to the `build` directory.  Copy the `build.sh` script from the `util_df` directory to the 
`build` directory. Execute `./build.sh`.  This will configure your environment, make, and install 
the library.  Before running the `build.sh` script, make sure your directory names match what is 
written in the script.  

## Loading the Library into ROOT 

To use the library in ROOT, you will need to load the `include` and `lib` files 
into your ROOT session.  This is done by writing a `.rootlogon.C` file that loads the library to 
your ROOT session. See the `~/examples/rootlogon.C` file for an example.  Write your own file 
in your home directory, and adjust the `utilPath` string as necessary.   

## Using the Library

Sample usage of the code is given in the `examples` directory. 
