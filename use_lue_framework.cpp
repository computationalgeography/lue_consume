#include <lue/framework/algorithm/definition/focal_operation.hpp>
#include <lue/framework/algorithm/serialize/kernel.hpp>
#include "lue/framework/algorithm/value_policies/comparison.hpp"
#include "lue/framework/algorithm/value_policies/logical_and.hpp"
#include "lue/framework/algorithm/value_policies/uniform.hpp"
#include "lue/framework/algorithm/value_policies/where.hpp"
#include <lue/framework/partitioned_array.hpp>
#include <hpx/hpx_main.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


/*!
    @brief      Class for focal operation functors

    The logic is silly: it determines how many valid values are located within the focal
    area. If this count is an even number, some magic value is returned, and if it is odd,
    some other magic value is returned.
*/
template<typename InputElement>
class FocalEvenOdd
{

    public:

        using OutputElement = InputElement;

        template<typename Kernel, typename OutputPolicies, typename InputPolicies, typename Subspan>
            OutputElement operator()(
                Kernel const& kernel,
                OutputPolicies const& output_policies,
                InputPolicies const& input_policies,
                Subspan const& window) const
            {
                using Weight = lue::ElementT<Kernel>;

                auto const& indp = input_policies.input_no_data_policy();
                auto const& ondp = output_policies.output_no_data_policy();

                lue::Count nr_valid_elements{0};

                for (lue::Index r = 0; r < window.extent(0); ++r)
                {
                    for (lue::Index c = 0; c < window.extent(1); ++c)
                    {
                        Weight const weight{kernel(r, c)};
                        InputElement const value{window(r, c)};

                        if (!indp.is_no_data(value) && weight)
                        {
                            ++nr_valid_elements;
                        }
                    }
                }

                return nr_valid_elements % 2 == 0 ? _even : _odd;
            }

    private:

        static OutputElement const _even{5};

        static OutputElement const _odd{3};

};


// Some values and types used in this example
lue::Rank const rank{2};

using Element = std::int32_t;
using Array = lue::PartitionedArray<Element, rank>;
using Shape = typename Array::Shape;
using Kernel = lue::Kernel<std::uint8_t, rank>;


lue::PartitionedArray<Element, rank> focal_even_odd(
    Array const& array, Kernel const& kernel)
{
    using Policies = lue::policy::DefaultSpatialOperationValuePolicies<
        lue::policy::AllValuesWithinDomain<Element>,
        lue::policy::OutputElements<Element>,
        lue::policy::InputElements<Element>>;
    using Functor = FocalEvenOdd<Element>;

    return lue::focal_operation(Policies{}, array, kernel, Functor{});
}


int main([[maybe_unused]] int const argc, [[maybe_unused]] char** argv)
{
    int status{EXIT_FAILURE};

    try {
        // Select operations that use certain policies
        using namespace lue::value_policies;

        // Create a partitioned array, filled with random values [0, 100]
        Shape const array_shape{60, 40};
        Shape const partition_shape{10, 10};
        Element const min_value{0};
        Element const max_value{100};

        // TODO Get rid of partition_shape argument
        Array input_array = uniform<Element>(array_shape, partition_shape, min_value, max_value);

        // Introduce some no-data by excluding a range of values [40, 60]
        input_array = where(input_array < Element{40} && input_array > Element{60}, input_array);

        // Call our function and wait for it to finish
        Kernel const kernel = lue::box_kernel<std::uint8_t, rank>(1, 1);
        Array output_array = focal_even_odd(input_array, kernel);

        lue::wait_all(output_array.partitions());

        std::cout << "→ Successfully performed some asynchronous computations\n";
        status = EXIT_SUCCESS;
    }
    catch(std::exception const& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    return status;
}
