#pragma once

#include "BulletBase.h"

class StraightBullet : public BulletBase
{
public:
	StraightBullet(VECTOR pos, VECTOR velocity);
	virtual ~StraightBullet();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;
};
