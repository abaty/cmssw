import FWCore.ParameterSet.Config as cms
#customisation by A. Baty for pp reco of XeXe run in Oct 2017

# Add caloTowers to AOD event content
def storeCaloTowersAOD(process):

    process.load('Configuration.EventContent.EventContent_cff')
    
    # extend AOD content
    if hasattr(process,'AODoutput'):
        process.AODoutput.outputCommands.extend(['keep *_towerMaker_*_*'])

    if hasattr(process,'AODSIMoutput'):
        process.AODSIMoutput.outputCommands.extend(['keep *_towerMaker_*_*'])

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

def customisePPwithHI(process):

    process=storeCaloTowersAOD(process)
    process=customisePF(process)
    process=customiseVertexing(process)
    process=customiseTracking(process)

    return process
