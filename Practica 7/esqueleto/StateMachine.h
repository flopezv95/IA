#pragma once

class SM
{
	enum States 
	{ 
		eIdle, 
		eAttack,
		eAlarm,
		eHit,
		eDead,
		eRunAway 
	};

public:
	SM();
	void Update();
private:
	void Idle(); 
	void Attack(); 
	void Runaway();
	void Alarm();
	void Hit();
	void Dead();
};