#include "ComCamera.h"

#include "../GameObject.h"

namespace Biendeo::GameOff2016::Engine::Components {
	ComCamera::ComCamera(GameObject* gameObject) : Component(gameObject) {
		perspective = true;
		fov = 75.0f;
	}

	ComCamera::~ComCamera() {

	}

	bool ComCamera::Perspective() {
		return perspective;
	}

	bool ComCamera::Perspective(bool perspective) {
		this->perspective = perspective;
		return perspective;
	}

	float ComCamera::FOV() {
		return fov;
	}

	float ComCamera::FOV(float fov) {
		this->fov = fov;
		return fov;
	}

	void ComCamera::SetupViewCamera() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// TODO: Use the screen ratio and not arbitrary numbers I chose.
		glFrustum(-0.1, 0.1, -0.075, 0.075, 0.1 / tan(FOV() / 2.0f * atanf(1.0) * 4.0f / 180.0f), 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// TODO: Use the global transform rather than the local transform.
		glRotatef(-gameObject->Transform().Rotate().x, 1.0f, 0.0f, 0.0f);
		glRotatef(-gameObject->Transform().Rotate().y, 0.0f, 1.0f, 0.0f);
		glRotatef(-gameObject->Transform().Rotate().z, 0.0f, 0.0f, 1.0f);
		glTranslatef(-gameObject->Transform().Translate().x, -gameObject->Transform().Translate().y, -gameObject->Transform().Translate().z);
	}

	void ComCamera::Awake() {

	}

	void ComCamera::LateUpdate() {

	}

	void ComCamera::OnActive() {

	}

	void ComCamera::OnDestroy() {

	}

	void ComCamera::OnDisable() {

	}

	void ComCamera::Start() {

	}

	void ComCamera::Update() {
		
	}
}