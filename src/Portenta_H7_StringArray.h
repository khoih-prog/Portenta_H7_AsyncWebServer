/****************************************************************************************************************************
  Portenta_H7_StringArray.h - Dead simple AsyncWebServer for STM32 LAN8720 or built-in LAN8742A Ethernet

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi

  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with Vision-Shield Ethernet or Murata WiFi

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license

  Version: 1.4.2

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      06/10/2021 Initial coding for Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  1.1.0   K Hoang      08/10/2021 Add support to Portenta_H7 (STM32H7) using Murata WiFi
  1.1.1   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  1.2.0   K Hoang      07/12/2021 Fix crashing issue
  1.2.1   K Hoang      12/01/2022 Fix authenticate issue caused by libb64
  1.3.0   K Hoang      26/09/2022 Fix issue with slow browsers or network
  1.4.0   K Hoang      02/10/2022 Option to use cString instead og String to save Heap
  1.4.1   K Hoang      04/10/2022 Don't need memmove(), String no longer destroyed
  1.4.2   K Hoang      10/11/2022 Add examples to demo how to use beginChunkedResponse() to send in chunks
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_STRINGARRAY_H_
#define PORTENTA_H7_STRINGARRAY_H_

#include "stddef.h"
#include "WString.h"

/////////////////////////////////////////////////

template <typename T>
class LinkedListNode
{
    T _value;

  public:
    LinkedListNode<T>* next;
    LinkedListNode(const T val): _value(val), next(nullptr) {}
    ~LinkedListNode() {}

    /////////////////////////////////////////////////

    const T& value() const
    {
      return _value;
    };

    /////////////////////////////////////////////////

    T& value()
    {
      return _value;
    }
};

/////////////////////////////////////////////////

template <typename T, template<typename> class Item = LinkedListNode>
class LinkedList
{
  public:
    typedef Item<T> ItemType;
    typedef std::function<void(const T&)> OnRemove;
    typedef std::function<bool(const T&)> Predicate;

  private:
    ItemType* _root;
    OnRemove _onRemove;

    class Iterator
    {
        ItemType* _node;

      public:
        Iterator(ItemType* current = nullptr) : _node(current) {}
        Iterator(const Iterator& i) : _node(i._node) {}

        /////////////////////////////////////////////////

        Iterator& operator ++()
        {
          _node = _node->next;
          return *this;
        }

        /////////////////////////////////////////////////

        bool operator != (const Iterator& i) const
        {
          return _node != i._node;
        }

        /////////////////////////////////////////////////

        const T& operator * () const
        {
          return _node->value();
        }

        /////////////////////////////////////////////////

        const T* operator -> () const
        {
          return &_node->value();
        }
    };

  public:
    typedef const Iterator ConstIterator;

    /////////////////////////////////////////////////

    ConstIterator begin() const
    {
      return ConstIterator(_root);
    }

    /////////////////////////////////////////////////

    ConstIterator end() const
    {
      return ConstIterator(nullptr);
    }

    /////////////////////////////////////////////////

    LinkedList(OnRemove onRemove) : _root(nullptr), _onRemove(onRemove) {}
    ~LinkedList() {}

    /////////////////////////////////////////////////

    void add(const T& t)
    {
      auto it = new ItemType(t);

      if (!_root)
      {
        _root = it;
      }
      else
      {
        auto i = _root;

        while (i->next)
          i = i->next;

        i->next = it;
      }
    }

    /////////////////////////////////////////////////

    T& front() const
    {
      return _root->value();
    }

    /////////////////////////////////////////////////

    bool isEmpty() const
    {
      return _root == nullptr;
    }

    /////////////////////////////////////////////////

    size_t length() const
    {
      size_t i = 0;
      auto it = _root;

      while (it)
      {
        i++;
        it = it->next;
      }

      return i;
    }

    /////////////////////////////////////////////////

    size_t count_if(Predicate predicate) const
    {
      size_t i = 0;
      auto it = _root;

      while (it)
      {
        if (!predicate)
        {
          i++;
        }
        else if (predicate(it->value()))
        {
          i++;
        }

        it = it->next;
      }

      return i;
    }

    /////////////////////////////////////////////////

    const T* nth(size_t N) const
    {
      size_t i = 0;
      auto it = _root;

      while (it)
      {
        if (i++ == N)
          return &(it->value());

        it = it->next;
      }

      return nullptr;
    }

    /////////////////////////////////////////////////

    bool remove(const T& t)
    {
      auto it = _root;
      auto pit = _root;

      while (it)
      {
        if (it->value() == t)
        {
          if (it == _root)
          {
            _root = _root->next;
          }
          else
          {
            pit->next = it->next;
          }

          if (_onRemove)
          {
            _onRemove(it->value());
          }

          delete it;

          return true;
        }

        pit = it;
        it = it->next;
      }

      return false;
    }

    /////////////////////////////////////////////////

    bool remove_first(Predicate predicate)
    {
      auto it = _root;
      auto pit = _root;

      while (it)
      {
        if (predicate(it->value()))
        {
          if (it == _root)
          {
            _root = _root->next;
          }
          else
          {
            pit->next = it->next;
          }

          if (_onRemove)
          {
            _onRemove(it->value());
          }

          delete it;

          return true;
        }

        pit = it;
        it = it->next;
      }

      return false;
    }

    /////////////////////////////////////////////////

    void free()
    {
      while (_root != nullptr)
      {
        auto it = _root;
        _root = _root->next;

        if (_onRemove)
        {
          _onRemove(it->value());
        }

        delete it;
      }

      _root = nullptr;
    }
};

/////////////////////////////////////////////////

class StringArray : public LinkedList<String>
{
  public:

    StringArray() : LinkedList(nullptr) {}

    /////////////////////////////////////////////////

    bool containsIgnoreCase(const String& str)
    {
      for (const auto& s : *this)
      {
        if (str.equalsIgnoreCase(s))
        {
          return true;
        }
      }

      return false;
    }
};

/////////////////////////////////////////////////

#endif /* PORTENTA_H7_STRINGARRAY_H_ */
