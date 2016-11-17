#pragma once
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

#include <GLFW/glfw3.h>


#include "Framerate.h"

namespace Biendeo::GameOff2016::Engine {
	// The main class for managing the game environment.
	class Engine {
		public:
		// Passes in the program input arguments and makes a new engine.
		Engine(int argc, char* argv[]);
		~Engine();

		// Starts the execution of the engine. This stops when the GLFW window is closed.
		void Run();

		private:
		Framerate* framerate;

		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;
		GLFWwindow* window;

		bool verbose;

		// Starts up GLFW.
		bool InitialiseGLFW();
		// Sets up the window used to display the game, with a valid OpenGL context.
		bool InitialiseWindow();

		// Draws the scene to the current active buffer.
		void DrawBuffer();
	};
}