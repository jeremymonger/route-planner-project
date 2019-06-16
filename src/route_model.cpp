#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  i = 0

  for (Model::Node node : this-> Nodes()){
    new_node = Node(int i, this, node);
    m_Nodes.push_back(new_node);
    i++;
)
  }
}
