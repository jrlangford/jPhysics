#ifndef POINTNORMALIZER_H
#define POINTNORMALIZER_H

#include "utilities.h"

namespace jrl{

	template <typename T>
	class PointNormalizer{
	public:
		T* pA;
		T* pB;
		PointNormalizer();
		PointNormalizer(T& _pA, T& _pB);
		void setPoints(T& _pA, T& _pB);
		void update();
		const T& getDiff() const;
		const float getMagSquared() const;
		const float getMag() const;
		const float getMagInv() const;
		const T& getNorm() const;
	private:
		T diff;
		float magSquared;
		float mag;
		float magInv;
		T norm; 

		void solveMagnitude(point_2D_tag);
		void solveMagnitude(point_3D_tag);
	};

	//Implementation
	template <typename T>
	inline PointNormalizer<T>::PointNormalizer(){
	}

	template <typename T>
	inline PointNormalizer<T>::PointNormalizer(T& _pA, T& _pB){
		setPoints(_pA, _pB);
	}

	template <typename T>
	void PointNormalizer<T>::setPoints(T& _pA, T& _pB){
		pA = &_pA;
		pB = &_pB;
		diff = _pA - _pB;
		solveMagnitude(typename point_traits<T>::point_category());
		norm = diff*magInv;
	}


	template <typename T>
	void PointNormalizer<T>::update(){
		diff = *pA - *pB;
		solveMagnitude(typename point_traits<T>::point_category());
		norm = diff*magInv;
	}

	template <typename T>
	inline const T& PointNormalizer<T>::getDiff() const{
		return diff;
	}

	template <typename T>
	inline const float PointNormalizer<T>::getMagSquared() const{
		return magSquared;
	}

	template <typename T>
	inline const float PointNormalizer<T>::getMag() const{
		return mag;
	}

	template <typename T>
	inline const float PointNormalizer<T>::getMagInv() const{
		return magInv;
	}

	template <typename T>
	inline const T& PointNormalizer<T>::getNorm() const{
		return norm;
	}

	template <typename T>
	inline void PointNormalizer<T>::solveMagnitude(point_2D_tag){
		magSquared = diff.x*diff.x + diff.y*diff.y;
		mag = sqrt(magSquared);
		magInv = 1/nonZero(mag);
		//std::cout<<"magS"<<endl;
	}

	template <typename T>
	inline void PointNormalizer<T>::solveMagnitude(point_3D_tag){
		magSquared = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
		mag = sqrt(magSquared);
		magInv = 1/nonZero(mag);
		
	}
}

#endif