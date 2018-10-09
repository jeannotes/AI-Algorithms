#ifndef GRAPH_SEGMENTATION_H
#define GRAPH_SEGMENTATION_H

#include <opencv2/opencv.hpp>
#include "image_graph.h"

#define RAND() ( (float) std::rand() / ( RAND_MAX ) )

class GraphSegmentationDistance {
  public:
    GraphSegmentationDistance(){};
    virtual ~GraphSegmentationDistance(){};
    virtual float operator()( const ImageNode& n, const ImageNode& m ) = 0;
};

class GraphSegmentationManhattenRGB : public GraphSegmentationDistance {
  public:
    GraphSegmentationManhattenRGB() {
        // Normalization.
        D = 255 + 255 + 255;
    }

    virtual float operator()( const ImageNode& n, const ImageNode& m ) {
        float dr = std::abs( n.r - m.r );
        float dg = std::abs( n.g - m.g );
        float db = std::abs( n.b - m.b );

        return ( dr + dg + db );
    }

  private:
    float D;
};

class GraphSegmentationManhattenXYZ : public GraphSegmentationDistance {
  public:
    GraphSegmentationManhattenXYZ() {
        // Normalization.
        D = 100 + 100 + 100;
    }

    virtual float operator()( const ImageNode& n, const ImageNode& m ) {
        float dx = std::abs( n.x - m.x );
        float dy = std::abs( n.y - m.y );
        float dz = std::abs( n.z - m.z );

        return ( dx + dy + dz );
    }

  private:
    float D;
};

class GraphSegmentationEuclideanRGB : public GraphSegmentationDistance {
  public:
    GraphSegmentationEuclideanRGB() {
        // Normalization.
        D = std::sqrt( 255 * 255 + 255 * 255 + 255 * 255 );
    }

    virtual float operator()( const ImageNode& n, const ImageNode& m ) {
        float dr = n.r - m.r;
        float dg = n.g - m.g;
        float db = n.b - m.b;

        return std::sqrt( dr * dr + dg * dg + db * db );
    }

  private:
    float D;
};

class GraphSegmentationEuclideanXYZ : public GraphSegmentationDistance {
  public:
    GraphSegmentationEuclideanXYZ() {
        // Normalization.
        D = std::sqrt( 100 * 100 + 100 * 100 + 100 * 100 );
    }

    virtual float operator()( const ImageNode& n, const ImageNode& m ) {
        float dx = std::abs( n.x - m.x );
        float dy = std::abs( n.y - m.y );
        float dz = std::abs( n.z - m.z );

        return std::sqrt( dx * dx + dy * dy + dz * dz );
    }

  private:
    float D;
};

class GraphSegmentationMagic {
  public:
    GraphSegmentationMagic(){};
    virtual bool operator()( const ImageNode& S_n, const ImageNode& S_m, const ImageEdge& e ) = 0;
};

class GraphSegmentationMagicThreshold : public GraphSegmentationMagic {
  public:
    GraphSegmentationMagicThreshold( float c ) : c( c ){};
    virtual bool operator()( const ImageNode& S_n, const ImageNode& S_m, const ImageEdge& e ) {
        float threshold = std::min( S_n.max_w + c / S_n.n, S_m.max_w + c / S_m.n );
        if ( e.w < threshold ) { return true; }

        return false;
    }

  private:
    float c;   // threshold
};

class GraphSegmentation {
  public:
    GraphSegmentation()
        : distance( new GraphSegmentationManhattenRGB() ),
          magic( new GraphSegmentationMagicThreshold( 1 ) ){};
    virtual ~GraphSegmentation(){};
    void setDistance( GraphSegmentationDistance* _distance ) { distance = _distance; }
    void setMagic( GraphSegmentationMagic* _magic ) { magic = _magic; }
    void buildGraph( const cv::Mat& image );
    void oversegmentGraph();
    void enforceMinimumSegmentSize( int M );
    cv::Mat deriveLabels();   // Derive labels from the produced oversegmentation, return labels as
                              // integer matrix

  protected:
    int H, W;
    ImageGraph graph;
    GraphSegmentationDistance* distance;
    GraphSegmentationMagic* magic;
};

#endif
