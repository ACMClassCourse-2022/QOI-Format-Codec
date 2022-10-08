# 本地测试

【**此部分并无需要额外实现的代码**，仅供大家测试、熟悉IDE和命令行使用】

本项目实际上借助您编写的 `qoi` 编码解码器，实现了一个命令行图片格式转换小应用。

它可以实现 `qoi(rgb) <-> ppm` 和 `qoi(rgba) <-> pam` 的图片格式转换。

> **PPM** 全称 portable pixmap format，是一种**人类可读**的图片格式，其RGB像素信息直接以十进制数值的形式写在图片文件当中。
> 
> **PAM** 全称 portable arbitrary map，同样是一种**人类可读**的图片格式，我们用它来保存RGBA图片的像素信息。值得注意的是，在 PAM 格式中四个色彩通道信息以 ARGB 的顺序排列。
> 
> **您可以直接用文本编辑器打开 `.ppm` 或 `.pam` 格式的图片**，它们能帮助您检查您的解码结果是否正确。您也可以自己手动构造这两种格式的图片，用来测试编码结果是否符合预期。
> 
> 有关 PPM 和 PAM 格式的更多信息，详见 [PPM](https://en.wikipedia.org/wiki/Netpbm) 和 [PAM](https://netpbm.sourceforge.net/doc/pam.html)

## A. 使用Clion

### 1. 构建项目

在顶端菜单栏中选择 Build > Install

<img src="assets/install-app.jpg" alt="" height=200>

如果构建正常，此时在项目根目录中会出现一个名为 `conv` 的可执行文件，那就是我们的图片格式转换器。

> `qoi.h` 的内容出现改动时需要重新构建项目

### 2. 使用命令行应用转换图片格式

 点击底端菜单栏中的 Terminal 一项，在弹出的窗口中新建wsl命令行窗口

<img src="assets/wsl-terminal.jpg" alt="" height=150>

在wsl命令行中运行 `./conv ...` 来使用应用

运行 `./conv -h` 查看帮助信息

### 3. 检查转换结果是否正确

您可以使用 Clion 自带的文本比较功能来判断转换结果是否正确

右键点击您的转换输出文件比，选择 Compare With...

<img src="assets/compare.jpg" alt="" height=300>

在弹出的窗口中选中样例数据中相应的文件。如果出现了 `Contents are identical` 的提示信息，那么恭喜您，您的转换结果是正确的；否则 Clion 会提示您不一致内容的所在位置，您可以根据此调试自己的代码。

> **【以下是可选的设置内容】**
> 
> Clion 默认将 `.ppm` 与 `.pam` 以图片格式打开，但我们可以通过调整 File Types 设置来以文本格式查看它们。
> 
> 在顶端菜单栏中选择 File > Settings...
> 
> <img title="" src="assets/setting.jpg" alt="" height="200">
> 
> 在弹出的设置窗口中选择 Editor > File Types
> 
> 在 Recognized File Types 中选择 Text
> 
> <img src="assets/reg-file-type.jpg" alt="" height=200>
> 
> 在右侧的 File name patterns 中新增 `*.ppm` 和 `*.pam` 两项
> 
> <img src="assets/name-pattern.jpg" alt="" height=150>
> 
> 这里可能会会有类型冲突的提示，选择 Reassign 即可

## B. 使用命令行

### 1. 编译项目

在项目根目录运行 `g++ main.cpp -o conv` 编译程序

### 2. 使用命令行应用转换图片格式

与 A.2 使用方法相同，不再赘述

### 3. 检查转换结果是否正确

运行 `diff path/to/your/file path/to/std/file` 进行文件比较，没有输出表示文件没有差异
