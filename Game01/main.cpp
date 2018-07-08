//
//  main.cpp
//  Game01
//
//  Created by kazuki sako on 2017/12/06.
//  Copyright © 2017年 kazuki sako. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <fmt/format.cc>
#include <fmt/format.h>


#include <GL/glew.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "system/Window.hpp"

#include <gli/gli.hpp>


#include "scenes/Scene01.hpp"

#include <glm/glm.hpp>

#include <map>

template<class Interface, class KeyT=std::string>
struct Factory {
    typedef KeyT Key;
    typedef std::auto_ptr<Interface> Type;
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
    static
    std::auto_ptr<Base> create_func() {
        return std::auto_ptr<Base>(new Actual());
    }
    
private:
    typedef std::map<Key, Creator> Registry;
    Registry _registry;
};

struct Base {
    typedef ::Factory<Base> Factory;
    virtual ~Base() {}
    virtual int answer() const = 0;
    
    static Factory::Type create(Factory::Key const& name) {
        return _factory.create(name);
    }
    template<class Derived>
    static void define(Factory::Key const& name) {
        bool new_key = _factory.define(name,
                                       &Factory::template create_func<Base, Derived>);
        if (not new_key) {
            throw std::logic_error(std::string(__PRETTY_FUNCTION__) +
                                   ": name already registered");
        }
    }
    
private:
    static Factory _factory;
};
Base::Factory Base::_factory;

struct A : Base {
    virtual int answer() const { return 42; }
};

int main(void)
{
    atexit(glfwTerminate);
    
    Base::define<A>("A");
    
    std::cout << Base::create("A")->answer() << std::endl;
    

    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    Window window;
    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }

    const GLfloat *const size(window.getSize());
    const Scene01* scene = new Scene01(size[0], size[1]);
//    const SceneDeferred* scene = new SceneDeferred(size[0], size[1]);

    glfwSetTime(0.0);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);



    while (window.shouldClose() == GL_FALSE)
    {
        scene->render();
        /* Swap front and back buffers */
        window.swapBuffers();
    }
    return 0;
}
