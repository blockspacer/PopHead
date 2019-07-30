#pragma once

#include "interface.hpp"
#include "GameObjects/drawableGameObject.hpp"

/* Uncomment if you want to experiment   */
// #define GUI_TEST

namespace ph {

class GUI
{
public:
	GUI();
	~GUI();

	class Gui_drawer : public DrawableGameObject
	{
	public:
		Gui_drawer(GameData* gameData, std::string name, LayerID id)
			: DrawableGameObject(gameData, name, id)
			, mGui(nullptr)
		{

		}

		void init(GUI* gui) {
			mGui = gui;
		}

		void onCollision(DrawableGameObject&) {};

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			mGui->draw();
		}

		void update(sf::Time delta)
		{
			mGui->update(delta);
		}

		void move(sf::Vector2f delta, bool recursive = true)
		{
			mGui->move(delta);
		}

	private:
		GUI* mGui;
	};

	Widget* addInterface(const std::string& name);

	Widget* getInterface(const std::string& name);

	void move(const sf::Vector2f&);

	void deleteInterface(const std::string& name);

	void showInterface(const std::string& name);

	void hideInterface(const std::string& name);

	void swap(const std::string& first, const std::string& second);

	void moveUp(const std::string& name);

	void update(sf::Time deltaTime);

	void transform();

	void draw();

	void init(GameData* gamedata);

private:
	std::map<std::string, std::unique_ptr<Interface>> mInterfaceList;
	Gui_drawer* mGuiDrawer;
	GameData* mGameData;
};

}
