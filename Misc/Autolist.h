#pragma once

/**
    Description:

    Inherit from this class to automatically create lists of
    similar objects. Whenever an object is created it will
    automatically be added to the list. Whenever it is destroyed
    it will automatically be removed.
*/

#include <list>

template <class T>
class AutoList
{
    public:

        typedef std::list<T*> ObjectList;

    private:

        static ObjectList objectList_;

    protected:

        AutoList()
        {
            objectList_.push_back(static_cast<T*>(this))
        }

        ~AutoList()
        {
            objectList_.remove(static_cast<T*>(this));
        }

    public:

        static ObjectList& GetAllMembers()
        {
            return objectList_;
        }
};

template<class T>
std::list<T*> AutoList<T>::objectList_;
