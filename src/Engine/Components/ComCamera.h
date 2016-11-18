#pragma once

#include <Windows.h>
#include <GL/GL.h>

#include "../Component.h"

namespace Biendeo::GameOff2016::Engine::Components {
	class ComCamera : public Component {
		public:
		ComCamera();
		~ComCamera();

		protected:
		bool perspective;
		float fov;
	};
}