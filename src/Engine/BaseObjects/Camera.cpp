#include "Camera.h"

#include <cmath>

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	Camera::Camera(Engine* engine) : Biendeo::GameOff2016::Engine::GameObject(engine) {
		if (!AddComponent(new Components::ComCamera(this))) {
			throw std::exception("A new camera couldn't create a component. Something's wrong.");
		}

		camera = GameObject::GetComponent<Components::ComCamera>();
	}

	Camera::~Camera() {

	}

	void Camera::SetupViewCamera() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		auto cameraPtr = std::shared_ptr<Components::ComCamera>(camera);
		// TODO: Use the screen ratio and not arbitrary numbers I chose.
		glFrustum(-0.1, 0.1, -0.075, 0.075, 0.1 / tan(cameraPtr->FOV() / 2.0f * atanf(1.0) * 4.0f / 180.0f), 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// TODO: Use the global transform rather than the local transform.
		glRotatef(-Transform().Rotate().x, 1.0f, 0.0f, 0.0f);
		glRotatef(-Transform().Rotate().y, 0.0f, 1.0f, 0.0f);
		glRotatef(-Transform().Rotate().z, 0.0f, 0.0f, 1.0f);
		glTranslatef(-Transform().Translate().x, -Transform().Translate().y, -Transform().Translate().z);
	}
}