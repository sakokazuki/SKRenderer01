#include "TestApp2.h"
#include "../lights/Light.hpp"
#include "../lights/SpotLight.hpp"
#include "../lights/DirectionalLight.hpp"
#include "../lights/PointLight.hpp"
#include "../meshes/PlaneMesh.hpp"
#include "../meshMaterials/SimpleMeshMaterial.h"

namespace app{
	TestApp2::TestApp2(Window *window): app::AppBase(window)
	{
		const GLint *const size(window->getViewport());
		int windowW = size[2];
		int windowH = size[3];
		Renderer* renderer = new TestRenderer(windowW, windowH);
		Scene::Scene* scene = new Scene::Scene();

		setRenderer(renderer);
		setScene(scene);

		Light* directionalLight = new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.1f);
		directionalLight->setPosition(glm::vec3(-2, 3, -3));
		directionalLight->castShadow = true;
		scene->addLight(directionalLight);

		Camera* camera = new Camera(windowW, windowH);
		camera->setPosition(glm::vec3(0, 2, 5));
		scene->setCamera(camera);

		Mesh* plane = new PlaneMesh();
		plane->setPosition(glm::vec3(0, 0, 0));
		plane->setScale(glm::vec3(2, 2, 2));

		SimpleMeshMaterial* meshMat = new SimpleMeshMaterial();
		plane->meshMaterial = meshMat;

		scene->addMesh(plane);

	}

	void TestApp2::loop() {

		AppBase::loop();
	}



	TestApp2::~TestApp2()
	{
	}

}


