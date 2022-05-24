#!/bin/bash


BASEDIR=$(dirname "$0")
cd ${BASEDIR}
BASEDIR=`pwd`

GIT_ROOT_DIR=$(git rev-parse --show-cdup)
cd ${GIT_ROOT_DIR}
GIT_ROOT_DIR=`pwd`
cd -
llvm_project=${GIT_ROOT_DIR}/../llvm-project/

cd ${llvm_project}
llvm_branch=`git branch --show-current`
cd -
llvm_install=${GIT_ROOT_DIR}/../${llvm_branch}
llvm_install=${GIT_ROOT_DIR}/../llvmorg-12.0.0
#llvm_install="${GIT_ROOT_DIR}/../llvmorg-13.0.0"

BUILD_TYPE="Ninja"
#BUILD_TYPE="Xcode"

echo "BUILD_TYPE: ${BUILD_TYPE}" 

if [ -d "${llvm_install}" ] 
then
    echo "Directory ${llvm_install} exists." 
else
    echo "Directory ${llvm_install} does not exists."
    
rm -rf build
rm -rf ${llvm_install}
mkdir build

cd build


if [ "$BUILD_TYPE" = "Ninja" ]; then 
cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=${llvm_install} \
${llvm_project}/llvm


ninja -j12

ninja install
elif [ "$BUILD_TYPE" = "Xcode" ]; then 

cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=${llvm_install} \
${llvm_project}/llvm

make -j12

make install
fi

fi

build_target=calc


cd ${BASEDIR}

build_target_dir=${BASEDIR}/build-${build_target}
install_target_dir=${BASEDIR}/install-${build_target}
rm -rf ${build_target_dir}
rm -rf ${install_target_dir}
mkdir ${build_target_dir}
cd ${build_target_dir}




if [ "$BUILD_TYPE" = "Ninja" ]; then 
cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DLLVM_DIR=${llvm_install}/lib/cmake/llvm \
-DCMAKE_INSTALL_PREFIX=${install_target_dir} ../


ninja

ninja install
elif [ "$BUILD_TYPE" = "Xcode" ]; then 

cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DLLVM_DIR=/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter03/calc/build/lib/cmake/llvm \
-DCMAKE_INSTALL_PREFIX=${install_target_dir} ../


make

make install
fi;




