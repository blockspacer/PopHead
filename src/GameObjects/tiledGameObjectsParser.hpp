#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace ph {

class GameData;
class GameObject;
class Xml;

class TiledGameObjectsParser
{
public:
	TiledGameObjectsParser(GameData* gameData, GameObject& root);

	void parseFile(const std::string& filePath);

private:
	std::vector<Xml> getObjectTypeNodes();
	Xml findGameObjects(const Xml& mapFile);
	void loadObjects(const Xml& gameObjects);

	void loadEntrance(const Xml& entranceNode);
	void loadZombie(const Xml& zombieNode);
	void loadSpawner(const Xml& spawnerNode);
	void loadNpc(const Xml& npcNode);

	void loadParticlesSystem();
	void loadPlayer(const Xml& rootNode);

	sf::Vector2f getPositionAttribute(const Xml& gameObjectNode) const;
	sf::Vector2f getSizeAttribute(const Xml& gameObjectNode) const;

private:
	GameData* const mGameData;
	GameObject& mRoot;
};

}