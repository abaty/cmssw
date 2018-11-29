import FWCore.ParameterSet.Config as cms
#for details of MB trigger, see
#https://twiki.cern.ch/twiki/bin/view/CMS/HIData2018

#L1 HF threshold in the HF trigger
#was changed throughout the run for various tests
#most of the data was taken on setting of '15'
L12018MBFilter = cms.EDFilter(
  "HI2018MBFilter",
  doADC12 = cms.bool(True),
  doADC13 = cms.bool(True),
  doADC14 = cms.bool(True),
  doADC15 = cms.bool(True),#most of hte high-lumi data taken with 15
  doADC16 = cms.bool(True),#roughly 10Million events rejected by putting this false
)

from HLTrigger.HLTfilters.hltHighLevel_cfi import *
HLTskimFilter = hltHighLevel.clone(
	HLTPaths = [
	"HLT_HIMinimumBias_part*_v1",
      
        #Single Pixel Track paths
	"HLT_HIMinimumBias_SinglePixelTrack_part*_v1",

	#thse 2 paired together give the same trigger as the one above,  but w/ less noise
	"HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part*_v1",
	"HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part*_v1",

        #CASTOR path
	"HLT_HICastorMinimumBias_part*_v1",

        #Reduced format paths
	"HLT_HIMinimumBiasRF_part*_v1",
	"HLT_HIMinimumBiasRF_SinglePixelTrack_part*_v1",
	],

	throw = False
)

HIMBFilter = cms.Sequence(L12018MBFilter * HLTskimFilter)

'''
#usage: place this somewhere in your config

process.load("HI2018MBFilter.HI2018MBFilter.HI2018MBFilter_cfi")

#put this at the end of your config (appends filter to front of each path)
for path in process.paths:
    getattr(process,path)._seq = process.HIMBFilter*getattr(process,path)._seq

'''
