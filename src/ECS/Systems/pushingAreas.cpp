#include "pushingAreas.hpp"

#include "ECS/Components/objectsComponents.hpp"
#include "ECS/Components/physicsComponents.hpp"

namespace ph::system {

void PushingAreas::update(float dt)
{
	auto pushingAreasView = mRegistry.view<component::PushingArea, component::BodyRect>();
	auto kinematicObjects = mRegistry.view<component::KinematicCollisionBody, component::BodyRect, component::Velocity>();

	for (auto pushingArea : pushingAreasView)
	{
		const auto& [pushingAreaDetails, areaBody] = pushingAreasView.get<component::PushingArea, component::BodyRect>(pushingArea);

		for (auto kinematicObject : kinematicObjects)
		{
			auto& [kinematicObjectBody, objectVelocity] = kinematicObjects.get<component::BodyRect, component::Velocity>(kinematicObject);
			if (areaBody.rect.contains(kinematicObjectBody.rect.getCenter()))
			{
				objectVelocity.dx += pushingAreaDetails.pushForce.x;
				objectVelocity.dy += pushingAreaDetails.pushForce.y;
			}
		}
	}
}

}