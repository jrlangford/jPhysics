#ifndef WORLDCONSTRAINTS2D_H
#define WORLDCONSTRAINTS2D_H

namespace jrl{
	
	template<typename T>
	class WorldConstraints2D{
	public:
		WorldConstraints2D();
		WorldConstraints2D(const T& _worldMin, const T& _worldMax);

		void setWorldConstraints(const T& _worldMin,const T& _worldMax);
		void setCollisionReturnValues(const T& _collisionReturnMin,const T& _collisionReturnMax);
		void checkCollision(T particle);
	private:
		T worldMin;
		T worldMax;
		T collisionReturnMin;
		T collisionReturnMax;
	};

	template<typename T>
	WorldConstraints2D<T>::WorldConstraints2D()
	{
	}

	template<typename T>
	WorldConstraints2D<T>::WorldConstraints2D(const T& _worldMin, const T& _worldMax):
		worldMin(_worldMin),
		worldMax(_worldMax)
	{
	}

	template<typename T>
	void WorldConstraints2D<T>::setWorldConstraints(const T& _worldMin,const T& _worldMax){
		worldMin = _worldMin;
		worldMax = _worldMax;
	}

	template<typename T>
	void WorldConstraints2D<T>::setCollisionReturnValues(const T& _collisionReturnMin,const T& _collisionReturnMax){
		collisionReturnMax=_collisionReturnMax;
		collisionReturnMin=_collisionReturnMin;
	}

	//template<typename T>
	//void WorldConstraints2D<T>::checkCollision(T particle){
	//	if(particle->currentPos.x
	//}
	
}

#endif