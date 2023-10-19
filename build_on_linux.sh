#!/usr/bin/env bash
set -e

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


# Consume LUE after installing it (and HPX and MDSpan) somewhere
build_directory2=~/tmp/lue_consume_build2
lue_install_prefix=~/tmp/lue-dev
hpx_install_prefix=~/development/opt/Debug/hpx
mdspan_install_prefix=~/development/opt/Debug/mdspan

build_type=Debug

cmake \
    -B ${build_directory2} \
    -G "Ninja" \
    -D CMAKE_BUILD_TYPE=$build_type \
    -D CMAKE_POLICY_DEFAULT_CMP0144=NEW \
    -D LUE_ROOT=$lue_install_prefix \
    -D HPX_ROOT=$hpx_install_prefix \
    -D MDSPAN_ROOT=$mdspan_install_prefix
cmake --build ${build_directory2} --target all

${build_directory2}/lue_consume_data_model
${build_directory2}/lue_consume_framework
