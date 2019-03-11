#include <b2d/Core/Entity.hpp>

namespace b2d
{
////////////////////////////////////////
Entity::Entity() : parent(nullptr), visible(true), zIndex(0), paused(false)
{
}

////////////////////////////////////////
Entity::~Entity()
{
	for (auto *child : this->children)
		delete child;
}

////////////////////////////////////////
bool Entity::isVisible() const
{
	return this->visible;
}

////////////////////////////////////////
void Entity::setVisible(bool visible)
{
	this->visible = visible;
}

////////////////////////////////////////
int Entity::getZIndex() const
{
	return this->zIndex;
}

////////////////////////////////////////
void Entity::setZIndex(int zIndex)
{
	if (this->zIndex == zIndex)
		return;

	this->zIndex = zIndex;

	if (this->parent)
	{
		this->parent->removeFromChildren(this);
		parent->placeChild(this);
	}
}

////////////////////////////////////////
void Entity::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
}

////////////////////////////////////////
void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (! this->visible)
		return;

	states.transform *= this->getTransform();
	this->onDraw(target, states);

	for (auto *child : this->children)
		child->draw(target, states);
}

////////////////////////////////////////
bool Entity::isPaused() const
{
	return this->paused;
}

////////////////////////////////////////
void Entity::setPause(bool paused)
{
	this->paused = paused;
}

////////////////////////////////////////
void Entity::onUpdate(unsigned int frameTime)
{
}

////////////////////////////////////////
void Entity::update(unsigned int frameTime)
{
	if (this->paused)
		return;

	this->onUpdate(frameTime);

	for (auto *child : this->children)
		child->update(frameTime);
}

////////////////////////////////////////
bool Entity::hasParent() const
{
	return this->parent;
}

////////////////////////////////////////
bool Entity::addChild(Entity *entity)
{
	if (! entity || entity->hasParent())
		return false;

	entity->setParent(this);
	this->placeChild(entity);
	return true;
}

////////////////////////////////////////
void Entity::setParent(Entity *entity)
{
	this->parent = entity;
}

////////////////////////////////////////
void Entity::placeChild(Entity *entity)
{
	for (auto it = this->children.begin(); it != this->children.end(); ++it)
	{
		if (entity->zIndex < (*it)->zIndex)
		{
			this->children.insert(it, entity);
			return;
		}
	}
}

////////////////////////////////////////
void Entity::removeFromChildren(Entity *child)
{
	for (auto it = this->children.begin(); it != this->children.end(); ++it)
	{
		if (child == (*it))
		{
			this->children.erase(it);
			return;
		}
	}
}

}