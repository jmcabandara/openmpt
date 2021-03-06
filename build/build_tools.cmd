@echo off

if not "x%1" == "xauto" (
	echo "WARNING: This script will unconditionally remove all files from the destination directories."
	pause
)

if "x%2" == "xnodownload" (
 set MPT_DOWNLOAD=no
)
if not "x%2" == "xnodownload" (
 set MPT_DOWNLOAD=yes
)

set MY_DIR=%CD%
set BATCH_DIR=%~dp0
cd %BATCH_DIR% || goto error
cd .. || goto error
goto main



:main



call build\scriptlib\unpack.cmd "include\genie" "build\externals\GENie-ec0a4a89d8dad4d251fc7195784a275c0c322a4d.zip" "GENie-ec0a4a89d8dad4d251fc7195784a275c0c322a4d" || goto error

xcopy /E /I /Y build\genie\genie\build\vs2017 include\genie\build\vs2017 || goto error

if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" (
 call build\auto\setup_vs2017.cmd || goto error
 cd include\genie\build\vs2017 || goto error
 devenv genie.sln /Upgrade || goto error
 msbuild genie.sln /target:Build /property:Configuration=Release;Platform=Win32 /maxcpucount /verbosity:minimal || goto error
 cd ..\..\..\.. || goto error
 goto geniedone
)
if exist "C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" (
 call build\auto\setup_vs2017.cmd || goto error
 cd include\genie\build\vs2017 || goto error
 devenv genie.sln /Upgrade || goto error
 msbuild genie.sln /target:Build /property:Configuration=Release;Platform=Win32 /maxcpucount /verbosity:minimal || goto error
 cd ..\..\..\.. || goto error
 goto geniedone
)

:geniedone

echo "ec0a4a89d8dad4d251fc7195784a275c0c322a4d" > include\genie\OpenMPT-version.txt



call build\scriptlib\unpack.cmd "include\premake" "build\externals\premake-5.0.0-alpha13-src.zip" "premake-5.0.0-alpha13" || goto error

if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" (
 call build\auto\setup_vs2017.cmd || goto error
 rem cd include\premake || goto error
 rem  nmake -f Bootstrap.mak windows MSDEV=vs2017 || goto error
 rem  bin\release\premake5 embed --bytecode || goto error
 rem  bin\release\premake5 --to=build/vs2017 vs2017 --no-curl --no-zlib --no-luasocket || goto error
 rem cd ..\.. || goto error
 cd include\premake\build\vs2017 || goto error
  msbuild Premake5.sln /target:Clean /property:Configuration=Release;Platform=Win32 /maxcpucount /verbosity:minimal || goto error
  msbuild Premake5.sln /target:Build /property:Configuration=Release;Platform=Win32 /maxcpucount /verbosity:minimal || goto error
 cd ..\..\..\.. || goto error
 goto premakedone
)
if exist "C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" (
 call build\auto\setup_vs2017.cmd || goto error
 rem cd include\premake || goto error
 rem  nmake -f Bootstrap.mak windows MSDEV=vs2017 || goto error
 rem  bin\release\premake5 embed --bytecode || goto error
 rem  bin\release\premake5 --to=build/vs2017 vs2017 --no-curl --no-zlib --no-luasocket || goto error
 rem cd ..\.. || goto error
 cd include\premake\build\vs2017 || goto error
  msbuild Premake5.sln /target:Clean /property:Configuration=Release;Platform=Win32 /maxcpucount /verbosity:minimal || goto error
  msbuild Premake5.sln /target:Build /property:Configuration=Release;Platform=Win32 /maxcpucount /verbosity:minimal || goto error
 cd ..\..\..\.. || goto error
 goto premakedone
)

goto error

:premakedone

echo "5.0.0-alpha13" > include\premake\OpenMPT-version.txt

goto ok

:ok
echo "All OK."
if "x%1" == "xauto" (
	exit 0
)
goto end
:error
echo "Error!"
if "x%1" == "xauto" (
	exit 1
)
goto end
:end
cd %MY_DIR%
pause
