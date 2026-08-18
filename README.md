# JK2D

## macOS 构建

需要安装 Xcode Command Line Tools、Homebrew 和 libpng：

```sh
xcode-select --install
brew install libpng pkg-config
make app
open JK2D.app
```

`make` 或 `make jk2d` 只生成可执行文件；`make app` 会生成包含 PNG 资源的
`JK2D.app`。运行 `make clean` 可删除构建产物。

当前渲染代码使用 macOS 仍兼容的 Legacy OpenGL；因此 macOS 目标不依赖 GLEW、
Win32、WGL 或 GDI。
