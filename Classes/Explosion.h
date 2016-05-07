#ifndef Explosion_h__
#define Explosion_h__

#include "cocos2d.h"
#include "Resources.h"

USING_NS_CC;

class Explosion :public Ref
{
public:
	virtual bool init();
	virtual ParticleSystem* explode(Sprite* sprite, ContactTag type);
private:
	ParticleSystem* explosionBurningFlare();

	ParticleSystem* explosionRingFlare();
};
#endif // Explosion_h__
