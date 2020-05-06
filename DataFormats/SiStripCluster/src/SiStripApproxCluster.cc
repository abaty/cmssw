
#include "DataFormats/SiStripApproxCluster/interface/SiStripApproxCluster.h"

SiStripApproxCluster::SiStripApproxCluster(const SiStripCluster cluster) :
  firstStrip_(range.first->strip()),
  error_x(-99999.9)
{

  //fix this

  amplitudes_.reserve( range.second - range.first);
  
  uint16_t lastStrip=0;
  bool firstInloop = true;
  for (SiStripDigiIter i=range.first; i!=range.second; i++) {
    
    /// check if digis consecutive
    if (!firstInloop && i->strip() != lastStrip + 1) {
      for (int j=0; j < i->strip()-(lastStrip+1); j++) {
	amplitudes_.push_back( 0);
      }
    }
    lastStrip = i->strip();
    firstInloop = false;
    
    amplitudes_.push_back(i->adc()); 
  }
}
