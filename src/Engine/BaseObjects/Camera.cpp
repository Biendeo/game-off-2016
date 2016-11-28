#include "Camera.h"

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	Camera::Camera(Engine& engine) : Biendeo::GameOff2016::Engine::GameObject(engine) {
		if (!AddComponent(new Components::ComCamera())) {
			throw std::exception("A new camera couldn't create a component. Something's wrong.");
		}

		camera = GetComponent<Components::ComCamera>();
	}

	Camera::~Camera() {

	}

	void Camera::SetupViewCamera() {

	}
}