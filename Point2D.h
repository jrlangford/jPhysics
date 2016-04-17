#pragma once //Including this directive removes VS 2010 warning on namespace declaration

#ifndef POINT2D_H
#define POINT2D_H

#include "Utilities/Utilities.h"
//#include "Utilities.h"
#include"JPhysicsUtils.h"

namespace jrl{

	class Point2D{

	public:

		typedef point_2D_tag point_category;
		typedef Point2D point_type;

		//Variables
		float x;
		float y;

		//Constructors
		Point2D();
		explicit Point2D(const float f);
		Point2D(const float x,const float y);
		//Copy constructor left with default implementation

		void set(const Point2D& point);
		void set(const float _all);
		void set(const float x, const float y);

		float getMag() const;
		float getDot(const Point2D& vec) const;
		//Operator overloading for Point2D


		//Uses default copy assignment operation
		Point2D operator+(const Point2D& rhs) const;
		Point2D& operator+=(const Point2D& rhs);
		Point2D operator-(const Point2D& rhs) const;
		Point2D& operator-=(const Point2D& rhs);
		Point2D operator*(const Point2D& rhs) const;
		Point2D& operator*=(const Point2D& rhs);
		Point2D operator/(const Point2D& rhs) const;
		Point2D& operator/=(const Point2D& rhs);
		//Negative operator
		Point2D  operator-() const;
		
		

		//Operator overloading for float
		//Float assignment
		Point2D& operator=(const float rhs);
		Point2D operator+(const float rhs) const;
		Point2D& operator+=(const float rhs);
		Point2D operator-(const float rhs) const;
		Point2D& operator-=(const float rhs);
		Point2D operator*(const float rhs) const;
		Point2D& operator*=(const float rhs);
		Point2D operator/(const float rhs) const;
		Point2D& operator/=(const float rhs);


	private:
		//No private members
		
	};

	//----------------------------------------------------------------------------
	//Impementation

	inline Point2D::Point2D():x(0), y(0){
	}

	inline Point2D::Point2D(const float all): x(all), y(all){
	}

	inline Point2D::Point2D(const float _x, const float _y):x(_x), y(_y){
	}

	inline void Point2D::set(const Point2D& point){
		x = point.x;
		y = point.y;
	}

	//Set operation
	inline void Point2D::set(const float _x,const float _y){
		x=_x;
		y=_y;
	}

	inline void Point2D::set(const float _all){
		x=_all;
		y=_all;
	}

	inline float Point2D::getMag() const {
		return sqrt(x*x + y*y);
	}

	inline float Point2D::getDot( const Point2D& vec ) const {
		return x*vec.x + y*vec.y;
	}

	//Member operators for Point2D objects

	inline Point2D Point2D::operator+(const Point2D& rhs) const{
		return Point2D(x + rhs.x, y + rhs.y);
	}

	inline Point2D& Point2D::operator+=(const Point2D& rhs){
		x+=rhs.x;
		y+=rhs.y;
		return *this;	
	}

	inline Point2D Point2D::operator-(const Point2D& rhs) const{
		return Point2D(x - rhs.x, y - rhs.y);
	}

	inline Point2D& Point2D::operator-=(const Point2D& rhs){
		x-=rhs.x;
		y-=rhs.y;
		return *this;
	}

	inline Point2D Point2D::operator*(const Point2D& rhs) const{
		return Point2D(x*rhs.x, y*rhs.y);
	}

	inline Point2D& Point2D::operator*=(const Point2D& rhs){
		x*=rhs.x;
		y*=rhs.y;
		return *this;
	}

	inline Point2D Point2D::operator/(const Point2D& rhs) const{
		return Point2D(x/nonZero(rhs.x), y/nonZero(rhs.y));
	}

	inline Point2D& Point2D::operator/=(const Point2D& rhs){
		x/=nonZero(rhs.x);
		y/=nonZero(rhs.y);
		return *this;
	}

	inline Point2D Point2D::operator-() const{
		return Point2D(-x,-y);
	}
	//Member operators for float

	inline Point2D& Point2D::operator=(const float rhs){
		x=rhs;
		y=rhs;
		return *this;
	}

	inline Point2D Point2D::operator+(const float rhs) const{
		return Point2D(x + rhs, y + rhs);
	}

	inline Point2D& Point2D::operator+=(const float rhs){
		x+=rhs;
		y+=rhs;
		return *this;
	}

	inline Point2D Point2D::operator-(const float rhs) const{
		return Point2D(x - rhs, y - rhs);
	}

	inline Point2D& Point2D::operator-=(const float rhs){
		x-=rhs;
		y-=rhs;
		return *this;
	}

	inline Point2D Point2D::operator*(const float rhs) const{
		return Point2D(x*rhs, y*rhs);
	}

	inline Point2D& Point2D::operator*=(const float rhs){
		x*=rhs;
		y*=rhs;
		return *this;
	}

	inline Point2D Point2D::operator/(const float rhs) const{
		return Point2D(x/nonZero(rhs), y/nonZero(rhs));
	}

	inline Point2D& Point2D::operator/=(const float rhs){
		x/=nonZero(rhs);
		y/=nonZero(rhs);
		return *this;
	}
}

//Non-Member operators
jrl::Point2D operator+(float lhs, const jrl::Point2D& rhs);
jrl::Point2D operator-(float lhs, const jrl::Point2D& rhs);
jrl::Point2D operator*(float lhs, const jrl::Point2D& rhs);
jrl::Point2D operator/(float lhs, const jrl::Point2D& rhs);

inline jrl::Point2D operator+(float lhs, const jrl::Point2D& rhs) {
	return rhs.operator+(lhs);
};

inline jrl::Point2D operator-(float lhs, const jrl::Point2D& rhs){
	return jrl::Point2D(lhs) - rhs;
};

inline jrl::Point2D operator*( float lhs, const jrl::Point2D& rhs){
	return rhs.operator*(lhs);
};

inline jrl::Point2D operator/( float lhs, const jrl::Point2D& rhs){
	return jrl::Point2D(lhs)/rhs;
};

#endif