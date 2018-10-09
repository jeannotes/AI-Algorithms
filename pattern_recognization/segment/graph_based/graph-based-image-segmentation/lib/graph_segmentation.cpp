#include "graph_segmentation.h"
#include <limits>

void GraphSegmentation::buildGraph( const cv::Mat& image ) {
    H = image.rows;
    W = image.cols;

    int N = H * W;
    graph = ImageGraph( N );

    for ( int i = 0; i < H; i++ ) {
        for ( int j = 0; j < W; j++ ) {
            int n           = W * i + j;
            ImageNode& node = graph.getNode( n );

            cv::Vec3b bgr = image.at< cv::Vec3b >( i, j );
            node.b        = bgr[0];
            node.g        = bgr[1];
            node.r        = bgr[2];

            // Initialize label.
            node.l  = n;
            node.id = 0;
            node.n  = 1;
        }
    }

    for ( int i = 0; i < H; i++ ) {
        for ( int j = 0; j < W; j++ ) {
            int n                 = W * i + j;
            const ImageNode& node = graph.getNode( n );

            if ( i < H - 1 ) {
                int m            = W * ( i + 1 ) + j;
                ImageNode& other = graph.getNode( m );

                ImageEdge edge;
                edge.n = n;
                edge.m = m;
                edge.w = ( *distance )( node, other );

                graph.addEdge( edge );
            }

            if ( j < W - 1 ) {
                int m            = W * i + ( j + 1 );
                ImageNode& other = graph.getNode( m );

                ImageEdge edge;
                edge.n = n;
                edge.m = m;
                edge.w = ( *distance )( node, other );

                graph.addEdge( edge );
            }
        }
    }
}

void GraphSegmentation::oversegmentGraph() {
    graph.sortEdges();

    for ( int e = 0; e < graph.getNumEdges(); e++ ) {
        ImageEdge edge = graph.getEdge( e % graph.getNumEdges() );

        ImageNode& n = graph.getNode( edge.n );
        ImageNode& m = graph.getNode( edge.m );

        ImageNode& S_n = graph.findNodeComponent( n );
        ImageNode& S_m = graph.findNodeComponent( m );

        // Are the nodes in different components?
        if ( S_m.id != S_n.id ) {
            // Here comes the magic!
            if ( ( *magic )( S_n, S_m, edge ) ) { graph.merge( S_n, S_m, edge ); }
        }
    }
}

void GraphSegmentation::enforceMinimumSegmentSize( int M ) {
    assert( graph.getNumNodes() > 0 );

    for ( int e = 0; e < graph.getNumEdges(); e++ ) {
        ImageEdge edge = graph.getEdge( e );

        ImageNode& n = graph.getNode( edge.n );
        ImageNode& m = graph.getNode( edge.m );

        ImageNode& S_n = graph.findNodeComponent( n );
        ImageNode& S_m = graph.findNodeComponent( m );

        if ( S_n.l != S_m.l ) {
            if ( S_n.n < M || S_m.n < M ) { graph.merge( S_n, S_m, edge ); }
        }
    }
}

cv::Mat GraphSegmentation::deriveLabels() {
    cv::Mat labels( H, W, CV_32SC1, cv::Scalar( 0 ) );
    for ( int i = 0; i < H; i++ ) {
        for ( int j = 0; j < W; j++ ) {
            int n = W * i + j;

            ImageNode& node   = graph.getNode( n );
            ImageNode& S_node = graph.findNodeComponent( node );

            const int max = std::numeric_limits< int >::max();

            labels.at< int >( i, j ) = S_node.id;
        }
    }

    return labels;
}