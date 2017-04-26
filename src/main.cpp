#include "autondn-man.hpp"
#include "conf-file-processor.hpp"

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/util/scheduler.hpp>

#include <iostream>

class Error : public std::runtime_error {
public:
  explicit
  Error(const std::string& what)
    : std::runtime_error(what)
  {
  }
};

int main() {
  boost::asio::io_service ioService;
  ndn::Face face(ioService);
  ndn::util::Scheduler scheduler(face.getIoService());

  std::string confFileName = "auto-ndn-manu.conf";
  autondn_man::AutoNdnMan autoNdnMan(face, scheduler);
  autondn_man::ConfFileProcessor fileProcessor(autoNdnMan, confFileName);
  if (fileProcessor.processConfFile()) {
    std::cout << "Successful in reading conf file." << std::endl;
  }
  else {
    std::cout << "Error in configuration file processing! Exiting from Autondn" << std::endl;
    throw Error("Error in configuration file processing! Exiting from Autondn");
  }

  autoNdnMan.getConfParameter().printConfParameters();

  return 0;
}