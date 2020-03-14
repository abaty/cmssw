#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "RecoBTau/JetTagComputer/interface/JetTagComputerESProducer.h"
#include "RecoBTag/CSVscikit/interface/CSVscikitTagger.h"

typedef JetTagComputerESProducer<CSVscikitTagger>        CSVscikitESProducer;
DEFINE_FWK_EVENTSETUP_MODULE(CSVscikitESProducer);
