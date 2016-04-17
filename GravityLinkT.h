#pragma once
#ifndef GRAVITYLINKT_H
#define GRAVITYLINKT_H

#include "Particle.h"
#include "Point2D.h"
//#include "Point3D.h"
#include "PointNormalizer.h"

namespace jrl{

	template <typename T>
	class GravityLinkT{
	public:
		GravityLinkT();
		///@todo Implement correct copy constructor to handle pointers.
		//GravityLinkT(T* _partA, T* _partB);
		//GravityLinkT(PointNormalizer<T>* externalPair);
		~GravityLinkT();
		void setParticles(T* _partA, T* _partB);
		void solve();
	private:
		T* partA;
		T* partB;
		//PointNormalizer<typename T::point_type>* pair;
		//PointNormalizer<Point2D>* pair;
		PointNormalizer<Point2D> pair;
		bool isPairLocal;
		
	};

	//Implementation
	
	template <typename T>
	inline GravityLinkT<T>::GravityLinkT(){
		//pair = new PointNormalizer<typename T::point_type>();
		//pair = new PointNormalizer<typename T::point_type>();
		//createNewPairVec(typename particle_traits<T>::point_category());
	}

	//template <typename T>
	//inline GravityLinkT<T>::GravityLinkT(T* _partA, T* _partB):
	//isPairLocal(true){
	//	partA = _partA;
	//	partB = _partB;
	//	pair = new PointNormalizer<typename T::point_type>();
	//	//createNewPairVec(typename particle_traits<T>::point_category());
	//	pair->setPoints(_partA->pos, _partB->pos);
	//}

	template <typename T>
	inline void GravityLinkT<T>::setParticles(T* _partA, T* _partB){
		partA = _partA;
		partB = _partB;
		//pair = new PointNormalizer<typename T::point_type>();
		//pair =new PointNormalizer<Point2D>();
		////createNewPairVec(typename particle_traits<T>::point_category());
		//pair->setPoints(_partA->pos, _partB->pos);
		pair.setPoints(_partA->pos, _partB->pos);
		////isPairLocal = true;
	}

	//template <typename T>
	//inline GravityLinkT<T>::GravityLinkT(PointNormalizer<T>* externalPair):
	//isPairLocal(false){
	//	pair = externalPair;	
	//}

	template <typename T>
	inline GravityLinkT<T>::~GravityLinkT(){
		//if(isPairLocal){
			//Program crashes if delete is activated
			//When temp object is deleted the pointer to the "pair" in the vector is also deleted
			//delete pair;
		//}
	}

	template <typename T>
	inline void GravityLinkT<T>::solve(){
		//if(pair->getMag()>radiusSum){
			float strengthMagInv = 1/pair.getMagSquared();
				
			float gravAccelReceived = partB->getMass()*strengthMagInv;
			float gravAccelApplied = partA->getMass()*strengthMagInv;

			partA->newAccel+=(pair.getNorm() * gravAccelReceived);
			partB->newAccel+=(pair.getNorm() * gravAccelApplied);
		//} 
	}



}

#endif