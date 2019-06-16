#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  int i = 0;

  for (Model::Node node : this-> Nodes()){
    auto new_node = Node( i, this, node);
    m_Nodes.push_back(new_node);
    i++;

  }
}
