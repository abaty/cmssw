#ifndef RecoLocalTracker_SiStripClusters2ApproxClusters_h
#define RecoLocalTracker_SiStripClusters2ApproxClusters_h

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"

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

  edm::Service<TFileService> fs;

  edm::InputTag inputClusters;
  edm::EDGetTokenT< edmNew::DetSetVector<SiStripCluster> > clusterToken;  

  TTree* stripTree_;

  uint32_t event;
  std::vector< uint32_t > detectorID;
  std::vector< std::vector< uint16_t >> firstStrip;
  std::vector< std::vector< uint8_t > > widths;

  void clearVectors();
};

void SiStripClusters2ApproxClusters::clearVectors(){
  event = 0;
  detectorID.clear();
  firstStrip.clear();
  widths.clear();
}

DEFINE_FWK_MODULE(SiStripClusters2ApproxClusters);
#endif

