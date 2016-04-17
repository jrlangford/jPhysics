#pragma once

#ifndef SPRINGLINKT_H
#define SPRINGLINKT_H

#include "Particle.h"
#include "VecNormalizer.h"

namespace jrl{

	template <typename T>
	class SpringLinkT{
	public:

		typedef typename T::point_type point_type;

		T* partA;
		T* partB;

		bool isBroken;
		float springForce;
		
		//point_type oldSpeed;
		VecNormalizer<point_type> normalizer;
		//VecNormalizer<point_type> speedNormalizer;

		SpringLinkT();
		void setParticles(T* _partA, T* _partB);
		void setConstant(float k);
		void setRestPosition(float pos);
		void solve();
	private:
		//point_type tempSpringForceVec;
		//point_type pointDiff;
		float restPosition;
		float springConstant;
		//VecNormalizer<Point> pair;
	};

	//Implementation
	
	template <typename T>
	inline SpringLinkT<T>::SpringLinkT(){
		springConstant = 0.1f;
		isBroken = false;
	}

	template <typename T>
	inline void SpringLinkT<T>::setParticles(T* _partA, T* _partB){
		partA = _partA;
		partB = _partB;
		//normalizer.setPoints(&(partB->pos), &(partA->pos)); 
		normalizer.setPoints(&(partA->pos), &(partB->pos)); 
		//speedNormalizer.setPoints(&(partB->speed), &(partA->speed)); 
	}

	template <typename T>
	inline void SpringLinkT<T>::setConstant(float k){
		springConstant = k;
	}

	template <typename T>
	inline void SpringLinkT<T>::setRestPosition(float pos){
		restPosition = pos;
	}

	template <typename T>
	inline void SpringLinkT<T>::solve(){

		if(!isBroken){
			normalizer.update();

		
			//Add spring force to total force
			float totalForce = springConstant * (normalizer.getMag()-restPosition);

			//float dampingConstant = 2*sqrt(partA->getMass() * springConstant);
			float dampingConstant = 0.07;
			//float dampingConstant = 0.1;
			
			point_type speedDiff(partB->speed - partA->speed);

			//Add damping force to total force
			totalForce += dampingConstant * speedDiff.getDot(normalizer.getVec());

			//Project total force over distance vector
			point_type totalForceVec = totalForce * normalizer.getNorm();
			partA->newAccel+= totalForceVec * partA->getMassInverse();
			partB->newAccel+= totalForceVec * -partB->getMassInverse();

			//if(springForce>4){
			//	isBroken = true;
			//}
		}
		
	}

	//template <typename T>
	//inline void SpringLinkT<T>::solve(){

	//	if(!isBroken){
	//		normalizer.update();

	//		springForce = springConstant * (normalizer.getMag()-restPosition);

	//		partA->newAccel+=normalizer.getNorm() * springForce * partA->getMassInverse();
	//		partB->newAccel+=normalizer.getNorm() * -springForce * partB->getMassInverse();

	//		//if(springForce>4){
	//		//	isBroken = true;
	//		//}
	//	}
	//	
	//}

	//Damping is important so it works locally instead of globally
		//point_type speedVec(partB->speed - partA->speed); 
		//float dampingForce = -0.005 * speedVec.getMag();
		//Project speed vectors on spring vectors and calculate force
		//float dampingForce = -0.002 * (
		//	partB->speed.dot(normalizer.getVec())
		//	- partA->speed.dot(normalizer.getVec())
		//	);

		//Project resulting force on X and Y

		//float dampingForce = -0.0002 * (
		//	normalizer.getVec().dot(partA->speed)
		//	-normalizer.getVec().dot(partB->speed)
		//);

		//float springForce = -springConstant * (10-normalizer.getMag()) - dampingForce;

	//template <typename T>
	//inline void SpringLinkT<T>::solve(){
	//	//for(int i=0;i<15;++i){
	//	//normalizer.update();

	//	//point_type correctionVecHalf = 	0.5*normalizer.getDiff()*(1-(10*normalizer.getMagInv()));
	//	//if(!partA->getStatic()){
	//	//partA->pos+=correctionVecHalf;
	//	//}

	//	//if (!partB->getStatic()){
	//	//	partB->pos-=correctionVecHalf; 
	//	//}
	//	//}
	//	//normalizer.update();
	//	//speedNormalizer.update();
	//	//20 great number
	//	//if(normalizer.getMag()>4){
	//	//ofVec2f speedA(partA->speed.x, partA->speed.y);
	//	//ofVec2f speedB(partB->speed.x, partB->speed.y);
	//	//ofVec2f vDiff(normalizer.getDiff().x,normalizer.getDiff().y); 

	//	//float dampingForce = - 0.8*(speedA.dot(vDiff) - speedB.dot(vDiff));
	//
	//	//point_type diff(partA->pos - partB->pos);
	//	////10 is the sqrt of mag
	//	//partA->newAccel+=springConstant * (20-diff) * partA->getMassInverse();
	//	//partB->newAccel+=-springConstant * (20-diff) * partB->getMassInverse();
	//}
}

#endif