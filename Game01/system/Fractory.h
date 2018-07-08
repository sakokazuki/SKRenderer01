//
//  Fractory.h
//  Game01
//
//  Created by kazuki sako on 2018/07/09.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Fractory_h
#define Fractory_h

#include <map>

template<class Interface, class KeyT=std::string>
struct Factory {
    typedef KeyT Key;
    typedef Interface* Type;
    typedef Type (*Creator)();
    
    bool define(Key const& key, Creator v) {
        // Define key -> v relationship, return whether this is a new key.
        return _registry.insert(typename Registry::value_type(key, v)).second;
    }
    Type create(Key const& key) {
        typename Registry::const_iterator i = _registry.find(key);
        if (i == _registry.end()) {
            throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) +
                                        ": key not registered");
        }
        else return i->second();
    }
    
    template<class Base, class Actual>
    static Base* create_func() {
        return new Actual();
    }
    
private:
    typedef std::map<Key, Creator> Registry;
    Registry _registry;
};

#endif /* Fractory_h */
