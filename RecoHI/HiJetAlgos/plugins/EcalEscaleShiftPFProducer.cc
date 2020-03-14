// -*- C++ -*-
//
// Package:    EcalEscaleShiftPFProducer
// Class:      EcalEscaleShiftPFProducer
// 
/**\class EcalEscaleShiftPFProducer EcalEscaleShiftPFProducer.cc RecoHI/EcalEscaleShiftPFProducer/src/EcalEscaleShiftPFProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/

// system include files
#include <memory>

// user include files
#include "RecoHI/HiJetAlgos/plugins/EcalEscaleShiftPFProducer.h"

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
EcalEscaleShiftPFProducer::EcalEscaleShiftPFProducer(const edm::ParameterSet& iConfig)
{
   //register your products  
  src_ = consumes<reco::PFCandidateCollection>(iConfig.getParameter<edm::InputTag>("src"));
  removePreshower_ = iConfig.getParameter<bool>("removePreshower");
  scaleEB_ = iConfig.getParameter<double>("scaleEB");
  scaleEE_ = iConfig.getParameter<double>("scaleEE");

  produces<reco::PFCandidateCollection>();
  
  //now do what ever other initialization is needed
  


}


EcalEscaleShiftPFProducer::~EcalEscaleShiftPFProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
EcalEscaleShiftPFProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<reco::PFCandidateCollection> inputsHandle;
   iEvent.getByToken(src_, inputsHandle);

   const reco::PFCandidateCollection pfcand = *(inputsHandle.product());


   auto prod = std::make_unique<reco::PFCandidateCollection>();
   
   for(reco::PFCandidateCollection::const_iterator pfcItr=pfcand.begin();
       pfcItr!=pfcand.end(); pfcItr++) {
     
     reco::PFCandidate scaledPFCand  = *pfcItr;
     
       
     if(pfcItr->particleId()==4){     
       if(fabs(pfcItr->eta())< 1.48) scaledPFCand.rescaleMomentum(scaleEB_);
       else{
	 if(!removePreshower_ || !(pfcItr->pS1Energy() + pfcItr->pS2Energy() >0 ) ) scaledPFCand.rescaleMomentum(scaleEE_);
	 else scaledPFCand.rescaleMomentum(scaleEE_*(1. - (pfcItr->pS1Energy() + pfcItr->pS2Energy())/pfcItr->energy()));
       }       
     }
     
     prod->push_back(scaledPFCand);
     
   }
   
   
   iEvent.put(std::move(prod));


}

// ------------ method called once each job just before starting event loop  ------------
void 
EcalEscaleShiftPFProducer::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
EcalEscaleShiftPFProducer::endJob() {
}

//define this as a plug-in                                                                                                                                                                                                                                                                
DEFINE_FWK_MODULE(EcalEscaleShiftPFProducer);
