#pragma once

namespace Biendeo::GameOff2016::Engine {
	class Component {
		public:
		// Gets called before Start when the object is created.
		virtual void Awake() = 0;
		// Gets called after Update every framew.
		virtual void LateUpdate() = 0;
		// Gets called when the object is made active.
		virtual void OnActive() = 0;
		// Gets called when the object is destroyed.
		virtual void OnDestroy() = 0;
		// Gets called when the object is made inactive.
		virtual void OnDisable() = 0;
		// Gets called when the object is created.
		virtual void Start() = 0;
		// Gets called every frame.
		virtual void Update() = 0;
	};
}