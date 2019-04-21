/*
* 目标：堆空间，栈空间；
	析构函数，delete 的区别
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
	//析构函数不能重载，没有参数，一个类只能有一个析构函数。如果没定义，编译器会自动生成一个。
	~Person()
	{
		cout << "~Person()"<<endl;
		if (this->name) {
			cout << "name = "<<name<<endl;
			delete this->name;
		}
		if (this->work) {
			cout << "work = "<<work<<endl;
			delete this->work;
		}
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
	//首先要明确一点，系统只会自动释放栈内空间，而堆内空间需要用户自己维护。
	//C++中，除了new来的空间存放在堆内，其他均存放在栈中
	
	//1.常规调用构造函数生成的实例化对象存储在栈空间，局部方法调用结束返回之前的瞬间有系统自动调用析构函数销毁对象
	Person per("zhangsan", 16);

	//2.局部方法中使用 new 实例化的对象存储在堆空间，只能手动通过 delete 销毁，
	//否则在方法退出后且主程序然在运行时( main 还在)依然存在，导致内存泄漏。
	//最终只能在主程序退出时由系统销毁，且此时并不会调用析构函数。
	Person *per7 = new Person("lisi", 18, "student");
	delete per7;

}

int main(int argc, char **argv)
{
	test_fun();
	cout << "run test_fun end"<<endl;
	sleep(10);
	return 0;
}

