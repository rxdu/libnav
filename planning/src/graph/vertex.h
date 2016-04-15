/*
 * vertex.h
 *
 *  Created on: Feb 1, 2016
 *      Author: rdu
 */

#ifndef SRC_GRAPH_VERTEX_H_
#define SRC_GRAPH_VERTEX_H_

#include <iostream>

namespace srcl_ctrl {

/****************************************************************************/
/*								 Edge  										*/
/****************************************************************************/
/// An edge data structure template.
template<typename BundledVertexType>
class Edge
{
public:
	/**
	 * @param src a pointer to the source vertex of the edge
	 * @param dst a pointer to the destination vertex of the edge
	 * @param c cost associated with the edge
	 */
	Edge(BundledVertexType* src = nullptr, BundledVertexType* dst = nullptr, double c = 0.0):
		src_(src),dst_(dst), cost_(c){};
	~Edge(){};

	BundledVertexType* src_;
	BundledVertexType* dst_;
	double cost_;

	/**
	 * == operator overloading. If two edges connect the same pair of vertices, they're
	 * regarded as equal.
	 */
	bool operator ==(const Edge<BundledVertexType> other)
	{
		if((src_->vertex_id_ == other.src_->vertex_id_ && dst_->vertex_id_ == other.dst_->vertex_id_)
			|| (src_->vertex_id_ == other.dst_->vertex_id_ && dst_->vertex_id_ == other.src_->vertex_id_))
			return true;
		else
			return false;
	}

	/**
	 * Print edge information: start vertex id, destination vertex id, edge cost.
	 */
	void PrintEdge()
	{
		std::cout << "Edge: src - " << src_->vertex_id_ << " , dst - " << dst_->vertex_id_ << " , cost - " << cost_ << std::endl;
	}
};

/****************************************************************************/
/*								 Vertex										*/
/****************************************************************************/
/// A vertex data structure template.
template<typename BundledStructType>
class Vertex
{
public:
	/**
	 * @param bundled_data a reference to the bundled data structure
	 */
	Vertex(const BundledStructType &bundled_data):
		// attributes related to associated node
		bundled_data_(bundled_data), vertex_id_(bundled_data.node_id_),
		// common attributes
		search_parent_(nullptr),
		is_checked_(false), is_in_openlist_(false),
		f_astar_(0),g_astar_(0),h_astar_(0){};

	~Vertex(){
		edges_.clear();
	};

	const BundledStructType& bundled_data_;
	uint64_t vertex_id_;
	std::vector<Edge<Vertex<BundledStructType>>> edges_;

	// member variables for search
    template<typename GraphVertexType>
    friend class AStar;
private:
	bool is_checked_;
	bool is_in_openlist_;
	double f_astar_;
	double g_astar_;
	double h_astar_;
	Vertex<BundledStructType>* search_parent_;

public:
	/**
	 * == operator overloading. If two vertices have the same id, they're
	 * regarded as equal.
	 */
	bool operator ==(const Vertex<BundledStructType> other)
	{
		if(vertex_id_ == other.vertex_id_)
			return true;
		else
			return false;
	}

	void ClearVertexSearchInfo(){
		is_checked_ = false;
		is_in_openlist_ = false;
		search_parent_ = nullptr;

		f_astar_ = 0.0;
		g_astar_ = 0.0;
		h_astar_ = 0.0;
	}

	double GetEdgeCost(const Vertex<BundledStructType>& dst_node)
	{
		double cost = -1;

		for(const auto& it : edges_)
		{
			if(it.dst_.vertex_id_ == dst_node.vertex_id_)
			{
				cost = it.cost_;
				break;
			}
		}

		return cost;
	}

	std::vector<Vertex<BundledStructType>*> GetNeighbours()
	{
		std::vector<Vertex<BundledStructType>*> neighbours;

		for(const auto& edge:edges_)
			neighbours.push_back(edge.dst_);

		return neighbours;
	}

	bool CheckNeighbour(Vertex<BundledStructType>* dst_node)
	{
		std::vector<Vertex<BundledStructType>*> neighbours = GetNeighbours();

		auto it = find(neighbours.begin(), neighbours.end(), dst_node);

		if(it != neighbours.end())
			return true;
		else
			return false;
	}
};

}

#endif /* SRC_GRAPH_VERTEX_H_ */
