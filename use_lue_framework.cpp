// #include <lue/data_model.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


int main([[maybe_unused]] int const argc, [[maybe_unused]] char** argv)
{
    int status{EXIT_FAILURE};

    try {
        status = EXIT_SUCCESS;
    }
    catch(std::exception const& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    return status;
}
