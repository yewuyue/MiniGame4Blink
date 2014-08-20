#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Sprite
{
public:
	EnemyBase();
	~EnemyBase();
	virtual bool init();
	
	CREATE_FUNC(EnemyBase);
	Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    Node* currPoint();
    Node* nextPoint();
    void runFollowPoint();
	void run(float dt);
    void setPointsVector(Vector<Node*> points);
    
private:
    Vector<Node*> pointsVector;
    
protected:
    int pointCounter;
    Animation *_animation;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(int, currHp, CurrHp);
    
};

/**/
class Zoombie : public EnemyBase
{
public:
	virtual bool init();

	static Zoombie* createZoombie(Vector<Node*> points);
};

#endif    //ENEMYBASE_H_