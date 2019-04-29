#include "entity.hpp"

using PopHead::World::Entity::Entity;

Entity::Entity(PopHead::World::EntityType type, PopHead::Base::GameData* gameData, std::string name)
:mEntityType(type)
,mGameData(gameData)
,mName(name)
{

}

void Entity::input()
{
    for(auto it = mChildren.begin(); it != mChildren.end(); ++it)
        (*it)->input();
}

void Entity::update(sf::Time delta)
{
    for(auto it = mChildren.begin(); it != mChildren.end(); ++it)
        (*it)->update(delta);
}

void Entity::addChild(EntityPtr newChild)
{
    newChild->mParent = this;
    mChildren.emplace_back(std::move(newChild));
}

void Entity::removeChild(const std::string& name)
{
    for(auto it = mChildren.begin(); it != mChildren.end(); )
        if((*it)->getName() == name)
            it = mChildren.erase(it);
        else
            ++it;
}

void Entity::removeChild(unsigned int id)
{

}

void Entity::removeChild(PopHead::World::EntityType)
{

}

void Entity::setName(const std::string& name) { mName = name; }

auto Entity::getEntityType() const -> PopHead::World::EntityType { return mEntityType; }

auto Entity::getParent() const -> Entity& { return *mParent; }

auto Entity::getChild(std::string name) const -> Entity&
{
    for(auto const &child : mChildren){
        if(child->getName() == name)
            return *(child.get());
    }
}

auto Entity::getChildren() -> std::list< std::unique_ptr<Entity> >& { return mChildren; }

auto Entity::getName() const -> const std::string& { return mName; }
