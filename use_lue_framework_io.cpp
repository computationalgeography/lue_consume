#include <lue/framework/algorithm/value_policies/all.hpp>
#include <lue/framework/algorithm/value_policies/comparison.hpp>
#include <lue/framework/algorithm/value_policies/uniform.hpp>
#include <lue/framework/io.hpp>
#include <lue/gdal.hpp>
#include <hpx/hpx_main.hpp>
#include <cstdlib>
#include <iostream>


int main([[maybe_unused]] int const argc, [[maybe_unused]] char** argv)
{
    int status{EXIT_FAILURE};

    try {
        // Select operations that use certain policies
        using namespace lue::value_policies;

        // Some values and types used in this example
        lue::Rank const rank{2};

        using Element = std::int32_t;
        using Array = lue::PartitionedArray<Element, rank>;
        using Shape = typename Array::Shape;

        // Create a partitioned array, filled with random values [0, 100]
        Shape const array_shape{60, 40};
        Shape const partition_shape{10, 10};
        Element const min_value{0};
        Element const max_value{100};

        // Needed because we one of GDAL's drivers
        lue::gdal::register_gdal_drivers();

        Array input_array = uniform<Element>(array_shape, partition_shape, min_value, max_value);

        // Save array to raster
        auto raster_written = lue::to_gdal(input_array, "test.tiff");

        // Wait for it to finish
        raster_written.get();

        // Read array from raster
        auto output_array = lue::from_gdal<Element>("test.tiff", partition_shape);

        // Compare arrays
        auto rasters_are_equal = all(output_array == input_array);

        if(rasters_are_equal.future().get())
        {
            std::cout << "→ Raster read is EQUAL to raster written\n";
            status = EXIT_SUCCESS;
        }
        else
        {
            std::cout << "→ Raster read is NOT EQUAL to raster written\n";
        }
    }
    catch(std::exception const& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    return status;
}
