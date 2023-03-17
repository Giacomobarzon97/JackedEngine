echo "Compiling Shaders"

%~dp0/Libraries/vulkan/Bin/glslc.exe %~dp0/JackedEngine/Rendering/Shaders/object.vert -o %~dp0/JackedEngine/Rendering/Shaders/object.vert.spv
%~dp0/Libraries/vulkan/Bin/glslc.exe %~dp0/JackedEngine/Rendering/Shaders/object.frag -o %~dp0/JackedEngine/Rendering/Shaders/object.frag.spv