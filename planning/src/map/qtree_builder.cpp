#include <vector>
#include <cmath>

#include "qtree_builder.h"
#include "image_utils.h"

using namespace srcl_ctrl;
using namespace cv;

/*
 * @param _src: grayscale image, max size: 2^16 * 2^16 = 65535 * 65535 pixels
 * @param max_depth: maximum depth of the tree to be built
 */
QuadTree* QTreeBuilder::BuildQuadTree(cv::InputArray _src, unsigned int max_depth)
{
	Mat image_bin;
	Mat image_map;
	Mat src = _src.getMat();

	// binarize grayscale image
	ImageUtils::BinarizeImage(src, image_bin, 200);

	// pad image to 2^n on each side so that we can calculate
	//	the dimension of the grid more conveniently
	ImageUtils::PadImageToSquared(image_bin, image_map);

	// Create quadtree
	QuadTree *tree = new QuadTree(image_map.cols, max_depth);

	if(max_depth > tree->MAX_DEPTH)
	{
		max_depth = tree->MAX_DEPTH;
		std::cout << "Maximum depth allowed is 32. Only 32 levels will be built." << std::endl;
	}

	std::vector<QuadTreeNode*> parent_nodes;

	for(int grown_depth = 0; grown_depth <= max_depth; grown_depth++)
	{
#ifdef DEBUG
		std::cout << "growth level:" << grown_depth << std::endl;
#endif
		// root level
		if(grown_depth == 0)
		{
			BoundingBox bbox;
			bbox.x.min = 0;
			bbox.x.max = image_map.cols - 1;
			bbox.y.min = 0;
			bbox.y.max = image_map.rows - 1;

			OccupancyType map_occupancy;
			map_occupancy = ImageUtils::CheckAreaOccupancy(image_map, bbox);

			tree->root_node_ = new QuadTreeNode(bbox, map_occupancy);

			// if map is empty, terminate the process
			if(map_occupancy != OccupancyType::MIXED)
			{
				tree->root_node_->node_type_ = NodeType::LEAF;
				return tree;
			}

			// prepare for next iteration
			parent_nodes.clear();
			parent_nodes.push_back(tree->root_node_);
		}
		// lower levels
		else
		{
			std::vector<QuadTreeNode*> inner_nodes;

			while(!parent_nodes.empty())
			{
				// divide the parent area
				QuadTreeNode* parent = parent_nodes.at(0);

				/* opencv image coordinate:
				 * 	0 - > x
				 * 	|
				 * 	v
				 * 	y
				 */
				BoundingBox bbox[4];
				OccupancyType occupancy[4];

				// top left area
				bbox[0].x.min = parent->bounding_box_.x.min;
				bbox[0].x.max = parent->bounding_box_.x.min + (parent->bounding_box_.x.max - parent->bounding_box_.x.min + 1)/2 - 1;
				bbox[0].y.min = parent->bounding_box_.y.min;
				bbox[0].y.max = parent->bounding_box_.y.min + (parent->bounding_box_.y.max - parent->bounding_box_.y.min + 1)/2 - 1;

				// top right area
				bbox[1].x.min = bbox[0].x.max + 1;
				bbox[1].x.max = parent->bounding_box_.x.max;
				bbox[1].y.min = bbox[0].y.min;
				bbox[1].y.max = bbox[0].y.max;

				// bottom left area
				bbox[2].x.min = bbox[0].x.min;
				bbox[2].x.max = bbox[0].x.max;
				bbox[2].y.min = bbox[0].y.max + 1;
				bbox[2].y.max = parent->bounding_box_.y.max;

				// bottom right area
				bbox[3].x.min = bbox[1].x.min;
				bbox[3].x.max = bbox[1].x.max;
				bbox[3].y.min = bbox[2].y.min;
				bbox[3].y.max = bbox[2].y.max;

				for(int i = 0; i < 4; i++)
				{
#ifdef DEBUG
					std::cout << "bounding box " << i <<": " << "x " << bbox[i].x.min << "-" << bbox[i].x.max
							<< " y " << bbox[i].y.min << "-" << bbox[i].y.max << std::endl;
#endif

					occupancy[i] = ImageUtils::CheckAreaOccupancy(image_map, bbox[i]);
					parent->child_nodes_[i] = new QuadTreeNode(bbox[i], occupancy[i]);

					if(grown_depth < max_depth)
					{
						// first push back this node for further dividing
						inner_nodes.push_back(parent->child_nodes_[i]);

						// check and assign node type
						if(occupancy[i] != OccupancyType::MIXED)
						{
							if(parent->node_type_ != NodeType::INNER)
							{
								parent->child_nodes_[i]->node_type_ = NodeType::DUMMY_INNER;

								if(parent->node_type_ == NodeType::LEAF)
								{
									parent->child_nodes_[i]->dummy_root_ = parent;
									parent->has_dummy_ = true;
								}
								else
									parent->child_nodes_[i]->dummy_root_ = parent->dummy_root_;
							}
							else
								parent->child_nodes_[i]->node_type_ = NodeType::LEAF;
						}
					}
					else
					{
						// assign node type as leaf
						if(parent->node_type_ != NodeType::INNER)
						{
							parent->child_nodes_[i]->node_type_ = NodeType::DUMMY_LEAF;

							if(parent->node_type_ == NodeType::LEAF)
							{
								parent->child_nodes_[i]->dummy_root_ = parent;
								parent->has_dummy_ = true;
							}
							else
								parent->child_nodes_[i]->dummy_root_ = parent->dummy_root_;
						}
						else
							parent->child_nodes_[i]->node_type_ = NodeType::LEAF;

						// generate index for the node
						uint16_t x,y;
						x = ((bbox[i].x.min + bbox[i].x.max + 1)/2)/tree->cell_res_;
						y = ((bbox[i].y.min + bbox[i].y.max + 1)/2)/tree->cell_res_;
						tree->node_manager_->SetNodeReference(x,y,parent->child_nodes_[i]);
					}
				}

				// delete the processed node
				parent_nodes.erase(parent_nodes.begin());
			}

			// prepare for next iteration
			parent_nodes.clear();
			parent_nodes = inner_nodes;
		}

		tree->tree_depth_++;
	}

	// Store all leaf nodes into a vector
	tree->leaf_nodes_ = QTreeBuilder::GetAllLeafNodes(tree);

	return tree;
}

std::tuple<QuadTree*, cv::Mat> QTreeBuilder::BuildQuadTreeMap(cv::InputArray _src, unsigned int max_depth)
{
	Mat image_bin;
	Mat image_map;
	Mat src = _src.getMat();

	// binarize grayscale image
	ImageUtils::BinarizeImage(src, image_bin, 200);

	// pad image to 2^n on each side so that we can calculate
	//	the dimension of the grid more conveniently
	ImageUtils::PadImageToSquared(image_bin, image_map);

	QuadTree *tree = QTreeBuilder::BuildQuadTree(_src, max_depth);

	return std::make_tuple(tree, image_map);
}

std::vector<QuadTreeNode*> QTreeBuilder::GetAllLeafNodes(QuadTree *tree)
{
	std::vector<QuadTreeNode*> leaves;

	if(tree != nullptr)
	{
		std::vector<QuadTreeNode*> parent_nodes;

		for(int i = 0; i < tree->tree_depth_; i++)
		{
			if(i == 0)
			{
				if(tree->root_node_->node_type_ != NodeType::LEAF)
				{
					for(int i = 0; i < 4; i++)
					{
						parent_nodes.clear();
						parent_nodes.push_back(tree->root_node_);
					}
				}
				else
				{
					leaves.push_back(tree->root_node_);
					break;
				}
			}
			else
			{
				std::vector<QuadTreeNode*> inner_nodes;

				while(!parent_nodes.empty())
				{
					QuadTreeNode* parent = parent_nodes.at(0);

					for(int i = 0; i < 4; i++)
					{
						if(parent->child_nodes_[i]->node_type_ == NodeType::INNER)
							inner_nodes.push_back(parent->child_nodes_[i]);
						else if(parent->child_nodes_[i]->node_type_ == NodeType::LEAF)
							leaves.push_back(parent->child_nodes_[i]);
					}

					// delete the processed node
					parent_nodes.erase(parent_nodes.begin());
				}

				// prepare for next iteration
				parent_nodes.clear();
				parent_nodes = inner_nodes;
			}
		}
	}

	// Assign id to tree leaf nodes
	std::vector<QuadTreeNode*>::iterator it;
	uint64_t id = 0;
	for(it = leaves.begin(); it != leaves.end(); it++)
	{
		(*it)->node_id_ = id;
		id++;
	}

	return leaves;
}
