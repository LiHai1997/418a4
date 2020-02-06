#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> node;
  std::shared_ptr<Object> node1, node2;
  std::shared_ptr<MeshTriangle> meshTriangle1, meshTriangle2;
  std::shared_ptr<AABBTree> tree1, tree2;

  if (box_box_intersect(rootA->box, rootB->box))
  {
  	queue.push_back(std::make_pair(rootA, rootB));
  }
  while(!queue.empty()){
  	node = queue.front();
  	node1 = node.first;
  	node2 = node.second;
  	queue.pop_front();

  	meshTriangle1 = std::dynamic_pointer_cast<MeshTriangle>(node1);
  	meshTriangle2 = std::dynamic_pointer_cast<MeshTriangle>(node2);

  	if (meshTriangle1 && meshTriangle2)
  	{
  		leaf_pairs.push_back(std::make_pair(meshTriangle1, meshTriangle2));
  	}else if (meshTriangle1)
  	{
  		node = queue.front();
  		tree1 = std::dynamic_pointer_cast<AABBTree>(node2);
  		if (box_box_intersect(node1->box, tree2->left->box))
  		{
  			queue.push_back(std::make_pair(node1, tree2->left));
  		}
  		if (box_box_intersect(node1->box, tree2->right->box))
  		{
  			queue.push_back(std::make_pair(node1, tree2->right));
  		}
  	}else if (meshTriangle2)
  	{
  		tree1 = std::dynamic_pointer_cast<AABBTree>(node1);
  		if (box_box_intersect(node2->box, tree1->left->box))
  		{
  			queue.push_back(std::make_pair(tree1->left, node2));
  		}
  		if (box_box_intersect(node2->box, tree1->right->box))
  		{
  			queue.push_back(std::make_pair(tree1->right, node2));
  		}
  	}else
  	{
  		tree1 = std::dynamic_pointer_cast<AABBTree>(node1);
  		tree2 = std::dynamic_pointer_cast<AABBTree>(node2);

  		if (box_box_intersect(tree1->left->box, tree2->left->box))
  		{
  			queue.push_back(std::make_pair(tree1->left, tree2->left));
  		}
  		if (box_box_intersect(tree1->left->box, tree2->right->box))
  		{
  			queue.push_back(std::make_pair(tree1->left, tree2->right));
  		}
  		if (box_box_intersect(tree1->right->box, tree2->left->box))
  		{
  			queue.push_back(std::make_pair(tree1->right, tree2->left));
  		}
  		if (box_box_intersect(tree1->right->box, tree2->right->box))
  		{
  			queue.push_back(std::make_pair(tree1->right, tree2->right));
  		}
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
