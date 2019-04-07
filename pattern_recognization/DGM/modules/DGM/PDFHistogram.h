// Histogram-based Probability Density function class
// Written by Sergey Kosov in 2015 for Project X
#pragma once

#include "IPDF.h"

namespace DirectGraphicalModels
{
// ================================ Histogram PDF Class ==============================
/**
	* @brief Histogram-based PDF class (1D)
	* @details This class makes use of distribution histograms in order to estimate the PDF. The length of the histogram is 255, 
	* thus arguments \b point of the addPoint() and getDensity() functions should be also in range [0; 255].
	* @author Sergey G. Kosov, sergey.kosov@project-10.de
	*/
class CPDFHistogram : public IPDF {
  public:
    CPDFHistogram( void );
    virtual ~CPDFHistogram( void );

    virtual void reset( void );

    virtual void addPoint( Scalar point );
    virtual double getDensity( Scalar point );
    virtual Scalar min( void ) const { return Scalar( 0 ); }
    virtual Scalar max( void ) const { return Scalar( 255 ); }

    /**
		* @brief Performs the gaussian smoothing on the histogram
		* @details Performs \b nIt iterations of gaussian smothing of the histograms in order to overcome the "over-fitting" problem
		* @param nIt Number of iterations
		*/
    void smooth( int nIt = 1 );

  protected:
    virtual void saveFile( FILE* pFile ) const;
    virtual void loadFile( FILE* pFile );

  private:
    long m_data[256];
};
}