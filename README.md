# C++ 实验源码

| 目录 | 内容 | 原始阶段提交 |
| --- | --- | --- |
| `experiment0/` | Hello World 与 CMake 构建 | `542a7df` |
| `experiment1/` | 车辆初始化、移动与左右转向 | `825e5b7` |
| `experiment2/` | 命令类重构与 F 加速指令 | `56f45f3` |
| `experiment3/` | 命令解耦、表驱动与 B 倒车指令 | `ba45cfd` |
| `experiment4/` | 动作编排、掉头、跑车与 bus | `d94ec2c` |

`third_party/googletest/` 是实验1至4共用的测试依赖。实验0的 Hello World 工程原来在 `cpp-experiment0`，现已归入本仓库的 `experiment0/`，原始提交保留在 Git 历史中。实验1至4的目录取自对应的阶段提交，只调整了构建文件中的头文件和测试依赖路径，使各阶段可以从总目录构建。实验4原有的五次阶段提交仍可查看。

## 构建与测试

使用支持 C++17 的工具链。课程的 Windows 构建环境为 MinGW-w64。将其 `bin` 加入终端的 `PATH` 后，在 `cpp-training` 根目录运行以下命令。默认选择实验4。

```powershell
cmake -S . -B build-4 -G "MinGW Makefiles" -DEXPERIMENT=4
cmake --build build-4
ctest --test-dir build-4 --output-on-failure
```

其他实验将 `4` 换成对应编号，并为每个实验使用独立构建目录。实验0构建目标为 `HelloWorld`，构建后可以直接运行 `build-0/experiment0/HelloWorld.exe`。实验1至4使用 `ctest` 或直接运行相应构建目录下 `experimentN/tests/training_main.exe` 中的测试程序。
