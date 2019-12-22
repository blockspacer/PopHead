#pragma once

#include "ECS/system.hpp"
#include <SFML/System/Vector2.hpp>

namespace ph {

class AIManager;

namespace system {

	class PlayerMovementInput : public System
	{
	public:
		PlayerMovementInput(entt::registry&, AIManager&);

		void update(float dt) override;
		void onEvent(const ActionEvent& event) override;

	private:
		bool isPlayerWithoutControl();
		sf::Vector2f getPlayerDirection() const;
		void updateInputFlags();
		void updateAnimationData();
		void setPlayerFaceDirection(const sf::Vector2f faceDirection) const;
		void setFlashLightDirection(const sf::Vector2f faceDirection) const;
		void updateGunAttackInput();
		void updateMeleeAttackInput();

	private:
		AIManager& mAIManager;
		bool mUp;
		bool mDown;
		bool mLeft;
		bool mRight;
	};
}

}
