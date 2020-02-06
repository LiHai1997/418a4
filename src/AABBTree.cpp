#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <math.h>
#include <Eigen/Geometry>
#include <iostream>


AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  if (objects.size() == 0)
  {
  	this->left = NULL;
  	this->right = NULL;
  }else if (objects.size() == 1)
  {
  	this->left = objects[0];
  	insert_box_into_box(this->left->box, this->box);
  	this->right = NULL;
  }else
  {
  	for (int i = 0; i < objects.size(); ++i)
  	{
  		insert_box_into_box(objects[i]->box, this->box);
  	}

  	auto x_len = abs(this->box.max_corner.x() - this->box.min_corner.x());
  	auto x_mid = (this->box.max_corner.x() + this->box.min_corner.x()) / 2.0;

  	auto y_len = abs(this->box.max_corner.y() - this->box.min_corner.y());
  	auto y_mid = (this->box.max_corner.y() + this->box.min_corner.y()) / 2.0;

  	auto z_len = abs(this->box.max_corner.z() - this->box.min_corner.z());
  	auto z_mid = (this->box.max_corner.z() + this->box.min_corner.z()) / 2.0;

  	std::vector<std::shared_ptr<Object>> left_tree, right_tree;
  	std::shared_ptr<Object> object;

  	for (int i = 0; i < objects.size(); ++i)
  	{
  		object = objects[i];
  		if (x_len > y_len && x_len > z_len)
  		{
  			if (object->box.center().x() < x_mid)
  			{
  				left_tree.push_back(object);
  			}else
  			{
  				right_tree.push_back(object);
  			}
  		}else if (y_len > z_len)
  		{
  			if (object->box.center().y() < y_mid)
  			{
  				left_tree.push_back(object);
  			}else
  			{
  				right_tree.push_back(object);
  			}
  		}else
  		{
  			if (object->box.center().z() < z_mid)
  			{
  				left_tree.push_back(object);
  			}else
  			{
  				right_tree.push_back(object);
  			}
  		}

  	}

  	if (left_tree.size() == objects.size())
  	{
  		for (int i = left_tree.size()/2; i < left_tree.size(); ++i)
  		{
  			right_tree.push_back(left_tree[i]);
  		}
  		left_tree.erase(left_tree.begin() + left_tree.size()/2, left_tree.end());
  	}else if (right_tree.size() == objects.size())
  	{
  		for (int i = right_tree.size()/2; i < right_tree.size(); ++i)
  		{
  			left_tree.push_back(right_tree[i]);
  		}
  		right_tree.erase(right_tree.begin() + right_tree.size()/2, right_tree.end());
  	}

  	if (left_tree.size() == 1)
  	{
  		this->left = left_tree[0];
  	}else if (left_tree.size() > 1)
  	{
  		this->left = std::make_shared<AABBTree>(left_tree, a_depth + 1);
  	}else 
  	{
  		throw;
  	}
  	if (right_tree.size() == 1)
  	{
  		this->right = right_tree[0];
  	}else if (right_tree.size() > 1)
  	{
  		this->right = std::make_shared<AABBTree>(right_tree, a_depth + 1);
  	}else 
  	{
  		throw;
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
