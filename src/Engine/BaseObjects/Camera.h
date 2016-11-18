#pragma once

#include <memory>

#include "../GameObject.h"
#include "../Components/ComCamera.h"

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	class Camera : public GameObject {
		public:
		Camera(Engine& engine);
		~Camera();

		protected:
		Biendeo::GameOff2016::Engine::Components::ComCamera camera;
	};
}