## 文件介绍
* include/\*：v8 头文件，来自 v8 12.4.1 源代码
* lib/libv8\_monolith.a：v8 静态库，由 v8 12.4.1 源代码编译得到
* src/\*：自己实现的迷你运行时源代码
* CMakeLists.txt：构建工具 cmake 的配置文件
* test.js：测试脚本

## 编译指导

这里提供两种编译方式

### 1. 使用构建工具 cmake 进行编译

使用该方式更便捷，更接近实际的工程化开发

```sh
# 安装依赖，以 ubuntu 为例
sudo apt install cmake gcc lld

# 编译
mkdir build
cd build
cmake ..
make
```

### 2. 手动调用 gcc 编译器进行编译

如果你不想额外接触一套工具，你也可以选择手动调用 gcc 编译器进行编译

```sh
# 安装依赖，以 ubuntu 为例
sudo apt install cmake gcc lld

# 编译
g++ src/main.cc src/example.cc -o my_node -Iinclude -fno-rtti -fuse-ld=lld -lv8_monolith -ldl -Llib/ -pthread -std=c++20 -DV8_COMPRESS_POINTERS -DV8_ENABLE_SANDBOX
```
