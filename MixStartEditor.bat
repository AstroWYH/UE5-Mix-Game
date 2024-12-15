@echo off
REM 设置引擎路径和项目路径

@REM set ENGINE_PATH="D:\ue\UnrealEngine\Engine\Binaries\Win64\UnrealEditor.exe"
@REM set PROJECT_PATH="D:\ue\UnrealEngine\Samples\MyGame\MyGame.uproject"

ENGINE_PATH="C:\nightgamer\ue5\ue52\Engine\Binaries\Win64\UnrealEditor.exe"
set PROJECT_PATH="C:\nightgamer\ue5\ue52\Samples\UE5-Mix-Game\MyGame.uproject"

REM 启动 Lyra 项目，显示日志窗口
%ENGINE_PATH% %PROJECT_PATH%