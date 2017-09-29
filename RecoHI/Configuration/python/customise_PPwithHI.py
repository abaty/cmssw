import FWCore.ParameterSet.Config as cms
#customisation for pp reco of XeXe run in Oct 2017

# Add caloTowers to AOD event content
def storeCaloTowersAOD(process):

    process.load('Configuration.EventContent.EventContent_cff')
    
    # extend AOD content
    if hasattr(process,'AODoutput'):
        process.AODoutput.outputCommands.extend(['keep *_towerMaker_*_*'])

    if hasattr(process,'AODSIMoutput'):
        process.AODSIMoutput.outputCommands.extend(['keep *_towerMaker_*_*'])

    return process

# Customize process to run HI-style photon isolation in the pp RECO sequences
def addHIIsolationProducer(process):

    process.load('Configuration.EventContent.EventContent_cff')
    
    # extend RecoEgammaFEVT content
    process.RecoEgammaFEVT.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*'
                                                  ])
    
    # extend RecoEgammaRECO content
    process.RECOEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])
    
    process.FEVTEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])
    process.FEVTSIMEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])
    # extend RecoEgammaRECO content
    process.RAWRECOEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])

    process.RECOSIMEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])

    process.RAWRECOSIMHLTEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])
    
    process.RAWRECODEBUGHLTEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])

    process.FEVTHLTALLEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])

    process.FEVTDEBUGEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                  'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*',
                                                  'keep recoCaloClusters_islandBasicClusters_*_*'
                                                  ])

    # extend RecoEgammaAOD content
    process.AODEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                 'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*'
                                                  ])

    process.AODSIMEventContent.outputCommands.extend(['keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerppGED_*_*',
                                                 'keep recoHIPhotonIsolationedmValueMap_photonIsolationHIProducerpp_*_*'
                                                  ])

    # add HI Photon isolation sequence to pp RECO
    process.load('RecoHI.HiEgammaAlgos.photonIsolationHIProducer_cfi')
    process.load('RecoEcal.EgammaClusterProducers.islandBasicClusters_cfi')

    process.photonIsolationHISequencePP = cms.Sequence(process.islandBasicClusters 
                                                       * process.photonIsolationHIProducerpp 
                                                       * process.photonIsolationHIProducerppGED)
    
    process.reconstruction *= process.photonIsolationHISequencePP
    
    return process

#delete a lot of features out of PF to save on timing
def customisePF(process):
    process.load("RecoParticleFlow.Configuration.RecoParticleFlow_cff")
    process.particleFlowBlock.useNuclear = cms.bool(False)

    #kill this because it uses huge amount of timing and HI doesn't need it
    process.load("RecoParticleFlow.PFTracking.particleFlowDisplacedVertexCandidate_cfi")
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.pt_min = 999999.0
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.nChi2_max = 0.0
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.pt_min_prim = 999999.0
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.dxy = 999999.0

    #kill the entire Tau sequence as well, takes too long to run
    process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")
    process.PFTau=cms.Sequence()#replace with an empty sequence

    #kill charged hadron subtraction for in-time PU mitigation
    process.pfNoPileUpIso.enable = False
    process.pfPileUpIso.Enable = False
    process.pfNoPileUp.enable = False
    process.pfPileUp.Enable = False

    #make it very hard to reconstruct conversions in this step (was bailing out in central events anyways)
    process.load("RecoTracker.ConversionSeedGenerators.PhotonConversionTrajectorySeedProducerFromSingleLeg_cfi")
    process.photonConvTrajSeedFromSingleLeg.RegionFactoryPSet.RegionPSet.ptMin = 999999.0
    process.photonConvTrajSeedFromSingleLeg.RegionFactoryPSet.RegionPSet.originRadius = 0
    process.photonConvTrajSeedFromSingleLeg.RegionFactoryPSet.RegionPSet.originHalfLength = 0

    #get rid of low pt tracker electrons
    process.load("RecoParticleFlow.PFTracking.trackerDrivenElectronSeeds_cfi")
    process.trackerDrivenElectronSeeds.MinPt = 5.0

    return process

#change vertexing to use gap fitter w/ zsep of 1cm (more robust in central evts)
def customiseVertexing(process):
    process.load("RecoVertex.Configuration.RecoVertex_cff")
    process.unsortedOfflinePrimaryVertices.TkClusParameters = cms.PSet(
        algorithm = cms.string("gap"),
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)        ## 1 cm max separation between clusters
        )
    )
    
    process.offlinePrimaryVertices.TkClusParameters = cms.PSet(
        algorithm = cms.string("gap"),
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)        ## 1 cm max separation between clusters
        )
    )

    process.offlinePrimaryVerticesWithBS.TkClusParameters = cms.PSet(
        algorithm = cms.string("gap"),
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)        ## 1 cm max separation between clusters
        )
    )

    #pull back inclusive vertex finder, should help w/ timing on TrackVertexArbitrator
    process.load("RecoVertex.AdaptiveVertexFinder.inclusiveVertexing_cff")
    process.inclusiveVertexFinder.minHits = 10
    process.inclusiveVertexFinder.minPt = 1.0
    process.inclusiveCandidateVertexFinderCvsL.minHits = 10
    process.inclusiveCandidateVertexFinderCvsL.minPt = 1.0

    return process

#don't try tracking under 0.3 GeV (unused for analysis anyways)
#higher threshhold for mixedtriplet/tobtec/pixelless steps to save on timing
def customiseTracking(process):

    #initial step
    process.load("RecoTracker.IterativeTracking.InitialStep_cff")
    process.initialStepTrajectoryFilterBase.minPt=0.6  # ptmin of tracking region is 0.5
    
    #high pt triplet
    process.load("RecoTracker.IterativeTracking.HighPtTripletStep_cff")
    process.highPtTripletStepTrajectoryFilterBase.minPt=0.7 # ptmin of tracking region is 0.6

    #detached triplet
    process.load("RecoTracker.IterativeTracking.DetachedTripletStep_cff")
    process.detachedTripletStepTrackingRegions.RegionPSet.ptMin = 0.8  # punt on low pt displaced tracks
    process.detachedTripletStepTrajectoryFilterBase.minPt = 0.9 

    #detached quad
    process.load("RecoTracker.IterativeTracking.DetachedQuadStep_cff")
    process.detachedQuadStepTrackingRegions.RegionPSet.ptMin = 0.8  # punt on low pt displaced tracks
    process.detachedQuadStepTrajectoryFilterBase.minPt = 0.9

    #low pt quad step
    process.load("RecoTracker.IterativeTracking.LowPtQuadStep_cff")
    process.lowPtQuadStepTrackingRegions.RegionPSet.ptMin = 0.25  
    process.lowPtQuadStepTrajectoryFilterBase.minPt=0.3  

    #low pt triplet step
    process.load("RecoTracker.IterativeTracking.LowPtTripletStep_cff")
    process.lowPtTripletStepTrackingRegions.RegionPSet.ptMin = 0.25
    process.lowPtTripletStepStandardTrajectoryFilter.minPt = 0.3
   
    #mixed triplet step
    process.load("RecoTracker.IterativeTracking.MixedTripletStep_cff")
    process.mixedTripletStepTrajectoryFilter.minPt = 0.4
    process.mixedTripletStepPropagator.ptMin = 0.4
    process.mixedTripletStepPropagatorOpposite.ptMin = 0.4

    #pixelless step
    process.load("RecoTracker.IterativeTracking.PixelLessStep_cff")
    process.pixelLessStepTrackingRegions.RegionPSet.ptMin = 3.0
    process.pixelLessStepTrajectoryFilter.minPt = 4.0

    #tobtec step
    process.load("RecoTracker.IterativeTracking.TobTecStep_cff")
    process.tobTecStepTrackingRegionsPair.RegionPSet.ptMin = 3.0
    process.tobTecStepTrackingRegionsTripl.RegionPSet.ptMin = 3.0
    process.tobTecStepTrajectoryFilter.minPt = 4.0

    return process

#copied almost exactly from RecoTracker/Configuration/python/customiseClusterCheckForHighPileup.py
#also need to reenable doClusterCheck because it is turned off by default in phase 1
def customiseClusterCheck(process):
    _maxPixel = 100000

    #FIXME:
    #FIXME:
    #FIXME: add back last two cuts with parameters determined for XeXe phase 1 tracker!
    #_cut = "strip < 1000000 && pixel < 100000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/7.)"
    _cut = "strip < 1000000 && pixel < 100000" 
    #ENDFIXME

    _maxElement = 1000000

    for module in process._Process__producers.values():
        cppType = module._TypedParameterizable__type

        # cluster multiplicity check
        if cppType == "ClusterCheckerEDProducer":
            module.doClusterCheck = True #added this line (not in pp config)
            module.MaxNumberOfPixelClusters = _maxPixel
            module.cut = _cut
        if hasattr(module, "ClusterCheckPSet"):
            module.ClusterCheckPSet.MaxNumberOfPixelClusters = _maxPixel
            module.ClusterCheckPSet.doClusterCheck = True #added this line (not in pp config)
            # PhotonConversionTrajectorySeedProducerFromQuadruplets does not have "cut"...
            if hasattr(module.ClusterCheckPSet, "cut"):
                module.ClusterCheckPSet.cut = _cut


        if cppType in ["PixelTripletLargeTipEDProducer", "MultiHitFromChi2EDProducer"]:
            module.maxElement = _maxElement
        if hasattr(module, "OrderedHitsFactoryPSet") and hasattr(module.OrderedHitsFactoryPSet, "GeneratorPSet"):
            #next line is in pp config but we comment it to be safe by changing more modules...
            #if module.OrderedHitsFactoryPSet.GeneratorPSet.ComponentName.value() in ["PixelTripletLargeTipGenerator", "MultiHitGeneratorFromChi2"]:
            module.OrderedHitsFactoryPSet.GeneratorPSet.maxElement = _maxElement
    
    return process

def customisePPwithHI(process):

    process=storeCaloTowersAOD(process)
    process=addHIIsolationProducer(process)
    process=customisePF(process)
    process=customiseVertexing(process)
    process=customiseTracking(process)
    process=customiseClusterCheck(process)

    return process
