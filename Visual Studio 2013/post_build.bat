REM post_build.bat
REM Created on 24/08/2015.
REM Copyright (c) 2015 Vraiment. All rights reserved.

@ECHO OFF

REM Get the value of the output dir
SET OUTPUT_DIR=%~1
IF NOT "%OUTPUT_DIR%" == "" (
    ECHO output dir: %OUTPUT_DIR%
) ELSE (
    ECHO No output dir was given
    EXIT /B 1
)

REM Get the value of the DLLs dir
SET INPUT_DLL_DIR=%~2
IF NOT "%INPUT_DLL_DIR%" == "" (
    ECHO input dll dir: %INPUT_DLL_DIR%
) ELSE (
    ECHO No input dll dir was given
    EXIT /B 1
)

REM Get the value of the resources dir
SET INPUT_RES_DIR=%~3
IF NOT "%INPUT_RES_DIR%" == "" (
    ECHO input resources dir: %INPUT_RES_DIR%
) ELSE (
    ECHO No input resources dir was given
	EXIT /B 1
)

REM Copy the DLLs
COPY "%INPUT_DLL_DIR%"*.DLL "%OUTPUT_DIR%"

REM Define resources directories
SET OUTPUT_RES_DIR=%OUTPUT_DIR%

REM Create the directories if they don't exists
IF NOT EXIST "%OUTPUT_RES_DIR%" (
    MKDIR "%OUTPUT_RES_DIR%"
    ECHO Created output resources dir
)
IF NOT EXIST "%OUTPUT_RES_DIR%"fonts (
    MKDIR "%OUTPUT_RES_DIR%"fonts
    ECHO Created output fonts dir
)
IF NOT EXIST "%OUTPUT_RES_DIR%"maps (
    MKDIR "%OUTPUT_RES_DIR%"maps
    ECHO Created output maps dir
)
IF NOT EXIST "%OUTPUT_RES_DIR%"textures (
    MKDIR "%OUTPUT_RES_DIR%"textures
    ECHO Created output textures dir
)

REM Perform the copies of resources
COPY "%INPUT_RES_DIR%"* "%OUTPUT_RES_DIR%"
COPY "%INPUT_RES_DIR%"fonts\* "%OUTPUT_RES_DIR%"fonts\
COPY "%INPUT_RES_DIR%"maps\* "%OUTPUT_RES_DIR%"maps\
COPY "%INPUT_RES_DIR%"textures\* "%OUTPUT_RES_DIR%"textures\
