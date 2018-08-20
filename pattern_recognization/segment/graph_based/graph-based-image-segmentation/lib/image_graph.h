#ifndef IMAGE_GRAPH_H
#define	IMAGE_GRAPH_H

#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>

class ImageEdge {
public:
    ImageEdge() : n(0), m(0), w(0) {};
    unsigned long int n, m;// first node, second node
    float w;/* Edge weight. */
};

class ImageEdgeSorter {
public:
    inline bool operator()(const ImageEdge & g, const ImageEdge h) {
        return (h.w > g.w);
    }
};

class ImageNode {
public:
    ImageNode() : b(0), g(0), r(0),
        x(0), y(0), z(0),
        l(0), n(1), id(0), max_w(0) {
    };
    unsigned char b, g, r;
    float x, y, z;// this is for pointcloud
    /**
     * label, i.e. the index of the node this node belongs to
     * size of node after merging with other nodes.
     * Id of the node.
    */
    unsigned long int l, n, id;// l = p, id = rank
    float max_w;/* weight */
};

class ImageGraph {
public:
    ImageGraph() {
        K = 0;
    };

    ImageGraph(int N) {
        nodes = std::vector<ImageNode>(N);
        K = N;
    }

    void operator=(const ImageGraph & graph) {
        nodes = graph.nodes;
        edges = graph.edges;
        K = graph.K;
    }

    void setNode(int n, ImageNode & node) {
        nodes[n] = node;
    }

    void addNode(ImageNode & node) {
        nodes.push_back(node);
        K++;
    }

    void addEdge(ImageEdge & edge) {
        edges.push_back(edge);
    }

    ImageNode & getNode(int n) {
        assert(n >= 0 && n < static_cast<int>(nodes.size()));
        return nodes[n];
    }

    ImageEdge & getEdge(int e) {
        assert(e >= 0 && e < static_cast<int>(edges.size()));
        return edges[e];
    }

    int getNumNodes() {
        return nodes.size();
    }

    int getNumEdges() {
        return edges.size();
    }

    int getNumComponents() {
        return K;
    }

    void sortEdges() {
        std::sort(edges.begin(), edges.end(), ImageEdgeSorter());
    }

    ImageNode & findNodeComponent(ImageNode & n) {
        int l = n.l;
        /**
         * label, i.e. the index of the node this node belongs to
         * Id of the node.
        */
        while (l != nodes[l].l) {
            l = nodes[l].l;
        }

        ImageNode & S = nodes[l];
        nodes[n].l = l;

        return S;
    }

    void merge(ImageNode & S_n, ImageNode & S_m, ImageEdge & e) {
        /**
         * here, merge means give the id to the label
         * so that next you find the label, just check it's label == id
        */
        S_m.l = S_n.id;
        S_n.n += S_m.n;
		if(S_m.id > S_n.id){
			S_n.l = S_m.l;
		}
        // Update maximum weight.
        S_n.max_w = std::max(std::max(S_n.max_w, S_m.max_w), e.w);
        K--;
    }
private:
    int K;//Number of components
    std::vector<ImageEdge> edges;
    std::vector<ImageNode> nodes;

};

#endif	/* IMAGE_GRAPH_H */

