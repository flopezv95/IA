#pragma once

class Character;

enum Status 
{ eInvalid, 
  eSuccess, 
  eFail,
  eRunning, 
};

class Behavior 
{ 
protected: 
	Status update(); 
	void onEnter(); 
	void onExit(); 
public: 
	Behavior(Character* owner);
	Status tick(); 
private: 
	Status m_Status; 
	Character* m_Owner;
};