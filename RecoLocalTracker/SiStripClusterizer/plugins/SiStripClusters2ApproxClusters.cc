#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusters2ApproxClusters.h"
#include <iostream>


SiStripClusters2ApproxClusters::SiStripClusters2ApproxClusters(const edm::ParameterSet& conf){
   inputClusters = conf.getParameter< edm::InputTag >("inputClusters");
   clusterToken = consumes< edmNew::DetSetVector< SiStripCluster > >(inputClusters);

   produces< edmNew::DetSetVector< SiStripApproximateCluster > >(); 

   stripTree_ = fs->make<TTree>("stripTree","v1");
   stripTree_->Branch("event",&event,"event/I");
   stripTree_->Branch("detectorID",&detectorID);
   stripTree_->Branch("barycenters",&firstStrip);
   stripTree_->Branch("widths",&widths);

}

void SiStripClusters2ApproxClusters::produce(edm::Event& e, edm::EventSetup const&){
  clearVectors();

  event = (uint32_t)e.id().event();

  std::unique_ptr<edmNew::DetSetVector< SiStripApproximateCluster > > result(new edmNew::DetSetVector< SiStripApproximateCluster > );

  edm::Handle<edmNew::DetSetVector< SiStripCluster >> clusterCollection;
  e.getByToken(clusterToken, clusterCollection);

  uint32_t minID = 470444276;
  int maxFirst = -1;

  for( edmNew::DetSetVector<SiStripCluster>::const_iterator i = clusterCollection->begin(); i!=clusterCollection->end(); i++){

    detectorID.push_back((uint32_t) i->id());

    std::vector< SiStripApproximateCluster > tempVec;    

    edmNew::DetSetVector<SiStripApproximateCluster>::FastFiller ff = edmNew::DetSetVector<SiStripApproximateCluster>::FastFiller(*result, i->id());

    std::vector<uint16_t> tempFirstStrip;
    std::vector<uint8_t> tempWidth;
    for( edmNew::DetSet<SiStripCluster>::const_iterator j = i->begin(); j!=i->end(); j++){
      //std::cout << i->id() << " " << j->firstStrip() << " " << j->amplitudes().size() << " " << j->barycenter() << " " << minID << " " << maxFirst << std::endl;
      tempFirstStrip.push_back(j->barycenter()); 
      tempWidth.push_back(j->amplitudes().size());

      if(maxFirst<j->firstStrip()) maxFirst = j->firstStrip();
      if(minID>i->id()) minID = i->id();

      uint16_t firstStrip = j->firstStrip(); 
      uint8_t width = j->amplitudes().size();

      int charge = 0;
      for (unsigned k = 0; k < j->amplitudes().size(); k++) {
        charge += (int)j->amplitudes()[k];
        //std::cout << (int)j->amplitudes()[k] << " " ;
      }
      //std::cout << std::endl;

      SiStripApproximateCluster approxCluster = SiStripApproximateCluster( firstStrip, width, (uint8_t)(charge/width) );
      ff.push_back(approxCluster);
      //tempVec.push_back(approxCluster);      
    }
    firstStrip.push_back(tempFirstStrip);
    widths.push_back(tempWidth);    

    //edmNew::DetSet< SiStripApproximateCluster> tempDetSet = edmNew::DetSet< SiStripApproximateCluster>(i->id(), tempVec,0,0); 
    //std::cout << tempDetSet.size() << std::endl;

    //result->insert(tempDetSet);
  }

  
  //const edmNew::DetSetVector<SiStripCluster>&  clusters = *clusterCollection.product();



  //std::cout << clusters.size() << std::endl;

  stripTree_->Fill();
  e.put(std::move(result));
}


