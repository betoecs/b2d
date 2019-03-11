#ifndef B2D_CORE_ENTITY_HPP
#define B2D_CORE_ENTITY_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace b2d
{

////////////////////////////////////////
// A node in a tree structure. It's transformable
// and drawable. It can has a parent and children
// and a collision body.
////////////////////////////////////////
class Entity : public sf::Drawable, public sf::Transformable
{
public:
	///// Constructors and destructors

	////////////////////////////////////////
	// Default constructor
	////////////////////////////////////////
	Entity();

	////////////////////////////////////////
	// Destroys its children too.
	////////////////////////////////////////
	virtual ~Entity();

	///// Drawable relathed members

	////////////////////////////////////////
	// Indicates whether the entity is visible
	// or not.
	////////////////////////////////////////
	bool isVisible() const;

	////////////////////////////////////////
	// Sets whether the entity is visible or not.
	////////////////////////////////////////
	void setVisible(bool visible);

	////////////////////////////////////////
	// Gets the z-index of the entity.
	////////////////////////////////////////
	int getZIndex() const;

	////////////////////////////////////////
	// Sets the z-index of the entity. If the
	// entity has parent, it's placed according
	////////////////////////////////////////
	// to its new z-index
	void setZIndex(int zIndex);

	///// Update relathed members

	////////////////////////////////////////
	// Indicates whether the entity is paused
	// or not.
	////////////////////////////////////////
	bool isPaused() const;

	////////////////////////////////////////
	// Sets whether the entity is paused or not.
	////////////////////////////////////////
	void setPause(bool paused);

	////////////////////////////////////////
	// Override this method to define your
	// entity's behaviour. *frameTime* represents
	// the time of the current frame in millisenconds
	////////////////////////////////////////
	virtual void onUpdate(unsigned int frameTime);

	////////////////////////////////////////
	// Calls to onUpdate() and to all its
	// children to update.
	//
	// **Note**: This method works only if
	// the entity is not paused.
	////////////////////////////////////////
	void update(unsigned int frameTime);

	///// Tree node relathed methods

	////////////////////////////////////////
	// Indicates whether the entity has parent
	// or not.
	////////////////////////////////////////
	bool hasParent() const;

	////////////////////////////////////////
	// Adds an entity as child of this. If it
	// has parent, the addition is cancelled.
	//
	// **Returns** true if the entity was added.
	////////////////////////////////////////
	bool addChild(Entity *entity);

protected:
	///// Drawable relathed members

	////////////////////////////////////////
	// Override this method to define how your
	// entity is going to be drawn.
	////////////////////////////////////////
	virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;

private:
	///// Drawable relathed members

	////////////////////////////////////////
	// Combines its transform with *states*'
	// transform and calls to onDraw(). Also,
	// calls to all its children to draw.
	//
	// **Note**: This method works only if
	// the entity is visible.
	////////////////////////////////////////
	void draw(sf::RenderTarget &target, sf::RenderStates states) const final;

	///// Tree node relathed methods

	////////////////////////////////////////
	// Sets the parent of the entity. It does not
	// verifies that the entity to be added does
	// not have parent.
	////////////////////////////////////////
	void setParent(Entity *entity);

	////////////////////////////////////////
	// Places an entity into the children vector
	// taking into account its z-index.
	////////////////////////////////////////
	void placeChild(Entity *entity);

	////////////////////////////////////////
	// Removes a child from the children vector.
	// The child is not deleted nor released.
	////////////////////////////////////////
	void removeFromChildren(Entity *child);

	///// Drawable relathed members

	////////////////////////////////////////
	// Determines whether the entity and its
	// children must be drawn or not. **true**
	// by default.
	//
	// **Relathed methods:**
	// + isVisible()
	// + setVisible()
	////////////////////////////////////////
	bool visible;

	////////////////////////////////////////
	// Determines the drawing and updating order
	// between this entity and its siblings.
	// If the value between 2 entities are
	// the same, the order in that both were
	// added as child is used. **0** by default.
	//
	// **Related methods:**
	// + getZIndex()
	// + setZIndex()
	////////////////////////////////////////
	int zIndex;

	///// Update relathed members

	////////////////////////////////////////
	// Determines if an entity (and its children)
	// are going to be updated or not. **false**
	// by default.
	//
	// **Related methods:**
	// + isPaused()
	// + setPaused()
	////////////////////////////////////////
	bool paused;

	///// Tree node relathed members

	////////////////////////////////////////
	// Parent of the entity. It's set automatically
	// when the entity is added as child
	// of another. **nullptr** by default.
	//
	// **Related methods:**
	// + hasParent()
	// + setParent()
	////////////////////////////////////////
	Entity *parent;

	////////////////////////////////////////
	// Children of the entity. Each geometry-related
	// method affects directly these entities.
	//
	// **Relathed methods:**
	// + addChild()
	////////////////////////////////////////
	std::vector <Entity *> children;
};

}

#endif // B2D_CORE_ENTITY_HPP