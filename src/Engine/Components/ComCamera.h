#pragma once

#include <Windows.h>
#include <GL/GL.h>

#include "../Component.h"

namespace Biendeo::GameOff2016::Engine::Components {
	class ComCamera : public Component {
		public:
		ComCamera();
		~ComCamera();

		void Awake() override;
		void LateUpdate() override;
		void OnActive() override;
		void OnDestroy() override;
		void OnDisable() override;
		void Start() override;
		void Update() override;

		protected:
		bool perspective;
		float fov;
	};
}