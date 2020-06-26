#ifndef RecoLocalTracker_SiStripClusters2ApproxClusters_h
#define RecoLocalTracker_SiStripClusters2ApproxClusters_h

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/SiStripApproximateCluster/interface/SiStripApproximateCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/DetSetVector.h"

#include <vector>
#include <memory>

class SiStripClusters2ApproxClusters: public edm::stream::EDProducer<>  {

public:

  explicit SiStripClusters2ApproxClusters(const edm::ParameterSet& conf);
  void produce(edm::Event&, const edm::EventSetup&) override;

private:

  edm::InputTag inputClusters;
  edm::EDGetTokenT< edmNew::DetSetVector<SiStripCluster> > clusterToken;  
};

DEFINE_FWK_MODULE(SiStripClusters2ApproxClusters);
#endif

