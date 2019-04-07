#pragma once

#define DGM_VERSION_MAJOR 1
#define DGM_VERSION_MINOR 7
#define DGM_VERSION_PATCH 0

/* #undef DEBUG_MODE */
/* #undef DEBUG_PRINT_INFO */
/* #undef ENABLE_PPL */
/* #undef ENABLE_AMP */
/* #undef USE_OPENGL */
#define USE_SHERWOOD


#include <vector>
#include <memory>
#include <thread>
#include <math.h>
#ifdef ENABLE_PPL
#include <ppl.h>
#include "concrtrm.h"
#endif
#ifdef ENABLE_AMP
#include <amp.h>
#endif
#include "opencv2/opencv.hpp"

using namespace cv;

using byte	= uint8_t;
using word	= uint16_t;
using dword	= uint32_t;
using qword	= uint64_t;

using vec_mat_t			= std::vector<Mat>;
using vec_bool_t		= std::vector<bool>;
using vec_byte_t		= std::vector<byte>;
using vec_word_t		= std::vector<word>;
using vec_int_t			= std::vector<int>;
using vec_float_t		= std::vector<float>;
using vec_size_t		= std::vector<size_t>;
using vec_string_t		= std::vector<std::string>;
using vec_scalar_t		= std::vector<Scalar>;

using pair_mat_t		= std::pair<Mat, Mat>;
using ptr_float_t		= std::unique_ptr<float[]>;

static const double	Pi	= 3.1415926;			///< Pi number
static const float	Pif	= 3.1415926f;			///< Pi number

template <class T>  T& lvalue_cast(T&& t) { return t; }
#define EmptyMat	lvalue_cast(Mat())	

// DGM lib
namespace DirectGraphicalModels
{
	class IEdgeModel;
	
	using   vec_nColor_t	= std::vector<std::pair<Scalar, std::string> >;
	using 	ptr_edgeModel_t = std::shared_ptr<IEdgeModel>;
	const	size_t	STR_LEN	= 256; 
}
