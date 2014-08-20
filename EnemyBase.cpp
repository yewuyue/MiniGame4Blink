#include "EnemyBase.h"

EnemyBase::EnemyBase() : pointCounter(0), _animation(NULL), pointsVector(NULL), runSpeed(0), maxHp(0), currHp(0)
{
}

EnemyBase::~EnemyBase()
{
}

bool EnemyBase::init()
{
	if (!Sprite::init()) {
		return false;
	}

	return true;
}

Animation* EnemyBase::createAnimation(std::string prefixName, int frameNum, float delay)
{
	Vector<SpriteFrame*> animFrames;

	for (int i=1; i<=frameNum; i++)
	{
		char buffer[20] = {0};
		sprintf(buffer, "%i.png", i);
		std::string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack( frame );
	}

	return Animation::createWithSpriteFrames(animFrames, delay);
}

Node* EnemyBase::currPoint()
{
	return this->pointsVector.at(pointCounter);
}

Node* EnemyBase::nextPoint()
{
	int maxCount = this->pointsVector.size();

	pointCounter++;
	if (pointCounter < maxCount) {
		auto node = this->pointsVector.at( pointCounter );
		return node;
	}
	else {
		pointCounter = maxCount-1;
	}

	return NULL;
}

void EnemyBase::runFollowPoint()
{
	auto point = currPoint();
	setPosition( point->getPosition() );
	point = nextPoint();

	if (point != NULL) {
		runAction( CCSequence::create(MoveTo::create(getRunSpeed(), point->getPosition()), CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFollowPoint, this)), NULL) );
	}
}

void EnemyBase::run(float dt)
{
	runAction( Animate::create(AnimationCache::getInstance()->getAnimation("run")));
}

void EnemyBase::setPointsVector(Vector<Node*> points)
{
	pointsVector = points;
}

/*Zoombie class*/
bool Zoombie::init()
{
	if (!Sprite::init()) {
		return false;
	}

	setRunSpeed(3);
	_animation = createAnimation("sprite1_", 5, 0.1f);
	AnimationCache::getInstance()->addAnimation(_animation, "run");

	schedule( schedule_selector(EnemyBase::run), 0.4f); 
	return true;
}

Zoombie* Zoombie::createZoombie(Vector<Node *> points)
{
	Zoombie* zoo = new Zoombie();
	if (zoo && zoo->init()) {
		zoo->setPointsVector( points );
		zoo->runFollowPoint();

		zoo->autorelease();

		return zoo;
	}
	else {
		delete zoo;
		zoo = NULL;
		return NULL;
	}
}