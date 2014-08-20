#include "PatientManager.h"

CPatientManager* CPatientManager::m_pInstace = NULL;
CPatientManager::CPatientManager()
{

}


CPatientManager::~CPatientManager()
{
}


// ��ȡ����ʵ��
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


// ��Ӿ���
int CPatientManager::Insert(unsigned int eFirstPressKey, unsigned int eSecondPressKey,  CCSprite * pPatient)
{
	unsigned int key = (eFirstPressKey << ACTION_NUNM) + eSecondPressKey;
	PatientMap::iterator iter = m_patientMap.find(key);
	if ( m_patientMap.end() == iter) //����������Ӹ����������ٲ���
	{
		auto pList = new cocos2d::Vector<CCSprite*>();
		pList->pushBack(pPatient);
		m_patientMap.insert(PatientMapPair(key, pList));
	}
	else //������ֱ�Ӳ���
	{
		iter->second->pushBack(pPatient);
	}
	return 0;
}

/***********************************************************************************************************
***����ֵ��-1,0,1
*** -1 �� ��ʾû���ҵ����Բв��� or �����޷�ƥ�䣬��Ҫ�������
*** 0  �� ��ʾ����ƥ�䵽�����ǻ�û��������
*** 1  �� ��ʾ�ɹ���������һ��
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
