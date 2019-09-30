#pragma once
#include "character.h"
class World
{
public:
	static void AddToWorld(Character* CharacterToAdd) { Characters.push_back(CharacterToAdd); }
	static std::vector<Character*> Characters;
};

std::vector<Character*> World::Characters { nullptr };