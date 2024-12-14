@echo off
REM 设置引擎路径和项目路径
set ENGINE_PATH="D:\ue\UnrealEngine\Engine\Binaries\Win64\UnrealEditor.exe"
set PROJECT_PATH="D:\ue\UnrealEngine\Samples\MyGame\MyGame.uproject"

REM 启动 Lyra 项目，显示日志窗口
%ENGINE_PATH% %PROJECT_PATH%