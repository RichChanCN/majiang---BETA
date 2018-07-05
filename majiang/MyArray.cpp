#include"MyArray.h"
template<class T>

void MyArray::randomArray(T &targetArray) {

	int n = sizeof(targetArray) / sizeof(targetArray[0]);
	T *tempArray = new T[n];
	//	T tempArray[108];
	for (int i = 0; i < n; i++)
		tempArray[i] = targetArray[i];
	//定义两个向量
	vector <int> newArray;
	vector <int> oldArray;
	// 初始化原数组
	for (int i = 0; i<n; i++)
		oldArray.push_back(i);
	// 打乱
	// 随机打乱
	for (int i = n; i>0; i--) {
		srand(unsigned(time(NULL)));
		// 选中的随机下标
		int index = rand() % i;
		// 根据选中的下标将原数组选中的元素push到新数组
		newArray.push_back(oldArray[index]);
		// 将原数组中选中的元素剔除
		oldArray.erase(oldArray.begin() + index);
	}

	for (int i = 0; i < n; i++)
		targetArray[newArray[i]] = tempArray[i];

	delete[] tempArray;
};

vector <int> MyArray::randomIndex(int n) {

	//定义两个向量
	vector <int> newArray;
	vector <int> oldArray;
	// 初始化原数组
	for (int i = 0; i<n; i++)
		oldArray.push_back(i);
	// 打乱
	// 随机打乱
	for (int i = n; i>0; i--) {
		srand(unsigned(time(NULL)));
		// 选中的随机下标
		int index = rand() % i;
		// 根据选中的下标将原数组选中的元素push到新数组
		newArray.push_back(oldArray[index]);
		// 将原数组中选中的元素剔除
		oldArray.erase(oldArray.begin() + index);
	}

	return newArray;
}

int MyArray::intCompare(const void* a, const void* b)
{
	int * pa, *pb;
	pa = (int*)a;
	pb = (int*)b;

	return pa - pb;
}


int MyArray::elementNumInArray(int* &p,int num,int n)
{
	int counts = 0;
	for (int i = 0; i < num; i++)
	{
		if (p[i] == n)
			counts++;
	}
	return counts;
}

void MyArray::repeatElement(int* &a, int num, int keytype, vector<int>& duizi)
{
	int out[5] = {0,0,0,0,0};
	
	int temp;
	int n = 0;
	for (int i = 0; i < num; i = i + 2)
	{
		temp = a[i];
		if (temp / 10 == keytype,
			elementNumInArray(a, num, temp) > 1
			&& n < 4
			&& temp != out[0]
			&& temp != out[1]
			&& temp != out[2]
			&& temp != out[3]
			&& temp != out[4]
			)
		{
			out[n] = temp;
			++n;
			duizi.push_back(temp);
		}
	}

}

void MyArray::removeELement(int* &a, int arraysize, int element, int num, vector<int>& result)
{
	result.clear();
	int count = 0;
	for (int i = 0; i < arraysize; i++)
	{
		if (a[i] == element && count < num)
		{
			count++;
		}
		else
			result.push_back(a[i]);
	}
}

bool MyArray::judge(vector<int> &r)
{
	vector<int>::iterator location1;
	vector<int>::iterator location2;
	int temp;
	int rsize = r.size();
	while (rsize > -1)
	{
		if (rsize == 0)
			return true;
		temp = rsize - 1;

		if (rsize > 2 && (r[temp] + r[temp - 1] + r[temp - 2]) / 3 == r[temp])//有三张
		{
			for (int i = 0; i < 3; i++)
			{
				r.pop_back();//去掉这3张
				
			}
			rsize = r.size();
			continue;
		}

		location1 = find(r.begin(), r.end(), r[temp] - 1);
		
		if (location1 - r.begin() != rsize)		//有比最后一个小1的元素吗
		{
			location2 = find(r.begin(), r.end(), r[temp] - 2);

			if (location2 - r.begin() != rsize) //有比最有一个元素小2的吗
			{//小1小2的都有的话，删除这3个元素
				r.pop_back();
				location1 = r.erase(location1);
				location2 = r.erase(location2);
			}
			else   //有小1的没有小2的
			{
				if (rsize > 5 && (r[temp] + r[temp - 1] + r[temp - 2]) / 3 == r[temp] && (r[temp - 3] + r[temp - 4] + r[temp - 5]) / 3 == r[temp - 3])//那这两种牌应该是每个三张
					for (int i = 0; i < 6; i++)
					{
						r.pop_back(); //去掉这6张
					}
				else//否则没胡
					return false;
			}
		}
		else //没有小1的
		{
			if (rsize > 2 && (r[temp] + r[temp - 1] + r[temp - 2]) / 3 == r[temp])//那这种牌应该是有三张
			{
				for (int i = 0; i < 3; i++)
				{
					r.pop_back();//去掉这3张
				}
			}
			else
				return false;
		}

		rsize = r.size();
	}
	
}