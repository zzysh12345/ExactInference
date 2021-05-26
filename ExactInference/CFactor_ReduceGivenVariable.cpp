/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_ReduceGivenVariable.cpp
//功  能：		根据给定的变量和值，化简因子。用于计算条件概率分布
//开发者：		高志强
//日  期：		2021年03月13日
//更  新：		2021年03月14日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		50行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		ReduceGivenVariable()
//功  能：		根据给定的变量ID和值ID，化简因子
//参  数：		unsigned int,unsigned int
//返回值：		无
void CFactor::ReduceGivenVariable(unsigned int nVariableID, unsigned int nValueID)
{
	//////////////////////////////////////////
	//函数3：因子化简。需要同学完成
	//cout << nVariableID;
	//cout << nValueID;
	for (unsigned int i = 0; i < m_VariableIDs.size(); i++) {
		if (nVariableID == m_VariableIDs[i]) {
			//当前因子就是需要化简的因子,需要去掉不符合的因子行
			for (vector<FACTOR_ROW>::iterator it = m_FactorRows.begin(); it != m_FactorRows.end();) {
				if ((*it).ValueIDs[i] != nValueID) {
					//当前因子行不符合条件，去掉
					it = m_FactorRows.erase(it);
					if (it == m_FactorRows.end()) {
						break;
					}
				}
				else { it++; }
			}
		}
	}
	//////////////////////////////////////////
}