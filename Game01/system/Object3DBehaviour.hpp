//
//  Object3DBehaviour.hpp
//  Game01
//
//  Created by kazuki sako on 2018/06/23.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Object3DBehaviour_hpp
#define Object3DBehaviour_hpp

#include <stdio.h>
#include "Object3D.hpp"
#include "./Fractory.h"

class Object3DBehaviour: public Object3D {
public:
    typedef ::Factory<Object3DBehaviour> Factory;
private:
    Object3D* manager;
    static Factory _factory;
public:
    Object3DBehaviour();
    void update() override;
    static Factory::Type create(Factory::Key const & name);
    ~Object3DBehaviour();
    
    template<class Deriverd> static void define(Factory::Key const & name){
        bool new_key = _factory.define(name,
                                       &Object3DBehaviour::Factory::template create_func<Object3DBehaviour, Deriverd>);
        if (not new_key) {
            throw std::logic_error(std::string(__FUNCSIG__) +
                                   ": name already registered");
        }
    }
    
};



#endif /* Object3DBehaviour_hpp */

