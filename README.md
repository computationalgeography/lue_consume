# lue_consume
Dummy project for demonstrating how and testing whether consuming the LUE repository works.

When configuring the project, CMake will first try to find LUE using `FindPackage`. If that fails,
`FetchContent` is used to download and configure LUE (and HPX) as part of the `lue_consume`
project. Whichever option is used to obtain the LUE targets is not relevant to how to use the
LUE targets in the CMake and C++ code.
