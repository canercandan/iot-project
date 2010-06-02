#ifndef SINGLETON_HPP
# define SINGLETON_HPP
/*
** NB: works for class  with 0 or 1 params in constructors
** if you need more parameters in constructors just add a templated getInstance
 */
template <class T> class Singleton
{
private:
  Singleton(){;}
  static T* theInstance;

public:
  static T* getInstance()
  {
    if (theInstance == NULL)
      theInstance = new T();
    return theInstance;
  }
  template <class C> static T* getInstance(C val)
  {
    if (theInstance == NULL)
      {
	theInstance = new T(val);
      }
    return theInstance;
  }
};

template <class T>  T* Singleton<T>::theInstance = NULL;

#endif /*!SINGLETON_HPP*/
