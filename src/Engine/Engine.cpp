#include "Engine.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "BaseObjects/Camera.h"

namespace Biendeo::GameOff2016::Engine {
	// The callback method when GLFW errors. This just outputs a message to stderr.
	void GLFWErrorCallback(int error, const char* description) {
		std::cerr << "GLFW Error: " << description << "\n";
	}

	Engine::Engine(int argc, char* argv[]) {
		// Start off by turning the arguments into a vector.
		std::vector<std::string> arguments(argc);
		for (int i = 0; i < argc; ++i) {
			arguments[i] = argv[i];
		}

		// Set up the command-line variables.
		this->verbose = true;

		for (const std::string& arg : arguments) {
			// The /Q flag makes this program not print output.
			if (arg == "/Q") {
				verbose = false;
			}
		}

		// Then we set up our program.
		if (!InitialiseGLFW()) {
			abort();
		}

		if (!InitialiseWindow()) {
			abort();
		}

		// This prevents GLFW from swapping buffers until it's finished.
		glfwSwapInterval(1);

		// This establishes a framerate.
		// TODO: Custom based on argument?
		framerate = std::unique_ptr<Framerate>(new Framerate(vidmode->refreshRate));
	}

	Engine::~Engine() {
		glfwDestroyWindow(window);

		glfwTerminate();
	}

	void Engine::Run() {
		// TODO: Test GameObject stuff here.
		{
			using namespace BaseObjects;

			int count = 100000;

			std::vector<Camera*> bigCameraList(count);
			std::vector<std::weak_ptr<GameObject>> bigCameraList2(count);
			for (int i = 0; i < count; ++i) {
				bigCameraList.at(i) = new Camera(*this);

				Instantiate(bigCameraList.at(i));

				bigCameraList.at(i)->Name("Camera #" + std::to_string(i));

				//delete bigCameraList.at(i);

				bigCameraList2.at(i) = std::weak_ptr<GameObject>(gameObjects.at(bigCameraList.at(i)->ID()));

				if (i != 0 && bigCameraList.at(i - 1)->GetChildDepth() != GameObject::MAXIMUM_CHILD_DEPTH) {
					bigCameraList.at(i)->Parent(bigCameraList.at(i - 1)->GetWeakPointer());
				}
			}
			
			for (int i = 0; i < count; i += GameObject::MAXIMUM_CHILD_DEPTH + 1) {
				bigCameraList.at(i)->Destroy();
			}
		}

		while (!glfwWindowShouldClose(window)) {
			DrawBuffer();
			framerate->SleepToNextSwapBuffer();
			glfwSwapBuffers(window);
			if (verbose) std::cout << "Frame " << framerate->FrameCount() << "\n";
			framerate->UpdateDrawTimes();
			framerate->IncrementFrameCount();
			glfwPollEvents();
		}
	}

	bool Engine::InitialiseGLFW() {
		if (!glfwInit()) {
			if (verbose) std::cout << "GLFW couldn't initialize, something is wrong!\n";
			return false;
		} else {
			if (verbose) {
				int major, minor, revision;
				glfwGetVersion(&major, &minor, &revision);
				std::cout << "Using GLFW " << major << "." << minor << "." << revision << "\n";
			}

			// This associates the error callback function just so we can see GLFW errors.
			glfwSetErrorCallback(GLFWErrorCallback);

			return true;
		}
	}

	bool Engine::InitialiseWindow() {
		// Then we get monitor and video properties.
		monitor = glfwGetPrimaryMonitor();
		vidmode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		const bool borderlessFullscreen = false;

		const char* windowTitle = "Biendeo's Game Off 2016";

		// This is the point when you call glfwWindowHint for features.
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

		// Then, we create the window.
		if (borderlessFullscreen) {
			window = glfwCreateWindow(vidmode->width, vidmode->height, windowTitle, monitor, nullptr);
		} else {
			window = glfwCreateWindow(800, 600, windowTitle, nullptr, nullptr);
		}

		glfwMakeContextCurrent(window);

		if (verbose) {
			std::cout << "OpenGL Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION)) << "\n";
		}

		return true;
	}

	void Engine::DrawBuffer() {
		// TODO: Turn this into something good.
		glClear(GL_COLOR_BUFFER_BIT);
		static GLfloat value = 0.0f;
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(value, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, value, 0.0f);
		glVertex2f(-0.3f, 0.0f);
		glColor3f(0.0f, 0.0f, value);
		glVertex2f(0.3f, 0.0f);
		glEnd();
		value += 0.01f;
		if (value > 1.0f) {
			value -= 1.0f;
		}
	}

	bool Engine::Instantiate(GameObject* gameObject) {
		gameObject->ID(NewID());
		gameObjects.insert(std::pair<uint64_t, std::shared_ptr<GameObject>>(gameObject->ID(), std::shared_ptr<GameObject>(gameObject)));
		return true;
	}

	bool Engine::RemoveGameObject(GameObject& gameObject) {
		// TODO: Improve performance, this takes a while for decent numbers of objects.
		try {
			std::shared_ptr<GameObject> ptr = gameObjects.at(gameObject.ID());
			gameObjects.erase(ptr->ID());
			return true;
		} catch (std::out_of_range::exception& e) {
			std::cerr << "The engine tried to delete ID: " << gameObject.ID() << " but it didn't exist!\n";
			std::cerr << e.what() << "\n";
		}

		return false;
	}

	uint64_t Engine::NewID() {
		static uint64_t id = 1;
		return id++;
	}

	std::weak_ptr<GameObject> Engine::GetGameObjectWeakPointer(GameObject& gameObject) {
		return std::weak_ptr<GameObject>(gameObjects.at(gameObject.ID()));
	}
}