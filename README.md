# cx_header_file
关于cuda的一些高效头文件
以及对于BLAS的张量化改写
# CX Header File

> 🚀 A lightweight CUDA utility header library with optimized wrappers for cuBLAS and Tensor Core programming.

![CUDA](https://img.shields.io/badge/CUDA-12.x-green)
![Language](https://img.shields.io/badge/C++17-blue)
![Platform](https://img.shields.io/badge/Linux%20%7C%20Windows-lightgrey)
![License](https://img.shields.io/badge/License-MIT-blue)

---

## 📖 项目简介

**CX Header File** 是一个面向 CUDA 开发的头文件工具库，提供了一系列高性能 CUDA 编程辅助模块，并对 **cuBLAS** API 进行了轻量化封装，使 GPU 编程更加简洁、高效。

本项目主要面向：

- CUDA 开发者
- GPU 高性能计算（HPC）
- 深度学习底层开发
- CUDA 学习与实验
- Tensor Core 编程

所有组件均采用 Header Only 方式组织，可直接引入工程使用。

---

## ✨ 功能特性

- ⚡ CUDA 常用工具函数
- 🚀 cuBLAS API 封装
- 🧮 Tensor Core 示例与工具
- ⏱ CUDA Kernel 性能计时
- 📦 CUDA 二进制数据操作
- 🔧 常用 CUDA 配置封装
- 🖥 Header Only，无需额外编译

---

## 📂 项目结构

```text
cx_header_file
│
├── cx.h                     # 主头文件
├── cxbinio.h                # CUDA 二进制工具
├── cxconfun.h               # CUDA 常用函数封装
├── cxtetures.h              # CUDA Texture 相关工具
├── cxtimers.h               # CUDA 高精度计时器
├── CUBLA_TENSORCORE_CUH.cuh # Tensor Core/cuBLAS 实现
└── README.md
```

---

## 🔧 环境要求

- CUDA Toolkit 11.x / 12.x
- NVIDIA GPU
- GCC / Clang / MSVC
- C++17（推荐）

---

## 📥 使用方式

直接包含需要的头文件即可。

```cpp
#include "cx.h"
```

或者

```cpp
#include "CUBLA_TENSORCORE_CUH.cuh"
```

无需编译独立库。

---

## 🚀 示例

```cpp
#include "cx.h"

int main()
{
    // Initialize CUDA

    // Your CUDA code

    return 0;
}
```

---

## 📚 模块介绍

### cx.h

项目统一入口头文件。

包含公共宏定义、CUDA 初始化以及公共工具。

---

### cxconfun.h

CUDA 常用函数封装，例如：

- Error Check
- Device Query
- Grid 配置
- Kernel Launch Helper

---

### cxtimers.h

GPU 性能分析工具。

支持：

- CUDA Event Timer
- Kernel Execution Time
- Benchmark

---

### cxbinio.h

CUDA 二进制数据处理。

适用于：

- 数据读写
- Binary IO
- GPU 数据管理

---

### cxtetures.h

CUDA Texture Memory 工具。

提供 Texture Object 的快速创建与管理接口。

---

### CUBLA_TENSORCORE_CUH.cuh

本项目核心模块。

包含：

- cuBLAS API 封装
- Tensor Core GEMM 示例
- CUDA Matrix Multiply
- Tensor Core 优化实现

---

## 💡 项目特点

✔ Header Only

✔ 易于集成

✔ CUDA 原生开发

✔ 面向高性能计算

✔ Tensor Core 支持

✔ cuBLAS 简化调用

---

## 🎯 应用场景

- CUDA 学习
- GPU 编程
- HPC
- 深度学习框架开发
- Matrix Multiplication
- Tensor Core Benchmark

---

## 🤝 欢迎贡献

欢迎提交：

- Issue
- Pull Request
- CUDA 优化建议
- Tensor Core 新实现
- cuBLAS 新封装

---

## 📄 License

本项目采用 **MIT License**。

---

## 👤 作者

**DRChen114514**

GitHub：

https://github.com/DRChen114514

如果这个项目对你有所帮助，欢迎点一个 ⭐ Star！
