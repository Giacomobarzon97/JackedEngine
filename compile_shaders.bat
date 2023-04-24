echo "Compiling Shaders"

set pathToShaders=%~dp0JackedEngine\Backends\Shaders
set pathToCompiler=%~dp0Libraries\vulkan\Bin\glslc.exe

mkdir %pathToShaders%\CompiledShaders

for %%i in (%pathToShaders%\*) do  %pathToCompiler% %pathToShaders%\%%~nxi -o %pathToShaders%\CompiledShaders\%%~nxi.spv

echo %pathToShaders%
echo %pathToCompiler%