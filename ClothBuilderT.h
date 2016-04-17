#pragma once

#ifndef CLOTHBUILDERT_H
#define CLOTHBUILDERT_H

#include "ParticleGridT.h"
#include "SpringLinkT.h"
//#include "Collection2DT.h"
#include "jDataStructures/Collection2DT.h"

namespace jrl{

	template <typename T>
	class ClothBuilderT:public ParticleGridT<T>{

	public:

		

		//typedefs
		typedef typename T::point_type point_type;
		typedef SpringLinkT<ParticleKD> SpringLinkKD;
		typedef typename std::vector<SpringLinkKD>::iterator springIt;
		typedef typename std::vector<SpringLinkKD>::reverse_iterator springRevIt;
		typedef Collection2DT<SpringLinkKD> SpringGrid;

		//Spring Vars
		std::vector<SpringLinkKD> springLinks;
		//std::vector<SpringLinkKD> diagSpringLinks;
		SpringGrid diagSpringLinks;
		
		std::vector<SpringLinkKD> torsionSpringLinks;		
		
		float dampingFactor;
		
		float gravityAcceleration;		
		bool gravityEnabled;

		//UI vars
		float springConstant;

		ClothBuilderT();
		~ClothBuilderT();

		void init(const point_type& _frameSize, int cols, int rows);
		void solve();		
		void setSpringKForAll(float _springConstant);

	private:

		void initBoundSprings();
		void initDiagSprings();
		void initTorsionSprings();
		void initCyclicSprings();
	};

	//Implementation

	template <typename T>
	ClothBuilderT<T>::ClothBuilderT(){

	}

	template <typename T>
	ClothBuilderT<T>::~ClothBuilderT(){

	}

	template <typename T>
	void ClothBuilderT<T>::init(const point_type& _frameSize, int cols, int rows){
		frameSize.set(_frameSize);
		//gridCols = cols;
		//gridRows = rows;
		
		gravityAcceleration = 30;

		float step = frameSize.x/(cols-1);

		initGrid(cols, rows, step);

		//Add mass to particles
		partIt partRun = getParticles().begin();
		while(partRun!=getParticles().end()){
			partRun->setMass(0.3f);
			//Set damping force
			partRun->damping.set(dampingFactor);
			++partRun;
		}

		

		initBoundSprings();
		//initDiagSprings();
		//initTorsionSprings();
		//initCyclicSprings();

		std::cout<<"---------------------------"<<std::endl;
	}

	//--------------------------------------------------------------
	template <typename T>
	void ClothBuilderT<T>::solve(){
	
		//springIt selectedSpring = springLinks.begin() + 2*particleSelector;
		springIt springFwdRun = springLinks.begin();
		while(springFwdRun!=springLinks.end()){
			springFwdRun->solve();
			++springFwdRun;
		}

		//springFwdRun = diagSpringLinks.getObjects().begin();
		//	while(springFwdRun!=diagSpringLinks.getObjects().end()){
		//	springFwdRun->solve();
		//	++springFwdRun;
		//}

		////springIt selectedSpring = springLinks.begin() + 2*particleSelector;
		//springFwdRun = torsionSpringLinks.begin();
		//	while(springFwdRun!=torsionSpringLinks.end()){
		//	springFwdRun->solve();
		//	++springFwdRun;
		//}
	
		partIt partRun = getParticles().begin();
		if(gravityEnabled){
			while(partRun!=getParticles().end()){
				partRun->newAccel.y+=gravityAcceleration; 
				//partRun->damping.set(dampingFactor);
				partRun->update();
				++partRun;
			}
		} else{
			while(partRun!=getParticles().end()){
				//partRun->damping.set(dampingFactor);
				partRun->update();
				++partRun;
			}
		}
	}

	template <typename T>
	void ClothBuilderT<T>::setSpringKForAll(float _springConstant){
		springConstant = _springConstant;
		springIt springFwdRun = springLinks.begin();
		while(springFwdRun!=springLinks.end()){
			springFwdRun->setConstant(springConstant);
			++springFwdRun;
		} 
	}

	template <typename T>
	void ClothBuilderT<T>::initBoundSprings(){

		//Number of links is height*(width-1) + width(height-1)
		std::vector<SpringLinkKD>& activeLinks = springLinks;
		activeLinks.clear();

		int springGridWidth = gridCols -1;
		int springGridHeight = gridRows -1;
		int numOfSprings = 2*numOfParticles - gridCols - gridRows;

		SpringLinkKD springTemplate;
		springTemplate.setConstant(springConstant);
		//springTemplate.setRestPosition(step);
		springTemplate.setRestPosition(0);
		activeLinks.insert(activeLinks.cend(), numOfSprings, springTemplate);
		std::cout<<"Constraining Spring Links inserted: "<<activeLinks.size()<<std::endl;

		int springIndex = 0;
		int partIndex= 0;
		int yIndex = 0;
		for(int y = 0; y<springGridHeight; ++y){
			for(int x = 0; x<springGridWidth; ++x){
				partIndex = yIndex + x;

				activeLinks[springIndex].setParticles( 
					&getParticles()[partIndex],
					&getParticles()[partIndex+1]
				);
				++springIndex;
				activeLinks[springIndex].setParticles( 
					&getParticles()[partIndex],
					&getParticles()[partIndex + gridCols]
				);
				++springIndex;
			}
			yIndex+=gridCols;
		}

		//Fill last row
		partIndex = gridCols*(gridRows-1);
		for(int i=0; i<springGridWidth;++i){
			activeLinks[springIndex].setParticles( 
					&getParticles()[partIndex],
					&getParticles()[partIndex+1]
			);
			++partIndex;
			++springIndex;
		}

		//Fill last column
		partIndex = gridCols - 1;
		yIndex = 0;
		for(int i=0;i<springGridHeight;++i){
			activeLinks[springIndex].setParticles( 
				&getParticles()[partIndex],
				&getParticles()[partIndex + gridCols]
			);
			partIndex+=gridCols;
			++springIndex;
		}

		std::cout<<"Constraining Spring Links initialized: "<<springIndex<<std::endl;
	}

	template <typename T>
	void ClothBuilderT<T>::initDiagSprings(){

		//Number of links is height*(width-1) + width(height-1)
		SpringGrid& activeLinks = diagSpringLinks;

		activeLinks.getObjects().clear();

		int springGridWidth = gridCols -1;
		int springGridHeight = gridRows -1;
		int numOfSprings = 2*springGridWidth*springGridHeight;

		SpringLinkKD springTemplate;
		springTemplate.setConstant(springConstant);
		//springTemplate.setRestPosition(step);
		springTemplate.setRestPosition(0);
		
		diagSpringLinks.init(2*springGridWidth, springGridHeight);
		std::cout<<"Shear Force Spring Links inserted: "<<activeLinks.getObjects().size()<<std::endl;

		springIt spring = activeLinks.getObjects().begin();
		partIt part = getParticles().begin(); 

		for(int y = 0; y<springGridHeight; ++y){
			for(int x = 0; x<springGridWidth; ++x){
				spring->setParticles( 
					&(*part),
					&(*lookRight(lookDown(part)))
				);
				++spring;

				goRight(part);

				spring->setParticles( 
					&(*part),
					&(*lookLeft(lookDown(part)))
				);
				++spring;
			}
			goRight(part);//Skip last particle column
		}
		
		std::cout<<"Shear Force Spring Links initialized: "<<activeLinks.getObjects().size()<<std::endl;
	}

	//--------------------------------------------------------------
	template <typename T>
	void ClothBuilderT<T>::initTorsionSprings(){

		//Number of links is height*(width-1) + width(height-1)
		std::vector<SpringLinkKD>& activeLinks = torsionSpringLinks;
		activeLinks.clear();

		int linkStep=2;

		int springGridWidth = gridCols - linkStep; //Gridwidth - range of spring
		int springGridHeight = gridRows - linkStep ;
		int numOfSprings = 2*(gridCols - linkStep)*(gridRows- linkStep)
			+linkStep*(gridCols - linkStep) + linkStep*(gridRows - linkStep);

	
		SpringLinkKD springTemplate;
		springTemplate.setConstant(springConstant);
		springTemplate.setRestPosition(linkStep*step);
		activeLinks.insert(activeLinks.cend(), numOfSprings, springTemplate);
		std::cout<<"Torsion Spring Links inserted: "<<activeLinks.size()<<std::endl;

		int springIndex = 0;
		int partIndex= 0;
		int yIndex = 0;
		int yLinkStep = linkStep*gridCols;
		for(int y = 0; y<springGridHeight; ++y){
			for(int x = 0; x<springGridWidth; ++x){
				partIndex = yIndex + x;

				activeLinks[springIndex].setParticles( 
					&particles[partIndex],
					&particles[partIndex+2]
				);
				++springIndex;
				activeLinks[springIndex].setParticles( 
					&particles[partIndex],
					&particles[partIndex + yLinkStep]
				);
				++springIndex;
			}
			yIndex+=gridCols;
		}

		//Fill last rows
		for (int m= 0; m<linkStep; ++m){
			partIndex = gridCols*((springGridHeight+m));
			for(int i=0; i<springGridWidth;++i){
				activeLinks[springIndex].setParticles( 
					&particles[partIndex],
					&particles[partIndex+2]
				);
				++partIndex;
				++springIndex;
			} 
		}

		//Fill last column
		for (int m=0; m<linkStep; ++m){
			partIndex = springGridWidth + m;
			yIndex = 0;
			for(int i=0;i<springGridHeight;++i){
				activeLinks[springIndex].setParticles( 
					&particles[partIndex],
					&particles[partIndex + yLinkStep]
				);
				partIndex+=gridCols;
				++springIndex;
			} 
		}

		std::cout<<"Constraining Spring Links initialized: "<<springIndex<<std::endl;
	}

	//--------------------------------------------------------------
	template <typename T>
	void ClothBuilderT<T>::initCyclicSprings(){
	
		//int springGridWidth = gridCols -1;
		//int springGridHeight = gridRows -1;
		int numOfSprings = 2*numOfParticles;
		springLinks.insert(springLinks.cend(), numOfSprings, SpringLinkKD());
		std::cout<<"Spring Links inserted: "<<springLinks.size()<<std::endl;

		int springIndex = 0;
		int partIndex = 0;
		int rightPartIndex = 0;
		int downPartIndex = 0;
		for(int y = 0; y<gridRows; ++y){
			for(int x = 0; x<gridCols; ++x){

				partIndex = y*gridCols + x;
				rightPartIndex = partIndex + 1;
				downPartIndex = partIndex + gridCols;
				if(x==gridCols-1){
					rightPartIndex-=gridCols;
					//springLinks[springIndex].normalizer.offset.set(-step*(gridCols), 0);
					//springLinks[springIndex].normalizer.diffIsCyclic = true;
				}
				if(y==gridRows-1){
					downPartIndex%=gridCols;
					//springLinks[springIndex].normalizer.offset.set(0, -step*(gridRows));
					//springLinks[springIndex].normalizer.diffIsCyclic = true;
				}
			
				springLinks[springIndex].setParticles( 
					&particles[partIndex],
					&particles[rightPartIndex]
				);
				++springIndex;
				springLinks[springIndex].setParticles( 
					&particles[partIndex],
					&particles[downPartIndex]
				);
				++springIndex;
			}
		}

		std::cout<<"Spring Links initialized: "<<springIndex<<std::endl;
	}

}
#endif