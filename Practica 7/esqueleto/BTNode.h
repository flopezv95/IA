#pragma once

class Character;

enum Status
{
	eInvalid,
	eSuccess,
	eFail,
	eRunning,
};

class BTNode
{
public:
	virtual Status tick() 
	{ 
		return Status::eInvalid;
	}
	virtual void SetOwner(Character* newOwner) 
	{
		m_Owner = newOwner;
	}
	Status GetStatus() { return m_Status; }
	void SetStatus(Status newStatus) { m_Status = newStatus; }

protected:
	Character* m_Owner;
	Status m_Status = Status::eInvalid;
};