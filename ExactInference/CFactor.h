/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor.h
//功  能：		定义因子类
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月13日
//更  新：		2021年03月29日
//长  度：		210行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>							//map头文件
#include <set>							//set头文件
#include <string>						//string头文件
#include <list>							//list头文件
#include <vector>						//vector头文件
#include <algorithm>					//algorithm类头文件
#include <numeric>						//numeric类头文件
#include <sstream>						//sstream类头文件
#include <fstream>						//fstream类头文件
#include <time.h>						//时间函数类头文件
#include "math.h"						//数学函数头文件
#include "Helper.h"						//辅助函数头文件


//声明命名空间
using namespace std;					//使用标准命名空间


//定义因子行
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 变量值ID的列表，按照变量ID列表的顺序排列
	double fValue;												//02 因子的值
}FACTOR_ROW;


//定义因子类
class CFactor
{
	//构造函数与析构函数
public:
	CFactor();													//构造函数
	~CFactor();													//析构函数

	//公有方法
public:
	//初始化
	void SetFactorVariableIDs(vector<unsigned int>&);			//设置因子的变量ID列表
	void SetFactorRow(vector<unsigned int>&, double&);			//设置因子行的值
	//访问
	vector<unsigned int> GetFactorVariableIDs();				//获取变量ID列表
	//操作
	void ReduceGivenVariable(unsigned int, unsigned int);		//因子化简。消除给定变量ID、和变量值ID
	void SumOutVariable(unsigned int);								//因子求和掉给定变量ID
	void Normalize();											//因子归一化
	//查询
	double Query(vector<unsigned int>&,vector<unsigned int>&);	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值

	//重载因子积
	CFactor operator*(const CFactor& second)
	{
		//定义新的、待返回的因子
		CFactor factor;

		/////////////////////////////////////////////
		//函数1：因子积重载：需要由同学完成
		//步骤1：求两个因子的交
		map<unsigned int,unsigned int> FirstToSeconds;
		//步骤1.1：遍历第一个因子的变量ID
		for (unsigned int i=0;i<m_VariableIDs.size();i++){
		    unsigned  int nFirstVariableID=m_VariableIDs[i];
		    for (unsigned int j=0;j<second.m_VariableIDs.size();j++){
		        unsigned  int nSecondVariableID=second.m_VariableIDs[j];
		        //检查是否相等
		        if (nFirstVariableID==nSecondVariableID){
		            FirstToSeconds.insert(make_pair(i,j));   //建立映射
		        }
		    }
		}
		//步骤1.2：获取相同变量在第二个因子中的位置集合
		set<unsigned int> RedundantSeconds;
		for (map<unsigned int,unsigned int>::iterator it=FirstToSeconds.begin();it!=FirstToSeconds.end();it++){
		    RedundantSeconds.insert(it->second);
		}

		//步骤2:直接拼接
		if (FirstToSeconds.size()==0){
		    //如果两个因子没有相同变量
		    for (int i=0;i<m_FactorRows.size();i++){
		        for (int j=0;j<second.m_FactorRows.size();j++){
		            //定义新的因子行
		            FACTOR_ROW factor_row;
		            factor_row.ValueIDs=m_FactorRows[i].ValueIDs;   //第一个因子的变量取值
		            for (int m=0;m<second.m_FactorRows[j].ValueIDs.size();m++){
		                //这里需要一个一个添加第二个因子的变量值,有没有更好的办法?
		                factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
		            }
		            factor_row.fValue=m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;
		            factor.m_FactorRows.push_back(factor_row);
		        }
		    }
		    //上面完成了没有相同变量情况下的变量值拼接，下面是变量ID拼接
		    factor.m_VariableIDs=m_VariableIDs;
		    for (int i=0;i<second.m_VariableIDs.size();i++){
		        factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
		    }
		}
		//步骤3：间接拼接
		else{
		   //如果两个因子有相同变量，需要间接拼接
		   for (int i=0;i<m_FactorRows.size();i++){
		       for (int j=0;j<second.m_FactorRows.size();j++){
		           if (IsConsistentValueID(m_FactorRows[i],second.m_FactorRows[j],FirstToSeconds)){
		               //检查这一行相同变量的值是否相等，只有所有相同变量的取值相同才为真
		               FACTOR_ROW factor_row;
		               factor_row.ValueIDs=m_FactorRows[i].ValueIDs;
		               for (unsigned int m=0;m<second.m_FactorRows[j].ValueIDs.size();m++){
		                   if (!IsINTInSet(m,RedundantSeconds)){
		                       factor_row.ValueIDs.push_back(second.m_FactorRows[j].ValueIDs[m]);
		                   }
		               }
		               factor_row.fValue=m_FactorRows[i].fValue*second.m_FactorRows[j].fValue;
		               factor.m_FactorRows.push_back(factor_row);
		           }
		       }
		   }
		   factor.m_VariableIDs=m_VariableIDs;
		   for (unsigned int i=0;i<second.m_VariableIDs.size();i++){
		       if (!IsINTInSet(i,RedundantSeconds)){
		           factor.m_VariableIDs.push_back(second.m_VariableIDs[i]);
		       }
		   }
		}


		////////////////////////////////////////////

		//返回因子
		return factor;
	};		
	
	//私有方法
private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, map<unsigned int, unsigned int>&);	//检查两行是否兼容	
	//在求和时将因子的值合并到首行
	void MergeIntoFirstRow(FACTOR_ROW&);
	
	//私有数据
private:	
	vector<unsigned int> m_VariableIDs;					//因子变量ID列表
	vector<FACTOR_ROW> m_FactorRows;					//因子行的列表
};