#include <lue/framework/algorithm/definition/focal_operation.hpp>
#include <lue/framework/algorithm/serialize/kernel.hpp>
#include <lue/framework/partitioned_array.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


template<typename InputElement>
class FocalEvenOdd
{

    public:

        using OutputElement = InputElement;


        template<typename Kernel, typename OutputPolicies, typename InputPolicies, typename Subspan>
            OutputElement operator()(
                [[maybe_unused]] Kernel const& kernel,
                [[maybe_unused]] OutputPolicies const& output_policies,
                [[maybe_unused]] InputPolicies const& input_policies,
                [[maybe_unused]] Subspan const& window) const
            {
                return OutputElement{};
            }

    private:

};


template<typename Policies, typename Element, lue::Rank rank, typename Kernel>
lue::PartitionedArray<Element, rank> focal_even_odd(
    Policies const& policies, lue::PartitionedArray<Element, rank> const& array, Kernel const& kernel)
{
    using Functor = FocalEvenOdd<Element>;

    return lue::focal_operation(policies, array, kernel, Functor{});
}


using Element = std::int32_t;


using Policies = lue::policy::DefaultSpatialOperationValuePolicies<
    lue::policy::AllValuesWithinDomain<Element>,
    lue::policy::OutputElements<Element>,
    lue::policy::InputElements<Element>>;


using Kernel = lue::Kernel<std::uint8_t, 2>;


template lue::PartitionedArray<Element, 2> focal_even_odd<Policies>(
    Policies const&, lue::PartitionedArray<Element, 2> const&, Kernel const&);


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
