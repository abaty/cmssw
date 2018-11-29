
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/Parse.h"

#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "DataFormats/Provenance/interface/RunLumiEventNumber.h"

#include <fstream>

class HI2018MBFilter : public edm::EDFilter {
  public:

    explicit HI2018MBFilter(const edm::ParameterSet & iConfig);
    ~HI2018MBFilter() override {}

  private:

    bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup) override;

    bool doADC12;
    bool doADC13;
    bool doADC14;
    bool doADC15;
    bool doADC16;    
};


HI2018MBFilter::HI2018MBFilter(const edm::ParameterSet & iConfig)
  : doADC12 (iConfig.getParameter< bool >("doADC12") ),
    doADC13 (iConfig.getParameter< bool >("doADC13") ),
    doADC14 (iConfig.getParameter< bool >("doADC14") ),
    doADC15 (iConfig.getParameter< bool >("doADC15") ),
    doADC16 (iConfig.getParameter< bool >("doADC16") )
{
  produces<bool>();
}


bool HI2018MBFilter::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) {
  bool pass = false;

  edm::RunNumber_t run = iEvent.id().run();

  bool hasADC12 = 
    (run >= 326381 && run <= 326384) || 
    (run >= 326390 && run <= 326476);
  if(doADC12 && hasADC12) pass = true;
  
  bool hasADC13 = 
    (run == 326477) || 
    (run >= 326479 && run <= 326518); 
  if(doADC13 && hasADC13) pass = true;
  
  bool hasADC14 = 
    (run == 326478) || 
    (run >= 326519 && run <= 326521); 
  if(doADC14 && hasADC14) pass = true;
  
  bool hasADC15 = 
    (run >= 326388 && run <= 326389) || 
    (run >= 326523 && run <= 327430) || 
    (run >= 327455);
  if(doADC15 && hasADC15) pass = true;

  bool hasADC16 = (run == 327431);
  if(doADC16 && hasADC16) pass = true;

  iEvent.put(std::make_unique<bool>(pass));

  return pass;
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(HI2018MBFilter);
