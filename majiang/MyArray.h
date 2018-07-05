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
* �������������
*/

class MyArray{
public:
	template <class T>
	static void randomArray(T &targetArray);
	static vector <int> randomIndex(int n);
	//�ȽϺ���
	static int intCompare(const void* a,const void* b);
	//Ԥ������������������ظ���Ԫ��
	static void repeatElement(int* &a, int num, int keytype, vector<int>& result);
	//�ж��������м�����Ԫ��
	static int elementNumInArray(int* &a,int num, int n);
	//��������ɾ��ĳ���ظ�Ԫ�أ������һ��������
	static void removeELement(int* &a, int arraysize, int element, int num, vector<int>& result);
	//�ж����������Ԫ���Ƿ���AAA����ABC�͵�
	static bool judge(vector<int> &result);
};

#endif