#include "conf-parameter.hpp"

#include <iostream>

namespace autondn_man {

  ConfParameter::ConfParameter(){}

  void
  ConfParameter::printConfParameters() const {
    std::cout << "Manufacturer Name: " << m_manufactureName << std::endl;
  }
} // end of namespace autondn
