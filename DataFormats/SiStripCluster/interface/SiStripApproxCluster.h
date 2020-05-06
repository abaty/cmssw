#ifndef DATAFORMATS_SISTRIPAPPROXCLUSTER_H
#define DATAFORMATS_SISTRIPAPPROXCLUSTER_H

#include "DataFormats/SiStripDigi/interface/SiStripDigi.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include <vector>
#include <numeric>
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class SiStripApproxCluster  {
public:
  static const uint16_t stripIndexMask = 0x7FFF;  // The first strip index is in the low 15 bits of firstStrip_
  static const uint16_t mergedValueMask = 0x8000;  // The merged state is given by the high bit of firstStrip_


  /** Construct from a range of digis that form a cluster and from 
   *  a DetID. The range is assumed to be non-empty.
   */
  
  SiStripApproxCluster(){};
  SiStripApproxCluster(const SiStripCluster cluster);

  //need constructor


  /** The number of the first strip in the cluster.
   *  The high bit of firstStrip_ indicates whether the cluster is a candidate for being merged.
   */
  uint16_t firstStrip() const {return firstStrip_ & stripIndexMask;}

  /** The amplitudes of the strips forming the cluster.
   *  The amplitudes are on consecutive strips; if a strip is missing
   *  the amplitude is set to zero.
   *  A strip may be missing in the middle of a cluster because of a
   *  clusterizer that accepts holes.
   *  A strip may also be missing anywhere in the cluster, including the 
   *  edge, to record a dead/noisy channel.
   *
   *  You can find the special meanings of values { 0, 254, 255} in section 3.4.1 of
   *  http://www.te.rl.ac.uk/esdg/cms-fed/firmware/Documents/FE_FPGA_Technical_Description.pdf
   */

  /** The barycenter of the cluster, not corrected for Lorentz shift;
   *  should not be used as position estimate for tracking.
   */
  float getBarycenter() const {return barycenter; }
  void setBarycenter( float barycenter_) { barycenter = barycenter_;}

  float getlength() const {return length; }
  void setlength( float length_) { length = length_;}
  /** total charge
   *
   */
  int getCharge() const {return charge; }
  void setCharge( int charge_) { charge = charge_;}

  /** Test (set) the merged status of the cluster
   *
   */
  bool isMerged() const {return (firstStrip_ & mergedValueMask) != 0;}
  void setMerged(bool mergedState) {mergedState ? firstStrip_ |= mergedValueMask : firstStrip_ &= stripIndexMask;}

  float getSplitClusterError () const    {  return error_x;  }
  void  setSplitClusterError ( float errx ) { error_x = errx; }


private:

  uint16_t length;

  int charge;
  
  float barycenter;

  uint16_t firstStrip_ = 0;

  float error_x = -999999; 
 
};

#endif // DATAFORMATS_SISTRIPCLUSTER_H
