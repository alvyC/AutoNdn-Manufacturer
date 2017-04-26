#ifndef AUTO_NDN_MAN_HPP
#define AUTO_NDN_MAN_HPP

#include <ndn-cxx/name.hpp>
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/util/scheduler.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/validator-config.hpp>
#include <ndn-cxx/security/signing-info.hpp>
#include <ndn-cxx/security/certificate-cache-ttl.hpp>

#include "conf-parameter.hpp"

namespace autondn_man {

//static ndn::Name MANUFACTURER_PREFIX("");

class AutoNdnMan {
public:
  AutoNdnMan(ndn::Face& face, ndn::util::Scheduler& scheduler);

  void
  initialize();

  ndn::Face&
  getFace() {
    return m_face;
  }

  void
  loadValidator(boost::property_tree::ptree section,
                         const std::string& fileName) {
    m_validator.load(section, fileName);
  }

  ndn::ValidatorConfig&
  getValidator() {
    return m_validator;
  }

  void
  loadCertToPublish(ndn::shared_ptr<ndn::IdentityCertificate> certificate) {
    //m_certStore.insert(certificate);
  }

  ndn::Name&
  getIdentityName() {
    return m_identityName;
  }

  ConfParameter&
  getConfParameter() {
    return m_confParameter;
  }

  ndn::security::SigningInfo&
  getSigningInfo() {
    return m_signingInfo;
  }

private:
  void
  initializeKey();


private:
  ndn::Face& m_face;
  ndn::Scheduler& m_scheduler;
  //ndn::security::CertificateStore m_certStore;

  ConfParameter m_confParameter;

  ndn::shared_ptr<ndn::CertificateCacheTtl> m_certificateCache;
  ndn::security::ValidatorConfig m_validator;
  ndn::KeyChain m_keyChain;
  ndn::security::SigningInfo m_signingInfo;
  ndn::Name m_identityName;
};
}

#endif