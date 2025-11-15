# GDB 配置文件 - 自动跳过标准库和系统代码

# 跳过所有标准库头文件
skip -gfi /usr/include/c++/*
skip -gfi /usr/include/*

# 跳过 GCC 调试源码目录
skip -gfi /usr/src/debug/*
skip -gfi */gcc-build/*
skip -gfi */libstdc++*/*

# 跳过特定的标准库函数和模板
skip -rfu ^std::
skip -rfu ^__gnu_cxx::

# 美化打印设置
set print pretty on
set print array on
set print array-indexes on
set print elements 0

# 禁用 debuginfod（避免网络延迟）
set debuginfod enabled off

# 汇编风格设置为 Intel
set disassembly-flavor intel

# 启用历史记录
set history save on
set history size 10000
set history filename ~/.gdb_history

# 显示更多信息
set verbose off
set confirm off
