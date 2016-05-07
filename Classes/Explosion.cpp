#include "Explosion.h"

bool Explosion::init(){
	return true;
}

ParticleSystem* Explosion::explode(Sprite* sprite, ContactTag type){
	Vec2 position = sprite->getPosition();
	ParticleSystem* particleSystem = nullptr;
	switch (type)
	{
	case Enemy:
		particleSystem = explosionBurningFlare();
		sprite->getParent()->addChild(particleSystem, 10);
		particleSystem->setAutoRemoveOnFinish(true);
		particleSystem->setPosition(position);
		break;
	case Hero:
		particleSystem = explosionRingFlare();
		sprite->getParent()->addChild(particleSystem, 10);
		particleSystem->setAutoRemoveOnFinish(true);
		particleSystem->setPosition(position);
		break;
	}
	return particleSystem;
}

ParticleSystem* Explosion::explosionBurningFlare(){
	ParticleSystem* particleSystem = nullptr;
	particleSystem = ParticleSystemQuad::create(PATH_EFFECT1_PLIST);
	return particleSystem;
}

ParticleSystem* Explosion::explosionRingFlare(){
	ParticleSystem* particleSystem = nullptr;
	particleSystem = ParticleSystemQuad::create(PATH_EFFECT2_PLIST);
	return particleSystem;
}