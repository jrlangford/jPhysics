#ifndef POINTCOMPARATOR2D_H
#define POINTCOMPARATOR2D_H

#include "utilities.h"

namespace jrl{

	template <typename T>
	class PointComparator2D{
	public:
		PointComparator2D();
		PointComparator2D(T& _pA, T& _pB);
		void setPoints(T& _pA, T& _pB);
		float getXDiff();
		float getYDiff();
		float getDistSquared();
		float getDist();
		float getDistInv();
		float getNormX();
		float getNormY();
	private:
		float xDiff;
		float yDiff;
		float distSquared;
		float dist;
		float distInv;
		float normX;
		float normY;
	};

	//Implementation
	template <typename T>
	inline PointComparator2D<T>::PointComparator2D(){
	}

	template <typename T>
	inline PointComparator2D<T>::PointComparator2D(T& _pA, T& _pB){
		setPoints(_pA, _pB);
	}

	template <typename T>
	inline void PointComparator2D<T>::setPoints(T& _pA, T& _pB){
		xDiff = _pA.x - _pB.x;
		yDiff = _pA.y - _pB.y;
		distSquared = xDiff*xDiff + yDiff*yDiff;
		dist = sqrt(distSquared);
		distInv = 1/nonZero(dist);
		normX = xDiff*distInv;
		normY = yDiff*distInv;
	}

	template <typename T>
	inline float PointComparator2D<T>::getXDiff(){
		return xDiff;
	}

	template <typename T>
	inline float PointComparator2D<T>::getYDiff(){
		return yDiff;
	}

	template <typename T>
	inline float PointComparator2D<T>::getDistSquared(){
		return distSquared;
	}

	template <typename T>
	inline float PointComparator2D<T>::getDist(){
		return dist;
	}

	template <typename T>
	inline float PointComparator2D<T>::getDistInv(){
		return distInv;
	}

	template <typename T>
	inline float PointComparator2D<T>::getNormX(){
		return normX;
	}

	template <typename T>
	inline float PointComparator2D<T>::getNormY(){
		return normY;
	}
}

#endif