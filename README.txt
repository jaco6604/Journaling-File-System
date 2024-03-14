To run this project the boost filesystem must be installed which can be found at this link https://www.boost.org/doc/libs/1_84_0/more/getting_started/windows.html#get-boost
Once downloaded a file in there named b2 needs to be run to install the boost filesystem.
The stage folder will appear once this is ran.
Visual Studio was used in this project and to get the project to work with the boost filesystem go into the configuration properties the boost stage folder needs to be linked to under C++ -> General -> Additional Include Directories
This same folder needs to be included under Linker in the configuration properties. Linker -> General -> Additional Library Directories
The final thing to do is within Configuration Properties -> C/C++ -> Preprocessor -> Use Standard Conforming Preproces. Set this to "Yes (/Zc:preprocessor)