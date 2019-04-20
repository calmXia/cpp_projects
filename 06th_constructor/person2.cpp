
#include <iostream>
using namespace std;

class Person {
private:
	char *name;
	int age;
	char *work;

public:

	Person() {cout <<"Pserson()"<<endl;}
	Person(char *name) 
	{
		cout <<"Pserson(char *)"<<endl;
		this->name = name;
	}
	//work 设置默认值，避免实例化对象调用时未传参导致乱码（野值）的情况
	Person(char *name, int age, char *work = "none") 
	{
		cout <<"Pserson(char*, int)"<<endl;
		this->name = name;
		this->age = age;
		this->work = work;
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
		cout<<"name = "<<name<<", age = "<<age<<", work = "<<work<<endl;
	}
};

int main(int argc, char **argv)
{
	Person per("zhangsan", 16); /* 调用相应的有参构造函数*/
	Person per2;   /* 调用无参构造函数来实例化对象 */
	Person per3(); /* 这是函数声明（形如 int fun();），并不会调用无参构造函数.  */

	per.printInfo();
	return 0;
}

