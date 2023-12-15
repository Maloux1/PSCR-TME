#pragma once

#include "Barrier.h"
#include "util.h"

#include <thread>
#include <iostream>

using namespace std;

namespace pr {

	class Job {
	public:
		virtual void run () = 0;
		virtual ~Job() {};
	};

	// Job concret : exemple

	class SleepJob : public Job {
		int calcul (int v) {
			std::cout << "Computing for arg =" << v << std::endl;
			// traiter un gros calcul
			this_thread::sleep_for(1s);
			int ret = v % 255;
			std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
			return ret;
		}
		int arg;
		int * ret;
		Barrier& barrier;
	public :
		SleepJob(int arg, int * ret, Barrier& b) : arg(arg), ret(ret), barrier(b) {}
		void run () {
			* ret = calcul(arg);
			barrier.done();
		}
		~SleepJob(){}
	};

	class DrawJob : public Job {
		void compute(int x, int y, Color * pixels, Scene * scene, Scene::screen_t & screen, vector<Vec3D>& lights) {
			// le point de l'ecran par lequel passe ce rayon
			auto & screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon  ray(scene->getCameraPos(), screenPoint);

			int targetSphere = findClosestInter(*scene, ray);

			if (targetSphere == -1) {
				// keep background color
				return;
			} else {
				const Sphere & obj = *(scene->begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene->getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color & pixel = pixels[y*scene->getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
			}
		}
		int x;
		int y;
		Color * pixels;
		Scene * scene;
		Scene::screen_t& screen;
		vector<Vec3D>& lights;
	public :
		DrawJob(int x, int y, Color * pixels, Scene * scene, Scene::screen_t & screen, vector<Vec3D>& lights) :
			x(x),
			y(y),
			pixels(pixels),
			scene(scene),
			screen(screen),
			lights(lights)
			{

			}
		void run () {
			compute(x,y,pixels,scene,screen,lights);
		}
		~DrawJob(){}
	};

}
