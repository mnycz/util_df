#! /bin/bash  
# a simple script to build util_df
#_______________________________________________________________________________
function cleanup { 
   echo "Cleaning up previous build..."
   rm -r CMakeFiles *.cmake *.txt *.cxx *.pcm *.rootmap Makefile *.so 
   echo "--> Done!"
}
#_______________________________________________________________________________
function configure { 
   echo "Configuring..."
   cmake -DCMAKE_INSTALL_PREFIX=../install ../util_df 
   echo "--> Done!"
}
#_______________________________________________________________________________
function build_lib { 
   echo "Building..."
   make && make install
   # for macOS
   cd ../install/lib && rm *.so && ln -s libutil_df.dylib libutil_df.so
   # cp *.pcm *.rootmap ../lib
   echo "--> Done!"
}
#_______________________________________________________________________________
# main 
cleanup
configure
build_lib
