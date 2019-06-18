#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  int i = 0;

  for (Model::Node node : this-> Nodes()){
    auto new_node = Node( i, this, node);
    m_Nodes.push_back(new_node);
    i++;

  }
  CreateNodeToRoadHashmap();
}
void RouteModel::CreateNodeToRoadHashmap(){
  for (const Model::Road &road : Roads()){
    if (road.type != Model::Road::Type::Footway){
      for (int node_idx : Ways()[road.way].nodes)
      {
        if (node_to_road.find(node_idx) == node_to_road.end()){
          node_to_road[node_idx] = std::vector<const Model::Road *>();
        }
        node_to_road[node_idx].push_back(&road);
      }
    }
  }
}
RouteModel::Node *RouteModel::Node::FindNeighbor(std::vector<int> node_indices){
  Node *closest_node = nullptr;
  Node node;
  for(int node_idx : node_indices){
    node = parent_model->SNodes()[node_idx];
    if(this->distance(node) != 0 && !node.visited){
      if(closest_node == nullptr || this -> distance(node) < this-> distance(*closest_node)){
        closest_node = &parent_model->SNodes()[node_idx];
      }
    }

  }
  return closest_node;
}
void RouteModel::Node::FindNeighbors(){
  for (auto & road : parent_model->node_to_road[this->index]){
    RouteModel::Node * node_pointer = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
    if(node_pointer != nullptr){
      this->neighbors.push_back(node_pointer);
    }
  }
}
