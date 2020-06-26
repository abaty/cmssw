#ifndef DATAFORMATS_SISTRIPAPPROXIMATECLUSTER_H
#define DATAFORMATS_SISTRIPAPPROXIMATECLUSTER_H

#include <vector>
#include <numeric>
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class SiStripApproximateCluster  {
public:
  
  SiStripApproximateCluster() {}

  explicit SiStripApproximateCluster(uint16_t firstStrip, uint16_t width, uint8_t avgCharge): firstStrip_(firstStrip), width_(width), avgCharge_(avgCharge) {}

  uint16_t firstStrip() const {return firstStrip_;}
  uint16_t width() const {return width_;}
  uint8_t  avgCharge() const{return avgCharge_;} 

private:

  uint16_t                firstStrip_ = 0;

  uint8_t                 width_ = 0; 

  uint8_t                 avgCharge_ = 0;
};
#endif // DATAFORMATS_SISTRIPAPPROXIMATECLUSTER_H
