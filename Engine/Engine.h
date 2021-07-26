#pragma once
// Systems
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"

// Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

// Graphics
#include "Graphics/Shape.h"

// Framework
#include "Framework/EventSystem.h"
#include "Framework/ResourceSystem.h"

// Objects
#include "Base/Scene.h"
#include "Base/Actor.h"

#include "core.h"
#include <vector>
#include <memory>
#include <algorithm>

namespace PhoenixEngine
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics graphics);

		template <typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}