#include "collisionBody.hpp"
#include "bodyType.hpp"

using PopHead::Physics::CollisionBody;

CollisionBody::CollisionBody(sf::FloatRect rect, float mass, PopHead::Physics::BodyType bodyType,
							 PopHead::World::Entity::Object* const owner, PopHead::Base::GameData* gameData)
:mRect(rect)
,mMass(mass)
,mPreviousPosition(rect.left, rect.top)
,mOwner(owner)
,mBodyType(bodyType)
,mCollisionDebugRect(gameData, rect, this)
,mGameData(gameData)
{
	switch (bodyType)
	{
	case PopHead::Physics::BodyType::staticBody:
		gameData->getPhysicsEngine().addStaticBody(this);
		break;

	case PopHead::Physics::BodyType::kinematicBody:
		gameData->getPhysicsEngine().addKinematicBody(this);
		break;
	}
}

CollisionBody::~CollisionBody()
{
	switch (mBodyType)
	{
	case PopHead::Physics::BodyType::staticBody:
		mGameData->getPhysicsEngine().removeStaticBody(this);
		break;

	case PopHead::Physics::BodyType::kinematicBody:
		mGameData->getPhysicsEngine().removeKinematicBody(this);
		break;
	}
}

void CollisionBody::move(sf::Vector2f velocity)
{
	mVelocity = velocity;
	mRect.left += velocity.x;
	mRect.top += velocity.y;
	mCollisionDebugRect.move(velocity);
}

void CollisionBody::setPosition(sf::Vector2f position)
{
	mRect.left = position.x;
	mRect.top = position.y;
	mCollisionDebugRect.setPosition(position);
}

void CollisionBody::actionsAtTheEndOfPhysicsLoopIteration()
{
	setPreviousPositionToCurrentPosition();
	updateOwnerPosition();
	mVelocity = sf::Vector2f();
}

void CollisionBody::setPreviousPositionToCurrentPosition()
{
	mPreviousPosition.x = mRect.left;
	mPreviousPosition.y = mRect.top;
}

void CollisionBody::updateOwnerPosition()
{
	mOwner->setPosition(sf::Vector2f(mRect.left, mRect.top), false);
}

void CollisionBody::updatePush(sf::Time delta)
{
	if (mForceVector == sf::Vector2f())
		return;

    move(mForceVector * delta.asSeconds());
    mForceVector -= mForceVector * delta.asSeconds() * 1.5f;

	if (mForceVector.x < 40 && mForceVector.x > -40 && mForceVector.y < 40 && mForceVector.y > -40) {
		mForceVector = sf::Vector2f(0, 0);
	}
}