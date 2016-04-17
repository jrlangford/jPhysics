#ifndef PARTICLE_H
#define	PARTICLE_H

//#include "utilities.h"
#include "Utilities/Utilities.h"

namespace jrl{

	template <typename T>
	class Particle{
	public:
		//Echo point type and category
		typedef typename T::point_category point_category;
		typedef typename T::point_type point_type;
		
		T accel;
		T speed;
		T pos;
		T newAccel;
		//T oldPos;
		T damping;

		static const float deltaTime;

		Particle();

		//Getters-Setters
		void setMass(float _mass);
		float getMass();
		float getMassInverse();
		void setRadius(float _radius);
		float getRadius();
		void setCollisionStatus(int status);
		int getCollisionStatus();

		void update();
		void setStatic(bool isStatic);
		bool getStatic();
		void clearDynamics();
		//void setNonStatic();

	private:
		bool collisionStatus;
		bool isFixed;
		float mass;
		float inverseMass;
		float radius;

	};
	//Implementation
	template <typename T>
	const float Particle<T>::deltaTime = 0.01f;
	//const float Particle<T>::deltaTime = 1;


	template <typename T>
	inline Particle<T>::Particle():
	isFixed(false),
	collisionStatus(0){

	}

	template <typename T>
	inline void Particle<T>::setMass(float _mass){
		mass = nonZero(_mass);
		inverseMass= 1/mass;
	}

	template <typename T>
	inline float Particle<T>::getMass(){
		return mass;
	}

	template <typename T>
	inline float Particle<T>::getMassInverse(){
		return inverseMass;
	}

	template <typename T>
	inline void Particle<T>::setRadius(float _radius){
		radius = _radius;
	}

	template <typename T>
	inline float Particle<T>::getRadius(){
		return radius;
	}

	template <typename T>
	inline void Particle<T>::setCollisionStatus(int status){
		collisionStatus=status;
	}

	template <typename T>
	inline int Particle<T>::getCollisionStatus(){
		return collisionStatus;
	}

	template <typename T>
	inline void Particle<T>::update(){
		if(!isFixed){
			accel=newAccel;
			//speed+=accel;
			speed=(speed + accel*deltaTime)*damping;
			//speed=(speed + accel*deltaTime)*damping;
			pos+=speed*deltaTime;
			newAccel.set(0);
			//newAccel = T(0);
		}
		//Compare current method with verlet integration
		//if (!isFixed){
		//	T temp(pos);
		//	speed = pos-oldPos;
		//	pos = pos + speed*damping + newAccel;
		//	oldPos = temp;
		//	newAccel.set(0);
		//}
	}

	template <typename T>
	inline void Particle<T>::setStatic(bool _isFixed){
		isFixed = _isFixed;
		newAccel = 0;
	}

	template <typename T>
	inline bool Particle<T>::getStatic(){
		return isFixed;
	}

	template <typename T>
	inline void Particle<T>::clearDynamics(){
		accel.set(0);
		speed.set(0);
		newAccel.set(0);
	}
	//template <typename T>
	//inline void Particle<T>::setNonStatic(){
	//	isNotStatic = true;
	//	//Clear accumulated acceleration particle received while static
	//	newAccel = 0;
	//}

}

#endif