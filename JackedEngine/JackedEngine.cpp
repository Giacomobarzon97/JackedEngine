#include "JackedEngine.h"
#include "Logic/SceneObjects/Cameras/PerspectiveCamera.h"
#include "Windows/GLFWWindow.h"
#include "Logic/Model.h"
#include "Logic/SceneObjects/RenderableObject.h"

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
}


void JackedEngine::mainLoop() {
	Model model = Model(
		{
			{{-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
		},
		{
			0, 1, 2, 2, 3, 0
		}
	);
	RenderableObject object= RenderableObject(model);

	while (!window->ShouldClose()) {
		window->PollEvents();
		renderer->DrawObject(object);
	}

	renderer->Reset();
}