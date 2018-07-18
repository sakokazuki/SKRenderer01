//
//  Scene.hpp
//  Game01
//
//  Created by kazuki sako on 2018/07/09.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "../meshes/Mesh.hpp"
#include "../camera/Camera.hpp"
#include "../lights/Light.hpp"

namespace Scene {
    class Scene {
        Camera* camera;
        std::vector<Mesh*> meshes;
        std::vector<Light*> lights;
        
    public:
        Scene();
        void addMesh(Mesh* mesh);
        void addLight(Light* light);
        void setCamera(Camera* camera);
        std::vector<Mesh*> getMehses();
        std::vector<Light*> getLights();
        Camera* getCamera();
        
        void update();
        void draw();
        ~Scene();
    };
    
}


#endif /* Scene_hpp */

