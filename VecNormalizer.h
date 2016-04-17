#ifndef VECNORMALIZER_H
#define VECNORMALIZER_H

//#include "utilities.h"
#include "Utilities/Utilities.h"

namespace jrl{

	template <typename T>
	class VecNormalizer{
	public:
		T* pA;
		T* pB;
		//bool diffIsCyclic;
		//T offset;

		VecNormalizer();
		//VecNormalizer(T& _pA, T& _pB);
		void setPoints(T* _pA, T* _pB);
		void update();
		const T& getDiff() const;
		const T& getVec() const;
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
	inline VecNormalizer<T>::VecNormalizer(){
	}

	//template <typename T>
	//inline VecNormalizer<T>::VecNormalizer(T& _pA, T& _pB){
	//	setPoints(_pA, _pB);
	//}

	template <typename T>
	void VecNormalizer<T>::setPoints(T* _pA, T* _pB){
		pA = _pA;
		pB = _pB;
		update();
	}

	template <typename T>
	void VecNormalizer<T>::update(){

		diff = *pB - *pA;

		//if(diffIsCyclic){
		//	diff+=offset;
		//}
		solveMagnitude(typename point_traits<T>::point_category());
		norm = diff*magInv;
	}

	template <typename T>
	inline const T& VecNormalizer<T>::getDiff() const{
		return diff;
	}

	template <typename T>
	inline const T& VecNormalizer<T>::getVec() const{
		return diff;
	}

	template <typename T>
	inline const float VecNormalizer<T>::getMagSquared() const{
		return magSquared;
	}

	template <typename T>
	inline const float VecNormalizer<T>::getMag() const{
		return mag;
	}

	template <typename T>
	inline const float VecNormalizer<T>::getMagInv() const{
		return magInv;
	}

	template <typename T>
	inline const T& VecNormalizer<T>::getNorm() const{
		return norm;
	}

	template <typename T>
	inline void VecNormalizer<T>::solveMagnitude(point_2D_tag){
		magSquared = diff.x*diff.x + diff.y*diff.y;
		mag = sqrt(magSquared);
		magInv = 1/nonZero(mag);
	}

	template <typename T>
	inline void VecNormalizer<T>::solveMagnitude(point_3D_tag){
		magSquared = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
		mag = sqrt(magSquared);
		magInv = 1/nonZero(mag);
		
	}
}

#endif