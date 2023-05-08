# **Abstraction library for threads and synchronisation primitives**
## **Introduction**
This library provides abstractions for threading functions, mutex, and semaphores.

## Build steps

### **Prerequisites**
* cmake >= 3.25
* gcc >= 4.8.5 / clang toolchain (For x86-64 and aarch64 Linux builds)
* Visual Studio (For Windows builds)

### **Building for x86-64 Linux**
1. Create a buildtree
  ```
    libThreadPath=<Path to libfgs repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${libThreadPath}
    cmake . -B ${buildTree}\
    -DCMAKE_INSTALL_LIBDIR:STRING=${installPath}\
    -DCMAKE_INSTALL_INCLUDEDIR:STRING=${installPath}
  ```
2. Build using buildtree
  ```      
    cmake --build ${buildTree}
  ```
3. Install (Installs to 'lib' folder)
  ```      
    cmake --install ${buildTree}
  ```
### **Building for aarch64 Linux**
1. Create a buildtree
  ```
    toolchainPath=<Path to aarch64 toolchain>
    libThreadPath=<Path to libfgs repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${libThreadPath}
    PATH=${toolchainPath}:${PATH} cmake . -B ${buildTree}\
    -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchains/aarch64_toolchain.cmake\
    -DCMAKE_INSTALL_LIBDIR:STRING=${installPath}\
    -DCMAKE_INSTALL_INCLUDEDIR:STRING=${installPath}
  ```
2. Build using buildtree
  ```      
    cmake --build ${buildTree}
  ```
3. Install (Installs to 'lib' folder)
  ```      
    cmake --install ${buildTree}
  ```
### **Building for aarch32 Linux**
1. Create a buildtree
  ```
    toolchainPath=<Path to aarch32 toolchain>
    libThreadPath=<Path to libfgs repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${libThreadPath}
    PATH=${toolchainPath}:${PATH} cmake . -B ${buildTree}\
    -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchains/aarch32_toolchain.cmake\
    -DCMAKE_INSTALL_LIBDIR:STRING=${installPath}\
    -DCMAKE_INSTALL_INCLUDEDIR:STRING=${installPath}
  ```
2. Build using buildtree
  ```      
    cmake --build ${buildTree}
  ```
3. Install (Installs to 'lib' folder)
  ```      
    cmake --install ${buildTree}
  ```
### **Building for x86-64 Windows**
1. Open git bash
2. Create a buildtree
  ```
    libThreadPath=<Path to libfgs repo>
    buildTree=<Name of buildTree folder>
    installPath=<Path to install folder>
    cd ${libThreadPath}
    cmake . -B ${buildTree} -A x64
  ```
2. Build using buildtree
  ```      
    cmake --build ${buildTree}\
    -DCMAKE_INSTALL_LIBDIR:STRING=${installPath}\
    -DCMAKE_INSTALL_INCLUDEDIR:STRING=${installPath}\
    -- -p:Configuration="Release"
  ```
3. Install (Installs to 'lib' folder)
  ```      
    cmake --install ${buildTree}
  ```
## **License**
A BSD 3-Clause-Clear license is applicable. Refer to the [LICENSE](https://github.com/ittiam-systems/libthread/LICENSE) file together with the [LICENSE2](https://github.com/ittiam-systems/libthread/LICENSE2) file.
