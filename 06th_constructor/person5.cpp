/*
* 目标：了解运行时 new 出的内存空间没有被销毁，导致内存泄漏。
*/
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

class Person {
private:
	char *name;
	int age;
	char *work;

public:

	Person() {//cout <<"Pserson()"<<endl;
		name = NULL;
		work = NULL;
	}
	Person(char *name) 
	{
		/* 程序执行结束退出后，new 方法申请的堆空间会被自动释放回收。
		 * 理论上来说方法调用结束返回时，方法中局部变量的内存空间理应被释放。
		 * 但是如果程序运行时调用的局部方法在内部使用 new 实例化对象（例如下面的 test_fun()调用 Person 构造函数），
		 * 当局部方法返回时问题出现了--由 new 申请的堆空间并不会得到释放。当这种情况多了，会造成运行时内存的及大浪费
		 * 解决办法：(详见 person6.cpp)
		 */
		//cout <<"Pserson(char *)"<<endl;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->work = NULL;
	}

	Person(char *name, int age, char *work = "none") 
	{
		//cout <<"Pserson(char*, int)"<<endl;
		this->age = age;

		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

		this->work = new char[strlen(work) + 1];
		strcpy(this->work, work);
	}

	void setName(char *n)
	{
		name = n;
	}
	int setAge(int a)
	{
		if (a < 0 || a > 150)
		{
			age = 0;
			return -1;
		}
		age = a;
		return 0;
	}
	void printInfo(void)
	{
		//printf("name = %s, age = %d, work = %s\n", name, age, work); 
		//cout<<"name = "<<name<<", age = "<<age<<", work = "<<work<<endl;
	}
};

void test_fun()
{
	Person per("zhangsan", 16);
	Person per2;   /* µ÷ÓÃÎÞ²Î¹¹Ôìº¯Êý */
	Person per3(); /* int fun(); */

	Person *per4 = new Person;
	Person *per5 = new Person();

	Person *per6 = new Person[2];

	Person *per7 = new Person("lisi", 18, "student");
	Person *per8 = new Person("wangwu", 18);

	per.printInfo();
	per7->printInfo();
	per8->printInfo();

	delete per4;
	delete per5;
	delete []per6;
	delete per7;
	delete per8;

}

int main(int argc, char **argv)
{
	for (int i = 0; i < 1000000; i++)
		test_fun();
	cout << "run test_fun end"<<endl;
	sleep(10);
	return 0;
}

