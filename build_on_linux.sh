#!/usr/bin/env bash
set -eu

# # Configure, build and consume LUE (and HPX and MDSpan) as part of the lue_consume build
# build_directory1=~/tmp/lue_consume_build
#
# cmake \
#     --preset lue_consume_debug \
#     -B ${build_directory1} \
#     -G "Ninja" \
#     -D HPX_WITH_MALLOC="tcmalloc"
# cmake --build ${build_directory1} --target all
#
# ${build_directory1}/lue_consume_data_model
# ${build_directory1}/lue_consume_framework

build_type=Debug

# Consume LUE after installing it (and HPX and MDSpan) somewhere
build_directory2=~/tmp/lue_consume_build2
lue_install_prefix=~/tmp/lue-dev
hpx_install_prefix=~/development/opt/$build_type/hpx
mdspan_install_prefix=~/development/opt/$build_type/mdspan

cmake \
    -B ${build_directory2} \
    -G "Ninja" \
    -D CMAKE_BUILD_TYPE=$build_type \
    -D LUE_ROOT=$lue_install_prefix \
    -D HPX_ROOT=$hpx_install_prefix \
    -D MDSPAN_ROOT=$mdspan_install_prefix
cmake --build ${build_directory2} --target all

${build_directory2}/data_model/lue_consume_data_model
${build_directory2}/framework/lue_consume_framework_algorithm
${build_directory2}/framework/lue_consume_framework_io
