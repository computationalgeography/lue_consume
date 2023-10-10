#!/usr/bin/env bash
set -e

build_directory=~/tmp/lue_consume_build

cmake --preset lue_consume_debug \
    -B ${build_directory} \
    -G "Ninja" \
    -D HPX_WITH_MALLOC="tcmalloc"
cmake --build ${build_directory} --target all

${build_directory}/lue_consume_data_model
${build_directory}/lue_consume_framework
