#!/bin/bash
PROJECT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR=${PROJECT_DIR}/.build/
BIN_DIR=${PROJECT_DIR}/bin/
CONAN_DIR=${PROJECT_DIR}/conan/

if [ -d $BUILD_DIR ]; then 
    cd $BUILD_DIR
else 
    mkdir $BUILD_DIR
    cd $BUILD_DIR
fi 

BUILD_TYPE="Debug"
if [ "$#" -ge "1" ]; then
    BUILD_TYPE=$1;
fi

if [ "$BUILD_TYPE" = "clean" ]; then
    rm -rf $BUILD_DIR
    exit 0
fi 

conan install -s build_type=$BUILD_TYPE ${CONAN_DIR}
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. 
cmake --build .