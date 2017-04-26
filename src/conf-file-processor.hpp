#ifndef CONF_FILE_PROCESSOR_HPP
#define CONF_FILE_PROCESSOR_HPP

#include "autondn-man.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/cstdint.hpp>


namespace autondn_man {

class ConfFileProcessor {
public:
  ConfFileProcessor(AutoNdnMan& manf, std::string& confFileName);

  bool
  processConfFile();

private:
  typedef boost::property_tree::ptree ConfigSection;

  bool
  load(std::istream& input);

  bool
  processSection(const std::string& sectionName, const ConfigSection& section);

  bool
  processSectionGeneral(const ConfigSection& section);

  bool
  processSectionSecurity(const ConfigSection& section);

private:
  AutoNdnMan& m_manf;
  std::string m_confFileName;
};

} // end of namespace autondn_man

#endif // CONF_FILE_PROCESSOR_HPP