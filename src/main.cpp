#include <iostream>
#include <sslworld.h>
#include <physics/pobject.h>

int main() {
	
	auto* world = new SSLWorld();
	dReal x,y,z;
	while(true) {
		auto& ball = world->ball;
		for( int i =0 ; i< 1; i++) {
			auto& r = world->robots[i];
			r->getXY(x,y);
			z = r->getID();
			std::cout << "ROBOT: " << z << " " << x << " " << y << " " << std::endl;
			r->setSpeed(0.1,0.1,0.1);
		}
		ball->getBodyPosition(x, y, z);
//		std::cout << "Hello, World!" << x << " " << y << " " << z << " " << std::endl;
		world->step(0.1);
	}
	return 0;
}