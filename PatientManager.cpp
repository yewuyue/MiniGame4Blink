#include "PatientManager.h"

CPatientManager* CPatientManager::m_pInstace = NULL;
CPatientManager::CPatientManager()
{

}


CPatientManager::~CPatientManager()
{
}


// 获取本类实例
CPatientManager* CPatientManager::GetInstance(CCLayer * pLayer)
{
	if (NULL != pLayer)
	{
		m_pInstace = new CPatientManager();
		m_pInstace->m_pLayer = pLayer;
		return m_pInstace;
	}	
	return NULL;
}


// 添加精灵
int CPatientManager::Insert(unsigned int eFirstPressKey, unsigned int eSecondPressKey,  CCSprite * pPatient)
{
	unsigned int key = (eFirstPressKey << ACTION_NUNM) + eSecondPressKey;
	PatientMap::iterator iter = m_patientMap.find(key);
	if ( m_patientMap.end() == iter) //不存在则添加该类型链表，再插入
	{
		auto pList = new cocos2d::Vector<CCSprite*>();
		pList->pushBack(pPatient);
		m_patientMap.insert(PatientMapPair(key, pList));
	}
	else //存在则直接插入
	{
		iter->second->pushBack(pPatient);
	}
	return 0;
}

/***********************************************************************************************************
***返回值：-1,0,1
*** -1 ： 表示没有找到该脑残病人 or 输入无法匹配，需要清空输入
*** 0  ： 表示可以匹配到，但是还没输入完呢
*** 1  ： 表示成果的消除了一个
**********************************************************************************************************/
int CPatientManager::DeletePatient(unsigned int eFirstPressKey, unsigned int eSecondPressKey)
{
	unsigned int key = (eFirstPressKey << ACTION_NUNM) + eSecondPressKey;
	PatientMap::iterator iter = m_patientMap.find(key);
	if (m_patientMap.end() == iter)
	{
		if (eSecondPressKey == 0)
		{
			for (iter = m_patientMap.begin(); iter != m_patientMap.end(); ++iter)
			{
				if ((key & iter->first) == key)
				{
					return 0;
				}
			}
		}
		return -1;
	}

	if (iter->second && iter->second->size() != 0)
	{
		for (cocos2d::Vector<CCSprite*>::iterator it = iter->second->begin(); it != iter->second->end(); ++it)
		{			
			m_pLayer->removeChild(*it, true);
			
		}
		iter->second->clear();
		return 1;
	}		
	
	return -1;
}
