#ifndef ApproxSiStripRecHitConverter_h
#define ApproxSiStripRecHitConverter_h

#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoLocalTracker/SiStripRecHitConverter/interface/ApproxSiStripRecHitConverterAlgorithm.h"
#include "DataFormats/SiStripApproximateClusterv2/interface/SiStripApproximateClusterv2.h"

class ApproxSiStripRecHitConverter : public edm::stream::EDProducer<>
{
  
 public:
  
  explicit ApproxSiStripRecHitConverter(const edm::ParameterSet&);
  void produce(edm::Event&, const edm::EventSetup&) override;
  
 private:
  
  ApproxSiStripRecHitConverterAlgorithm recHitConverterAlgorithm;
  std::string matchedRecHitsTag, rphiRecHitsTag, stereoRecHitsTag;
  edm::EDGetTokenT<edmNew::DetSetVector<SiStripApproximateClusterv2> > clusterProducer;

};
#endif
