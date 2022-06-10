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


# ================================ buildLLVMTEMP 方法开始 =========================

function buildLLVMTEMP()
{
TEMP=$1
#TEMP_install=${GIT_ROOT_DIR}/../${llvm_branch}
TEMP_install=${GIT_ROOT_DIR}/../llvmorg-12.0.0
#TEMP_install="${GIT_ROOT_DIR}/../llvmorg-13.0.0"




#BUILD_TYPE="Ninja"
BUILD_TYPE="Xcode"

echo "BUILD_TYPE: ${BUILD_TYPE}" 


if [ "$BUILD_TYPE" = "Xcode" ]; then 
TEMP_install="${BASEDIR}/build-${TEMP}"
fi


#BUILD_FORCE="FORCE"
# 强制编译 ${TEMP}
if [ "$BUILD_FORCE" = "FORCE" ]; then 
echo "mv ${TEMP_install} ${TEMP_install}-bak..."
mv ${TEMP_install} ${TEMP_install}-bak
fi


if [ -d "${TEMP_install}" ] 
then
    echo "Directory ${TEMP_install} exists." 
else
    echo "Directory ${TEMP_install} does not exists."
    
rm -rf ${TEMP_install}
mkdir ${TEMP_install}

cd ${TEMP_install}


if [ "$BUILD_TYPE" = "Ninja" ]; then 
cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=${TEMP_install} \
${llvm_project}/${TEMP}


ninja -j12

ninja install
elif [ "$BUILD_TYPE" = "Xcode" ]; then 

cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=${TEMP_install} \
${llvm_project}/${TEMP}

make -j12

make install
fi

fi

}

# ================================ buildLLVMTEMP 方法结束 =========================

buildLLVMTEMP llvm

# ================================ build Target 开始 =========================


build_target=calc

cd ${BASEDIR}

build_target_dir=${BASEDIR}/build-${build_target}
install_target_dir=${BASEDIR}/install-${build_target}

if [ -d "${install_target_dir}" ] 
then
    echo "Directory ${install_target_dir} exists." 
else
rm -rf ${build_target_dir}
rm -rf ${install_target_dir}
mkdir ${build_target_dir}
cd ${build_target_dir}




if [ "$BUILD_TYPE" = "Ninja" ]; then 
cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DLLVM_DIR=${TEMP_install}/lib/cmake/llvm \
-DCMAKE_INSTALL_PREFIX=${install_target_dir} ../


ninja

ninja install
elif [ "$BUILD_TYPE" = "Xcode" ]; then 
cmake -G $BUILD_TYPE -DCMAKE_BUILD_TYPE=Release \
-DLLVM_DIR=${TEMP_install}/lib/cmake/llvm \
-DCMAKE_INSTALL_PREFIX=${install_target_dir} ../

fi;
fi;
# ================================ build Target 结束 =========================




