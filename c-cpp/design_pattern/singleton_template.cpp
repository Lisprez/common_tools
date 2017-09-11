#pragma once

template <class T>
Class Singleton {
protected:
	Singleton() {};
	Singleton(const Singleton&) = delete;
	Singleton& operator =(const Singleton&) = delete;
	Singleton(const Singleton&&) = delete;
	Singleton& operator =(const Singleton&&) = delete;

private:
	static T* instance_;

public:
	static T* GetInstance();
};

template <class T>
T* Singleton<T>::GetInstance()
{
	static T t;
	return &t;
}

// exmaple
// class Student : Singleton<Student> {
//		xxxx
// };
// 如上Student就成为了单例类, 而且是生成对象时线程安全的