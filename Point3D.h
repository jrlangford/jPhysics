//#pragma once //Including this directive removes VS 2010 warning on namespace declaration

#ifndef POINT3D_H
#define POINT3D_H

#include "math.h"
#include "Utilities/Utilities.h"
//#include "utilities.h"
#include"JPhysicsUtils.h"

namespace jrl{

	class Point3D{

	public:

		typedef point_3D_tag point_category;
		typedef Point3D point_type;

		//Variables
		float x;
		float y;
		float z;

		//Constructors
		Point3D();
		explicit Point3D(float f);
		Point3D(float x, float y, float z);
		//Copy constructor left with default implementation

		void set(const float _all);
		void set(float x, float y, float z);
		void set(const Point3D& point);

		float getMag() const;
		float getDot( const Point3D& vec ) const;
		Point3D getCrossed(const Point3D& vec) const;

		//Operator overloading for Point3D


		//Uses default copy assignment operation
		Point3D operator+(const Point3D& rhs) const;
		Point3D& operator+=(const Point3D& rhs);
		Point3D operator-(const Point3D& rhs) const;
		Point3D& operator-=(const Point3D& rhs);
		Point3D operator*(const Point3D& rhs) const;
		Point3D& operator*=(const Point3D& rhs);
		Point3D operator/(const Point3D& rhs) const;
		Point3D& operator/=(const Point3D& rhs);
		//Negative operator
		Point3D  operator-() const;
		
		

		//Operator overloading for float
		//Float assignment
		Point3D& operator=(const float rhs);
		Point3D operator+(const float rhs) const;
		Point3D& operator+=(const float rhs);
		Point3D operator-(const float rhs) const;
		Point3D& operator-=(const float rhs);
		Point3D operator*(const float rhs) const;
		Point3D& operator*=(const float rhs);
		Point3D operator/(const float rhs) const;
		Point3D& operator/=(const float rhs);


	private:
		//No private members
		
	};

	//----------------------------------------------------------------------------
	//Impementation

	inline Point3D::Point3D():x(0), y(0), z(0){
	}

	inline Point3D::Point3D(float all): x(all), y(all), z(all){
	}

	inline Point3D::Point3D(float _x, float _y, float _z):x(_x), y(_y), z(_z){
	}

	inline void Point3D::set(const Point3D& point){
		x = point.x;
		y = point.y;
		z = point.z;
	}

	inline void Point3D::set(const float _all){
		x=_all;
		y=_all;
		z=_all;
	}
	//Set operation
	inline void Point3D::set(float _x, float _y, float _z){
		x=_x;
		y=_y;
		z=_z;
	}

	inline float Point3D::getMag() const {
		return sqrt(x*x + y*y + z*z);
	}

	inline float Point3D::getDot( const Point3D& vec ) const {
		return x*vec.x + y*vec.y + z*vec.z;
	}

	inline Point3D Point3D::getCrossed( const Point3D& vec ) const {
	return Point3D( y*vec.z - z*vec.y,
				   z*vec.x - x*vec.z,
				   x*vec.y - y*vec.x );
	}

	//Member operators for Point3D objects

	inline Point3D Point3D::operator+(const Point3D& rhs) const{
		return Point3D(x + rhs.x, y + rhs.y, z+rhs.z);
	}

	inline Point3D& Point3D::operator+=(const Point3D& rhs){
		x+=rhs.x;
		y+=rhs.y;
		z+=rhs.z;
		return *this;	
	}

	inline Point3D Point3D::operator-(const Point3D& rhs) const{
		return Point3D(x-rhs.x, y-rhs.y, z-rhs.z);
	}

	inline Point3D& Point3D::operator-=(const Point3D& rhs){
		x-=rhs.x;
		y-=rhs.y;
		z-=rhs.z;
		return *this;
	}

	inline Point3D Point3D::operator*(const Point3D& rhs) const{
		return Point3D(x*rhs.x, y*rhs.y, z*rhs.z);
	}

	inline Point3D& Point3D::operator*=(const Point3D& rhs){
		x*=rhs.x;
		y*=rhs.y;
		z*=rhs.z;
		return *this;
	}

	inline Point3D Point3D::operator/(const Point3D& rhs) const{
		return Point3D(x/nonZero(rhs.x), y/nonZero(rhs.y), z/nonZero(rhs.z));
	}

	inline Point3D& Point3D::operator/=(const Point3D& rhs){
		x/=nonZero(rhs.x);
		y/=nonZero(rhs.y);
		z/=nonZero(rhs.z);
		return *this;
	}

	inline Point3D Point3D::operator-() const{
		return Point3D(-x,-y,-z);
	}
	//Member operators for float

	inline Point3D& Point3D::operator=(const float rhs){
		x=rhs;
		y=rhs;
		z=rhs;
		return *this;
	}

	inline Point3D Point3D::operator+(const float rhs) const{
		return Point3D(x+rhs, y+rhs, z+rhs);
	}

	inline Point3D& Point3D::operator+=(const float rhs){
		x+=rhs;
		y+=rhs;
		z+=rhs;
		return *this;
	}

	inline Point3D Point3D::operator-(const float rhs) const{
		return Point3D(x - rhs, y - rhs, z-rhs);
	}

	inline Point3D& Point3D::operator-=(const float rhs){
		x-=rhs;
		y-=rhs;
		z-=rhs;
		return *this;
	}

	inline Point3D Point3D::operator*(const float rhs) const{
		return Point3D(x*rhs, y*rhs, z*rhs);
	}

	inline Point3D& Point3D::operator*=(const float rhs){
		x*=rhs;
		y*=rhs;
		z*=rhs;
		return *this;
	}

	inline Point3D Point3D::operator/(float rhs) const{
		rhs = nonZero(rhs);
		return Point3D(x/rhs, y/rhs, z/rhs);
	}

	inline Point3D& Point3D::operator/=(float rhs){
		rhs = nonZero(rhs);
		x/=rhs;
		y/=rhs;
		z/=rhs;
		return *this;
	}
}

//Non-Member operators
jrl::Point3D operator+(float lhs, const jrl::Point3D& rhs);
jrl::Point3D operator-(float lhs, const jrl::Point3D& rhs);
jrl::Point3D operator*(float lhs, const jrl::Point3D& rhs);
jrl::Point3D operator/(float lhs, const jrl::Point3D& rhs);

inline jrl::Point3D operator+(float lhs, const jrl::Point3D& rhs) {
	return rhs.operator+(lhs);
};

inline jrl::Point3D operator-(float lhs, const jrl::Point3D& rhs){
	return jrl::Point3D(lhs) - rhs;
};

inline jrl::Point3D operator*( float lhs, const jrl::Point3D& rhs){
	return rhs.operator*(lhs);
};

inline jrl::Point3D operator/( float lhs, const jrl::Point3D& rhs){
	return jrl::Point3D(lhs)/rhs;
};

#endif