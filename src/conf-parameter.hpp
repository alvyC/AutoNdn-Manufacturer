#ifndef CONF_PARAMETER_HPP
#define CONF_PARAMETER_HPP

#include <ndn-cxx/name.hpp>

namespace autondn_man{
class ConfParameter {
public:
  ConfParameter();

  void
  setManName(ndn::Name manName) {
    m_manufactureName = manName;
  }

  ndn::Name
  getManName() const {
    return m_manufactureName;
  }

  void
  printConfParameters() const;

private:
  ndn::Name m_manufactureName;
};
}

#endif