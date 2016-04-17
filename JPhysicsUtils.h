#pragma once

#ifndef JPHYSICSUTILS_H
#define JPHYSICSUTILS_H

namespace jrl{

	//Traits to be used on point types
	struct point_2D_tag{
	};

	struct point_3D_tag{
	};

	//Trait templates
	template <typename P>
	struct point_traits{ //Get traits from Point object
		typedef typename P::point_category point_category;
	};

	template <typename P>
	struct particle_traits:public point_traits<P>{
	};


	//template <>
	//struct point_traits<_additionalKnown2DType>{ //replace _additionalKnown type with desired 2D object
	//	typedef point_2D_tag iterator_category;
	//}

	//template <>
	//struct point_traits<_additionalKnown3DType>{ //replace _additionalKnown type with desired 2D object
	//	typedef point_3D_tag iterator_category;
	//}

}

#endif