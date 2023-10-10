#include <lue/data_model.hpp>
#include <lue/validate.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


int main([[maybe_unused]] int const argc, [[maybe_unused]] char** argv)
{
    int status{EXIT_FAILURE};

    try {
        std::string const pathname{"lue_consume_test_file.lue"};

        // Create a dataset
        {
            auto dataset = lue::data_model::create_dataset(pathname, "Hello LUE dataset!");
            lue::data_model::assert_is_valid(dataset);
            std::cout << "→ Successfully created a LUE dataset\n";
        }

        // Read a dataset
        {
            auto dataset = lue::data_model::open_dataset(pathname);
            std::cout << "pathname       : " << pathname << std::endl;
            std::cout << "    LUE version: " << dataset.lue_version() << std::endl;
            std::cout << "    description: " << dataset.description() << std::endl;
            std::cout << "→ Successfully opened a LUE dataset\n";
        }

        // Remove a dataset
        {
            lue::data_model::remove_dataset(pathname);
            std::cout << "→ Successfully removed a LUE dataset\n";
        }

        status = EXIT_SUCCESS;
    }
    catch(std::exception const& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    return status;
}
