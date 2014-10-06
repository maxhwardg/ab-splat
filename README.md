#ab-splat
This repository contains source code for the ab-splat algorithm.

##Setup
Simply use 'make' to build the 'ab-splat' executable. Open this folder in the command line, and enter 'make'. Obviously you may need to install the latest versions of make and GCC if you do not have them installed.

##Usage
A brief version of usage information will be printed to the standard output stream when ab-splat is executed. A more detailed version follows here.
Call ab-splat like this './ab-splat a b' where a and b are the values for a and b used by the algorithm to generate sliding windows. If no values for a and b are provided, default values will be used. It is reccomend to use the default values unless you really know what you are doing.

##Notes
Vienna RNA (2.1.6) has been modified slightly for ab-splat, and a static library version is included in the vienna folder as 'libRNA.a'. The modified file (LFold.c) has also been included, along with the header needed to use the library. Obviously, libRNA.a can be recompiled with a newer version of Vienna by dropping the LFold.c and LFold.h files into the Vienna RNA source, and then running Vienna's makefile. Running this makefile produces libRNA.a, as well as all the Vienna RNA binaries.
