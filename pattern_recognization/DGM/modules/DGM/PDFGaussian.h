// Gaussian-based Probability Density function class
// Written by Sergey Kosov in 2015 for Project X
#pragma once

#include "IPDF.h"

namespace DirectGraphicalModels
{
// ================================ Histogram PDF Class ==============================
/**
	* @brief Gaissian-based PDF class
	* @details This class approximates PDF via Gaussian functions. 
	* @author Sergey G. Kosov, sergey.kosov@project-10.de
	*/
class CPDFGaussian : public IPDF {
  public:
    CPDFGaussian( void )
        : IPDF()
        , m_mu( 0 )
        , m_sigma2( 0 ) {}
    virtual ~CPDFGaussian( void ) {}

    virtual void reset( void );

    virtual void addPoint( Scalar point );
    virtual double getDensity( Scalar point );
    virtual Scalar min( void ) const { return Scalar( m_mu - 3 * sqrt( m_sigma2 ) ); }
    virtual Scalar max( void ) const { return Scalar( m_mu + 3 * sqrt( m_sigma2 ) ); }

  protected:
    virtual void saveFile( FILE* pFile ) const;
    virtual void loadFile( FILE* pFile );

  private:
    double m_mu;
    double m_sigma2;   // sigma^2
};
}
