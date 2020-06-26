#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusters2ApproxClusters.h"
#include <iostream>


SiStripClusters2ApproxClusters::SiStripClusters2ApproxClusters(const edm::ParameterSet& conf){
   inputClusters = conf.getParameter< edm::InputTag >("inputClusters");
   clusterToken = consumes< edmNew::DetSetVector< SiStripCluster > >(inputClusters);

   produces< edmNew::DetSetVector< SiStripApproximateCluster > >(); 

}

void SiStripClusters2ApproxClusters::produce(edm::Event& e, edm::EventSetup const&){
  std::unique_ptr<edmNew::DetSetVector< SiStripApproximateCluster > > result(new edmNew::DetSetVector< SiStripApproximateCluster > );

  edm::Handle<edmNew::DetSetVector< SiStripCluster >> clusterCollection;
  e.getByToken(clusterToken, clusterCollection);

  for( edmNew::DetSetVector<SiStripCluster>::const_iterator i = clusterCollection->begin(); i!=clusterCollection->end(); i++){

    std::vector< SiStripApproximateCluster > tempVec;    

    edmNew::DetSetVector<SiStripApproximateCluster>::FastFiller ff = edmNew::DetSetVector<SiStripApproximateCluster>::FastFiller(*result, i->id());

    for( edmNew::DetSet<SiStripCluster>::const_iterator j = i->begin(); j!=i->end(); j++){
      //std::cout << i->id() << " " << j->firstStrip() << " " << j->amplitudes().size() << std::endl;

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
    
    //edmNew::DetSet< SiStripApproximateCluster> tempDetSet = edmNew::DetSet< SiStripApproximateCluster>(i->id(), tempVec,0,0); 
    //std::cout << tempDetSet.size() << std::endl;

    //result->insert(tempDetSet);
  }

  
  //const edmNew::DetSetVector<SiStripCluster>&  clusters = *clusterCollection.product();



  //std::cout << clusters.size() << std::endl;

  e.put(std::move(result));
}


