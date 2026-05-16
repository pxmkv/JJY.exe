
# JJY.exe 叽叽歪病毒

> 一个早期 Windows 恶搞程序 / 病毒源码归档。  
> 本仓库仅用于历史留存、代码考古和安全教育，不建议编译、运行或传播其中的可执行文件。

## ⚠️ 安全警告

本仓库包含具有破坏性和干扰性的 Windows 系统修改逻辑，以及历史遗留的可执行文件。

请不要：

- 在真实电脑上运行 `JJY.exe` 或仓库中的任何可执行文件
- 将项目编译后发送给他人
- 尝试恢复、启用或改造其中的破坏性逻辑
- 在非隔离环境中测试相关行为

如需研究，请仅进行静态阅读。若确实需要做安全分析，应在一次性虚拟机、离线快照环境或专业恶意样本分析环境中进行。

## 项目简介

`JJY.exe` 是一个高中时期编写的 Windows 恶搞程序源码归档。项目主体使用 C/C++ 和 Win32 API 编写，包含窗口创建、资源释放、注册表修改、桌面资源替换、系统策略修改、全屏置顶显示等逻辑。

当前仓库更适合作为一个早期 Windows 恶搞程序的历史样本，而不是一个可运行软件项目。


## 仓库结构

```text
.
├── word.cpp              # 主程序源码，包含 Win32 入口和主要逻辑
├── StdAfx.cpp / .h       # 预编译头相关文件
├── Script1.rc            # Windows 资源脚本
├── resource.h            # 资源 ID 定义
├── word.dsp / word.dsw   # Visual C++ 6 / Microsoft Developer Studio 工程文件
├── 1.bmp ~ 5.bmp         # 程序使用的位图资源
├── icon1.ico             # 程序图标
├── file1.bin / file2.bin # 被嵌入的二进制资源
├── default1.bin          # manifest / 资源相关文件
├── JJY.exe               # 历史可执行文件，不建议运行
├── Debug/                # 历史调试构建产物
└── Release/              # 历史发布构建产物
```

## 行为概览

从源码静态阅读来看，历史逻辑大致包括以下类型的行为：

* 弹窗提示
* 释放内嵌资源到本地路径
* 修改 Windows 注册表策略
* 禁用部分系统工具入口
* 修改桌面壁纸和文件图标
* 隐藏部分桌面 / 系统图标
* 尝试复制自身到系统目录
* 显示全屏置顶窗口和位图动画
* 限制鼠标位置
* 创建恶搞文本文件
* 在特定流程中触发系统重启

这些行为属于典型的恶搞型 / 破坏型 Windows 程序特征。仓库保留这些代码仅用于历史记录和静态分析。

## 主要文件说明

### `word.cpp`

项目的主源码文件，包含 Win32 程序入口和主要逻辑。

当前入口函数在弹出提示框后直接返回，因此后续逻辑在当前源码中不会继续执行。

### `Script1.rc`

Windows 资源脚本文件，用于声明程序中使用的图标、位图和二进制资源。

### `resource.h`

资源 ID 定义文件，与 `Script1.rc` 配合使用。

### `word.dsp` / `word.dsw`

Visual C++ 6 / Microsoft Developer Studio 时代的工程文件，属于较老的 Windows C++ 工程格式。

### `1.bmp` ~ `5.bmp`

程序中使用的位图资源。

### `icon1.ico`

程序图标资源。

### `file1.bin` / `file2.bin` / `default1.bin`

历史代码中引用的二进制资源文件。

### `JJY.exe`

历史构建出的可执行文件。
不建议运行。

## 不提供的内容

为了避免误用，本仓库不提供：

* 构建步骤
* 运行步骤
* 样本复现指南
* 绕过杀毒软件的说明
* 修改后重新启用破坏逻辑的方法
* 在真实系统中测试该程序的教程

## 适合的研究方向

这个项目可以作为以下主题的静态阅读材料：

* 早期 Win32 API 编程风格
* Visual C++ 6 时代的工程结构
* Windows 资源脚本和嵌入资源
* 恶搞程序常见行为模式
* 注册表策略对系统行为的影响
* Windows 桌面环境和系统策略接口
* 为什么此类程序不应在真实环境中运行

## 历史背景

这是一个早期个人项目，原始 README 中提到它是高中时期和朋友一起写的恶搞程序源码。现在公开仓库主要作为历史留存。

相关链接：

* Bilibili 主页：[https://space.bilibili.com/15094572](https://space.bilibili.com/15094572)

## Repository Description 建议

如果需要修改 GitHub 仓库简介，可以使用：

```text
Archived Win32 prank/malware source code from high school. For static analysis and historical preservation only. Do not run.
```

或者更短一些：

```text
Archived Win32 prank program source code. Static analysis only. Do not run.
```

## 免责声明

本仓库中的代码和二进制文件可能对系统造成干扰或破坏。请不要在真实设备上运行。

任何由运行、修改、传播或复现该程序造成的后果，均由操作者自行承担。

本项目仅用于历史归档、静态分析和安全教育。

```
```
