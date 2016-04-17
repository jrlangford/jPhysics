#pragma once

#ifndef PARTICLEGRIDT_T
#define PARTICLEGRIDT_T

//#include "Collection2dT.h"
#include "jDataStructures/Collection2dT.h"

namespace jrl{

	template <typename T>
	class ParticleGridT:public Collection2DT<T>{
	public:

		//typedefs
		typedef typename T::point_type point_type;
		typedef typename std::vector<T>::iterator partIt; //Is the same as objIt
		typedef typename T ParticleKD; //Better suited for use outside this class

		//Frame vars
		point_type frameSize;


		int numOfParticles;

		float step;

		bool cornerAIsFixed;
		bool cornerBIsFixed;
		bool cornerCIsFixed;
		bool cornerDIsFixed;
		
		bool topBorderIsFixed;
		bool bottomBorderIsFixed;
		bool leftBorderIsFixed;
		bool rightBorderIsFixed;

		ParticleGridT();
		virtual ~ParticleGridT();

		void initGrid(int cols, int rows, float step);

		void fixPoints();

		void translatePartRange(partIt run,const partIt& end,const point_type& p);
		void seqTranslatePartRange(partIt run,const partIt& end, const point_type& p);

		void arrangeOnPlane(const point_type& colStep,const point_type& rowStep);

		std::vector<T>& getParticles();

	private:

	};

	//Implementation

	template <typename T>
	ParticleGridT<T>::ParticleGridT(){
	}

	template <typename T>
	ParticleGridT<T>::~ParticleGridT(){
	}

	template <typename T>
	void ParticleGridT<T>::initGrid(int cols, int rows, float _step){
		
		numOfParticles = cols*rows;
		init(cols, rows);
		
		std::cout<<"Particles inserted: "<<objects.size()<<std::endl;
		step = _step;

		//arrangeOnPlane();

		fixPoints();
	}

	template <typename T>
	void ParticleGridT<T>::fixPoints(){

		std::vector<T>& particles = objects;
		//Fix Particle Frame
		partIt partRun;

		//Left border
		partRun = particles.begin();
		while (partRun<particles.end()){
			partRun->setStatic(leftBorderIsFixed);
			goDown(partRun);
			//partRun+=gridCols;
		}
	
		//Bottom border
		//partRun=particles.end() - gridCols;
		partRun=lookUp(particles.end());
		while (partRun<particles.end()){
			partRun->setStatic(bottomBorderIsFixed);
			goRight(partRun);
			//++partRun;
		} 

		//Right Border
		//partRun=particles.end()-1;
		partRun=lookLeft(particles.end());
		while (partRun>particles.begin()){
			partRun->setStatic(rightBorderIsFixed);
			goUp(partRun);
			//partRun-=gridCols;
		} 

		//Top border
		partRun=particles.begin();	
		while (partRun<particles.begin() + gridCols){
			partRun->setStatic(topBorderIsFixed);
			goRight(partRun);
			//++partRun;
		} 


		//Fix particle edges
		particles.at(gridCols-1).setStatic(cornerAIsFixed || topBorderIsFixed || rightBorderIsFixed); 
		particles.front().setStatic(cornerBIsFixed || topBorderIsFixed || leftBorderIsFixed);
		(particles.end()-gridCols)->setStatic(cornerCIsFixed || bottomBorderIsFixed || rightBorderIsFixed);
		particles.back().setStatic(cornerDIsFixed || bottomBorderIsFixed || leftBorderIsFixed);
	}

	//--------------------------------------------------------------
	///Translates all the Particles;
	template <typename T>
	void ParticleGridT<T>::translatePartRange(partIt run,const partIt& end,const point_type& p){
		while(run!=end){
			run->pos+=p;
			++run;
		}
	}

	template <typename T>
	void ParticleGridT<T>::seqTranslatePartRange(partIt run,const partIt& end,const point_type& p){
		++run;
		while(run!=end){
			run->pos = (run-1)->pos + p;
			++run;
		}
	}

	template <typename T>
	void ParticleGridT<T>::arrangeOnPlane(const point_type& colStep, const point_type& rowStep){
		//point_type colStep(0,step,0);
		//point_type rowStep(step,0,0);
		
		std::vector<T>& particles = objects;

		partIt partRun = particles.begin() + gridCols;
		//Separate rows
		for(int i = 1; i<gridRows; ++i){
			translatePartRange(partRun, particles.end(), colStep);
			partRun+=gridCols;
		}

		//Separate columns
		partRun = particles.begin();
		for(int i = 0; i<gridRows; ++i){
			seqTranslatePartRange(partRun, partRun + gridCols, rowStep);
			partRun+=gridCols;
		}
	}

	template <typename T>
	inline std::vector<T>& ParticleGridT<T>::getParticles() {
		return objects;
	}

}
#endif