#ifndef DATAFORMATS_SISTRIPAPPROXIMATECLUSTERv2_H
#define DATAFORMATS_SISTRIPAPPROXIMATECLUSTERv2_H

#include <vector>
#include <numeric>
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class SiStripApproximateClusterv2  {
public:
  
  SiStripApproximateClusterv2() {}

  explicit SiStripApproximateClusterv2(uint8_t avgCharge, uint16_t barycenter, uint8_t width):avgCharge_(avgCharge) {
    baryWidth_ = barycenter;
    baryWidth_ = baryWidth_ << 6;
    if(width>63) width=63;
    baryWidth_ += width;
  }

  uint16_t barycenter() const {return (uint16_t)((baryWidth_ & 65472) >> 6);}
  uint8_t width() const {return (uint8_t) (baryWidth_ & 63);}
  uint8_t  avgCharge() const{return avgCharge_;} 

private:

  uint16_t                baryWidth_ = 0;

  uint8_t                 avgCharge_ = 0;
};
#endif // DATAFORMATS_SISTRIPAPPROXIMATECLUSTER_H
