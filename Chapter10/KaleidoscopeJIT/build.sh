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


# ================================ buildLLVMllvm 方法开始 =========================





#BUILD_TYPE="Ninja"
BUILD_TYPE="Xcode"

echo "BUILD_TYPE: ${BUILD_TYPE}" 


if [ "$BUILD_TYPE" = "Xcode" ]; then 
llvm_install="${BASEDIR}/../../../llvmorg-Xcode"
fi


#BUILD_FORCE="FORCE"
# 强制编译 ${llvm}
if [ "$BUILD_FORCE" = "FORCE" ]; then 
echo "mv ${llvm_install} ${llvm_install}-bak..."
mv ${llvm_install} ${llvm_install}-bak
fi


if [ -d "${llvm_install}" ] 
then
    echo "Directory ${llvm_install} exists." 
else
    echo "Directory ${llvm_install} does not exists."
    
rm -rf ${llvm_install}
mkdir ${llvm_install}

cd ${llvm_install}


if [ "$BUILD_TYPE" = "Ninja" ]; then 
cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=${llvm_install} \
${llvm_project}/llvm


ninja -j12

ninja install
elif [ "$BUILD_TYPE" = "Xcode" ]; then 

cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DLLVM_ENABLE_PROJECTS=clang \
-DCMAKE_INSTALL_PREFIX=${llvm_install} \
${llvm_project}/llvm

make -j12

make install
fi

fi


# ================================ buildLLVMllvm 方法结束 =========================



# ================================ build Target 开始 =========================


build_target=KaleidoscopeJIT

cd ${BASEDIR}

build_target_dir=${BASEDIR}/build-${build_target}
install_target_dir=${BASEDIR}/install-${build_target}

if [ -d "${build_target_dir}" ] 
then
    echo "Directory ${build_target_dir} exists." 
else
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
-DLLVM_DIR=${llvm_install}/lib/cmake/llvm \
-DCMAKE_INSTALL_PREFIX=${install_target_dir} ../

fi;
fi;
# ================================ build Target 结束 =========================




