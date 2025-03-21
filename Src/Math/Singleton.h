#ifndef SINGLETON_H_
#define SINGLETON_H_

template<class T>
class Singleton
{
public:
    static inline T& GetInstance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}

private:
    void operator=(const Singleton& obj) {}
    Singleton(const Singleton& obj) {}
    static T* instance;
};


template< class T >
T* Singleton< T >::instance = 0;

#endif