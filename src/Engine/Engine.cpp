#include "Engine.h"

#include <iostream>
#include <string>
#include <vector>

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
		framerate = new Framerate(vidmode->refreshRate);
	}

	Engine::~Engine() {
		if (framerate != nullptr) {
			delete framerate;
		}

		glfwDestroyWindow(window);

		glfwTerminate();
	}

	void Engine::Run() {
		GLfloat value = 0.0f;

		while (!glfwWindowShouldClose(window)) {
			DrawBuffer();
			framerate->SleepToNextSwapBuffer();
			glfwSwapBuffers(window);
			//if (verbose) std::cout << "Frame " << framerate->FrameCount() << "\n";
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
}