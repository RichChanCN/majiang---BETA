#ifndef __RANDOMARRAY_H__
#define __RANDOMARRAY_H__

#include <time.h>
#include <vector>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<algorithm>

using namespace std;


/**
* 将数组随机打乱
*/

class MyArray{
public:
	template <class T>
	static void randomArray(T &targetArray);
	static vector <int> randomIndex(int n);
	//比较函数
	static int intCompare(const void* a,const void* b);
	//预处理函数，输出数组中重复的元素
	static void repeatElement(int* &a, int num, int keytype, vector<int>& result);
	//判断数组里有几个该元素
	static int elementNumInArray(int* &a,int num, int n);
	//从数组里删除某个重复元素，输出在一个向量上
	static void removeELement(int* &a, int arraysize, int element, int num, vector<int>& result);
	//判断向量里面的元素是否都是AAA或者ABC型的
	static bool judge(vector<int> &result);
};

#endif