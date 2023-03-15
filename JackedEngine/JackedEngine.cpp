#include "JackedEngine.h"
#include "Scene/SceneObjects/Cameras/PerspectiveCamera.h"
#include "Scene/SceneObjects/RenderableObject.h"
#include "Windows/GLFWWindow.h"
#include <chrono>

const std::string JackedEngine::APP_NAME = "JackedEngine";

JackedEngine::JackedEngine()
{
	window = new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);

	camera = new PerspectiveCamera("Camera", *window, {2,2,2}, {-2,-2,-2});

	renderer = new Renderer(*window, *camera);

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete renderer;
	delete window;
	delete camera;
}


void JackedEngine::mainLoop() {
	std::vector<RenderableObject> objects;
	objects.push_back(RenderableObject(
			"Viking Room",
			"../Assets/Models/viking_room.obj",
			"../Assets/Textures/viking_room.png"
	));
	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();
	while (!window->ShouldClose()) {
		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevFrameTime).count();
		prevFrameTime = currentTime;
		objects[0].Rotate(0, 0, delta * 90);
		window->PollEvents();
		renderer->DrawObject(objects);
	}

	renderer->Reset();
	
}