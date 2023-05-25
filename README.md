# Learn-LLVM-12
<a href="https://www.packtpub.com/in/cloud-networking/learn-llvm-11?utm_source=github&utm_medium=repository&utm_campaign=9781786461629"><img src="https://www.packtpub.com/media/catalog/product/cache/4cdce5a811acc0d2926d7f857dceb83b/9/7/9781839213502-original_188.jpeg" alt="Useful Links" height="256px" align="right"></a>

This is the code repository for [Learn LLVM 12](https://www.packtpub.com/in/cloud-networking/learn-llvm-11?utm_source=github&utm_medium=repository&utm_campaign=9781786461629), published by Packt.

**A beginner's guide to learning LLVM compiler tools and core libraries with C++**

## What is this book about?
LLVM was built to bridge the gap between compiler textbooks and actual compiler development. It provides a modular codebase and advanced tools which help developers to build compilers easily. This book provides a practical introduction to LLVM, gradually helping you navigate through complex scenarios with ease when it comes to building and working with compilers.

You’ll start by configuring, building, and installing LLVM libraries, tools, and external projects. Next, the book will introduce you to LLVM design and how it works in practice during each LLVM compiler stage: frontend, optimizer, and backend. Using a subset of a real programming language as an example, you will then learn how to develop a frontend and generate LLVM IR, hand it over to the optimization pipeline, and generate machine code from it. Later chapters will show you how to extend LLVM with a new pass and how instruction selection in LLVM works. You’ll also focus on Just-in-Time compilation issues and the current state of JIT-compilation support that LLVM provides, before finally going on to understand how to develop a new backend for LLVM.

By the end of this LLVM book, you will have gained real-world experience in working with the LLVM compiler development framework with the help of hands-on examples and source code snippets.

This book covers the following exciting features:
Configure, compile, and install the LLVM framework
Understand how the LLVM source is organized
Discover what you need to do to use LLVM in your own projects
Explore how a compiler is structured, and implement a tiny compiler
Generate LLVM IR for common source language constructs
Set up an optimization pipeline and tailor it for your own needs
Extend LLVM with transformation passes and clang tooling
Add new machine instructions and a complete backend

If you feel this book is for you, get your [copy](https://www.amazon.com/dp/1839213507) today!

<a href="https://www.packtpub.com/?utm_source=github&utm_medium=banner&utm_campaign=GitHubBanner"><img src="https://raw.githubusercontent.com/PacktPublishing/GitHub/master/GitHub.png" 
alt="https://www.packtpub.com/" border="5" /></a>

## Instructions and Navigations
All of the code is organized into folders. For example, Chapter02.

The code will look like the following:
```
Size = 4;
uint32_t Inst = 0;
for (uint32_t I = 0; I < Size; ++I)
```

## Errata
Page 6, paragraph 2:
_.....with a package manager. The easiest way to install all the software is to use the Chocolately_ **should be read as** _.....with a package manager. The easiest way to install all the software is to use the Chocolatey_

Page 33, bullet point no. 5:
_You should see the friendly message. Please also check that the Basic library was installed_:
```
$ ls ../llvm-12/lib/libtinylang*
````
_This will show that there is a libtinylangBasic.a file._

**Should be read as:**


_You should see the friendly message. Please also check that the Basic library was installed_:
```
$ ls ../llvm-12/lib/tinylang*
```
_This will show that there is a tinylangBasic.lib file._

**Following is what you need for this book:**
This book is for compiler developers, enthusiasts, and engineers who are new to LLVM and are interested in learning about the LLVM framework. It is also useful for C++ software engineers looking to use compiler-based tools for code analysis and improvement, as well as casual users of LLVM libraries who want to gain more knowledge of LLVM essentials. Intermediate-level experience with C++ programming is mandatory to understand the concepts covered in this book more effectively.

With the following software and hardware list you can run all code files present in the book (Chapter 1-12).
### Software and Hardware List
| No. | Software required | OS required |
| -------- | ------------------------------------ | ----------------------------------- |
| 1 | C/C++ compiler | Windows, Mac OS X, and Linux (Any) |
| 2 | CMake 3.13.4 or later | Windows, Mac OS X, and Linux (Any) |
| 3 | Ninja 1.9.0 | Windows, Mac OS X, and Linux (Any) |
| 4 | Python 3.6 or later | Windows, Mac OS X, and Linux (Any) |
| 6 | Git 1.7.10 or later | Windows, Mac OS X, and Linux (Any) |

We also provide a PDF file that has color images of the screenshots/diagrams used in this book. [Click here to download it](https://static.packt-cdn.com/downloads/9781839213502_ColorImages.pdf).

## Code in Action
Please visit the following link to check the CiA videos: https://bit.ly/3nllhED

### Related products
* LLVM Techniques, Tips, and Best Practices Clang and Middle-End Libraries [[Packt]](https://www.packtpub.com/product/llvm-techniques-tips-and-best-practices-clang-and-middle-end-libraries/9781838824952?utm_source=github&utm_medium=repository&utm_campaign=9781838824952) [[Amazon]](https://www.amazon.com/dp/1838824952)

* Modern C++ Programming Cookbook - Second Edition [[Packt]](https://www.packtpub.com/product/modern-c-programming-cookbook-second-edition/9781800208988?utm_source=github&utm_medium=repository&utm_campaign=9781800208988) [[Amazon]](https://www.amazon.com/dp/1800208987)

## Get to Know the Author
**Kai Nacke** is a professional IT architect currently living in Toronto, Canada. He holds a diploma in computer science from the Technical University of Dortmund, Germany. His diploma thesis about universal hash functions was recognized as the best of the semester.
He has been working in the IT industry for more than 20 years and has great experience in the development and architecture of business and enterprise applications. In his current role, he evolves an LLVM/Clang-based compiler.
For some years, he was the maintainer of LDC, the LLVM-based D compiler. He is the author of D Web Development, published by Packt. In the past, he was also a speaker in the LLVM developer room at the FOSDEM.





## 1.4 opt 调试参数 （可以调试 ollvm）

-S -fla -debug-only=flattening --passes="obfuscation"  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/demo.ll -o /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/demo_out.ll

## 1.5 clang调试参数

-S -emit-llvm /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c -o  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll


SDKROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk

## 1.6 lldb 调试 obfuscation ,调试 clang
### 1.首先使用 Xcode的Debug模式下 clang -### 输出参数

-### -S -emit-llvm -mllvm -sub -mllvm -bcf -mllvm -fla /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c -o  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll

获得

clang version 12.0.0 (git@github.com:iOSPrincekin/llvm-project.git f460958227210abde112d224b8c156555321c34b)
Target: x86_64-apple-darwin21.5.0
Thread model: posix
InstalledDir: /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin
 (in-process)
 "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin/clang" "-cc1" "-triple" "x86_64-apple-macosx12.0.0" "-Wundef-prefix=TARGET_OS_" "-Werror=undef-prefix" "-Wdeprecated-objc-isa-usage" "-Werror=deprecated-objc-isa-usage" "-emit-llvm" "-disable-free" "-main-file-name" "main.c" "-mrelocation-model" "pic" "-pic-level" "2" "-mframe-pointer=all" "-fno-rounding-math" "-munwind-tables" "-target-sdk-version=12.3" "-fcompatibility-qualified-id-block-type-checking" "-fvisibility-inlines-hidden-static-local-var" "-target-cpu" "penryn" "-tune-cpu" "generic" "-debugger-tuning=lldb" "-target-linker-version" "762" "-resource-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0" "-isysroot" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk" "-internal-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/local/include" "-internal-isystem" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0/include" "-internal-externc-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/include" "-fdebug-compilation-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin" "-ferror-limit" "19" "-stack-protector" "1" "-fblocks" "-fencode-extended-block-signature" "-fregister-global-dtors-with-atexit" "-fgnuc-version=4.2.1" "-fmax-type-align=16" "-mllvm" "-sub" "-mllvm" "-bcf" "-mllvm" "-fla" "-o" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll" "-x" "c" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c"
### 2.使用新的参数，重新运行Xcode Debug模式下的clang

参数

"-cc1" "-triple" "x86_64-apple-macosx12.0.0" "-Wundef-prefix=TARGET_OS_" "-Werror=undef-prefix" "-Wdeprecated-objc-isa-usage" "-Werror=deprecated-objc-isa-usage" "-emit-llvm" "-disable-free" "-main-file-name" "main.c" "-mrelocation-model" "pic" "-pic-level" "2" "-mframe-pointer=all" "-fno-rounding-math" "-munwind-tables" "-target-sdk-version=12.3" "-fcompatibility-qualified-id-block-type-checking" "-fvisibility-inlines-hidden-static-local-var" "-target-cpu" "penryn" "-tune-cpu" "generic" "-debugger-tuning=lldb" "-target-linker-version" "762" "-resource-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0" "-isysroot" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk" "-internal-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/local/include" "-internal-isystem" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0/include" "-internal-externc-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/include" "-fdebug-compilation-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin" "-ferror-limit" "19" "-stack-protector" "1" "-fblocks" "-fencode-extended-block-signature" "-fregister-global-dtors-with-atexit" "-fgnuc-version=4.2.1" "-fmax-type-align=16" "-mllvm" "-sub" "-mllvm" "-bcf" "-mllvm" "-fla" "-o" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll" "-x" "c" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c"

## 1.7 解决clang 调试时，LLVM_DEBUG(dbgs() 不输出log的问题，-mllvm -debug、-mllvm -debug-only=isel 必须加 -mllvm

参数

--target=riscv32 -mllvm -debug -O2 /Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter09/tblgen/LLVM笔记/LLVM笔记\(10\)-指令选择\(二\)lowering/1.c  -S -mllvm -view-dag-combine1-dags=true

