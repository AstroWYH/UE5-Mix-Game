@echo off
REM 设置引擎路径和项目路径

set ENGINE_PATH="E:\uesrc\UnrealEngine\Engine\Binaries\Win64\UnrealEditor.exe"
set PROJECT_PATH="E:\uesrc\UnrealEngine\Samples\MyGame\MyGame.uproject"

@REM ENGINE_PATH="C:\nightgamer\ue5\ue52\Engine\Binaries\Win64\UnrealEditor.exe"
@REM set PROJECT_PATH="C:\nightgamer\ue5\ue52\Samples\UE5-Mix-Game\MyGame.uproject"

REM 启动 Lyra 项目，显示日志窗口
%ENGINE_PATH% %PROJECT_PATH%