// Base abstract class for random model triplets training
// Written by Sergey G. Kosov in 2015 for Project X
#pragma once

#include "ITrain.h"
#include "PriorTriplet.h"
#include "macroses.h"   // For DGM_WARNING

namespace DirectGraphicalModels
{
// ============================= Triplet Train Class =============================
/**
	@brief  Base abstract class for triplet potential training
	@author Sergey G. Kosov, sergey.kosov@project-10.de
	*/
class CTrainTriplet : public ITrain, private CPriorTriplet {
  public:
    CTrainTriplet( byte nStates, byte nFeatures )
        : CBaseRandomModel( nStates )
        , ITrain( nStates, nFeatures )
        , CPriorTriplet( nStates ) {}
    ~CTrainTriplet( void ) {}

    void reset( void ) { CPriorTriplet::reset(); }

    void train( bool doClean = false ) {}

    Mat getTripletPotentials( const Mat& featureVector1, const Mat& featureVector2, const Mat& featureVector3 ) const;

  protected:
    /**
		* @todo Implement save() function
		* @warning This function is not implemented
		*/
    void saveFile( FILE* pFile ) const { DGM_WARNING( "Save function is not implemented yet!" ); }
    /**
		* @todo Implement load() function
		* @warning This function is not implemented
		*/
    void loadFile( FILE* pFile ) { DGM_WARNING( "Load function is not implemented yet!" ); }

    void calculateTripletPotentials( const Mat& featureVector1, const Mat& featureVector2, const Mat& featureVector3 ) const;
};
}
