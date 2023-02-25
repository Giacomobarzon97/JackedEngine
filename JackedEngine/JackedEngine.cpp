#include "JackedEngine.h"
#include "Logic/SceneObjects/Cameras/PerspectiveCamera.h"
#include "Windows/GLFWWindow.h"
#include "Logic/Model.h"
#include "Logic/SceneObjects/RenderableObject.h"
#include <chrono>

const std::string JackedEngine::APP_NAME = "JackedEngine";

JackedEngine::JackedEngine()
{
	window = new GLFWWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);

	camera = new PerspectiveCamera(*window, {2,2,2}, {-2,-2,-2});

	renderer = new Renderer(*window, *camera);

	mainLoop();
}

JackedEngine::~JackedEngine() {
	delete renderer;
	delete window;
	delete camera;
}


void JackedEngine::mainLoop() {
	Model model = Model(
		{
			{{-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

			{{-0.5f, -0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		},
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		}
	);
	
	RenderableObject object = RenderableObject(model);
	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();
	while (!window->ShouldClose()) {
		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevFrameTime).count();
		prevFrameTime = currentTime;
		object.Rotate(0, 0, delta * 90);
		window->PollEvents();
		renderer->DrawObject(object);
	}

	renderer->Reset();
	
}