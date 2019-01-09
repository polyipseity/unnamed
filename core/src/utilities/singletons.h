#ifndef SINGLETONS_H_
#define SINGLETONS_H_

// Modified from https://stackoverflow.com/a/1008289.
template<class T>
class Singleton
{
protected:
    // Constructor.
    Singleton<T>(){}

public:
    static T& getInstance()
    {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        static T instance;
        return instance;
    }

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    //
    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status.

    Singleton<T>(Singleton<T> const&) final = delete;
    virtual void operator=(Singleton<T> const&) final = delete;
};

// Modified from https://stackoverflow.com/a/1008289.
template<class T>
class ThreadLocalSingleton
{
protected:
    // Constructor.
    ThreadLocalSingleton<T>(){}

public:
    static T& getInstance()
    {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        thread_local T instance;
        return instance;
    }

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    //
    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status.

    ThreadLocalSingleton<T>(ThreadLocalSingleton<T> const&) final = delete;
    virtual void operator=(ThreadLocalSingleton<T> const&) final = delete;
};

#endif /* SINGLETONS_H_ */
