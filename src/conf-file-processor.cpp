
#include "conf-file-processor.hpp"

#include <ndn-cxx/name.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <iostream>
#include <fstream>


namespace autondn_man {
using namespace std;

ConfFileProcessor::ConfFileProcessor(AutoNdnMan& manf, std::string& confFileName)
  : m_manf(manf)
  , m_confFileName(confFileName)
{
}


bool
ConfFileProcessor::processConfFile() {

  bool ret = true;
  ifstream inputFile;
  inputFile.open(m_confFileName.c_str());
  if (!inputFile.is_open()) {
    string msg = "Failed to read configuration file: ";
    msg += m_confFileName;
    cerr << msg << std::endl;
    return false;
  }
  ret = load(inputFile);
  inputFile.close();
  return ret;
}

bool
ConfFileProcessor::load(std::istream& input) {
   ConfigSection pt;
   bool ret = true;
   try {
    boost::property_tree::read_info(input, pt);
  }
  catch (const boost::property_tree::info_parser_error& error) {
    stringstream msg;
    std::cerr << "Failed to parse configuration file " << std::endl;
    std::cerr << m_confFileName << std::endl;
    return false;
  }

  for (ConfigSection::const_iterator tn = pt.begin();
          tn != pt.end(); ++tn) {
            ret = processSection(tn->first, tn->second);
            if (ret == false) {
              break;
            }
  }
  return ret;
}

bool
ConfFileProcessor::processSection(const std::string& sectionName, const ConfigSection& section) {
  bool ret = true;
  if (sectionName == "general") {
    ret = processSectionGeneral(section);
  }
  else if (sectionName == "security") {
    ret = processSectionSecurity(section);
  }
  else {
    cerr << "Wrong configuration section: " << sectionName << endl;
  }
  return ret;
}

bool
ConfFileProcessor::processSectionGeneral(const ConfigSection& section) {
  try {
    string name = section.get<string>("name");

    ndn::Name manufactureName(name);
    if (!manufactureName.empty()) {
      m_manf.getConfParameter().setManName(manufactureName);
    }
    else {
      cerr << "Manufacturer name cannot be empty" << endl;
    }
  }
  catch(const std::exception& ex) {
    cerr << ex.what() << endl;
    return false;
  }
  return true;
}

bool
ConfFileProcessor::processSectionSecurity(const ConfigSection& section) {
  ConfigSection::const_iterator  it = section.begin();

  if (it == section.end() ||  it->first != "validator") {
    std::cerr << "Error: Expect validator section!" << std::endl;
    return false;
  }

  m_manf.loadValidator(it->second, m_confFileName);

  it++;

  for (; it != section.end(); it++) {
    using namespace boost::filesystem;

    if (it->first != "cert-to-publish") {
      std::cerr << "Error: Expect cert-to-publish!" << std::endl;
      return false;
    }

    std::string file = it->second.data();
    path certfilePath = absolute(file, path(m_confFileName).parent_path());
    shared_ptr<ndn::IdentityCertificate> idCert =
    ndn::io::load<ndn::IdentityCertificate>(certfilePath.string());

    if (idCert == nullptr) {
      std::cerr << "Error: Cannot load cert-to-publish: " << file << "!" << std::endl;
      return false;
    }

    m_manf.loadCertToPublish(idCert);
  }

  return true;
}

} // end of namespace autondn_man
