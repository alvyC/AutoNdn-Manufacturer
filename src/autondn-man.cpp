#include "autondn-man.hpp"
#include <iostream>


namespace autondn_man {

AutoNdnMan::AutoNdnMan(ndn::Face& face, ndn::util::Scheduler& scheduler)
  : m_face(face)
  , m_scheduler(scheduler)
  , m_confParameter()
  , m_certificateCache(new ndn::CertificateCacheTtl(m_face.getIoService()))
  , m_validator(m_face, m_certificateCache)
  {
  }

  void
  AutoNdnMan::initializeKey() {
    std::cout << "initializeKey()" << std::endl;
  }

  void
  AutoNdnMan::initialize() {
    std::cout << "initialize()" << std::endl;
  }
}