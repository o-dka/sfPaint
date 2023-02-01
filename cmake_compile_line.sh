#!/usr/bin/env bash
cmake -G Ninja -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -B build -S .