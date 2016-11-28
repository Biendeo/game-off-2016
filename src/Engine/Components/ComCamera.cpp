#include "ComCamera.h"

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