#pragma once

#include "glm/glm.hpp"

#include "../Component.h"

namespace Biendeo::GameOff2016::Engine::Components {
	class Transform : public Component {
		public:
		Transform();
		~Transform();

		glm::vec3& Translate();
		glm::vec3& Rotate();
		glm::vec3& Scale();

		void Awake() override;
		void LateUpdate() override;
		void OnActive() override;
		void OnDestroy() override;
		void OnDisable() override;
		void Start() override;
		void Update() override;

		protected:
		glm::vec3 translate;
		// Convert this to a quaternion vec4 later.
		glm::vec3 rotate;
		glm::vec3 scale;
	};
}