echo "Compiling Shaders"

%~dp0/Libraries/vulkan/Bin/glslc.exe %~dp0/JackedEngine/Rendering/Shaders/default.vert -o %~dp0/JackedEngine/Rendering/Shaders/default.vert.spv
%~dp0/Libraries/vulkan/Bin/glslc.exe %~dp0/JackedEngine/Rendering/Shaders/default.frag -o %~dp0/JackedEngine/Rendering/Shaders/default.frag.spv