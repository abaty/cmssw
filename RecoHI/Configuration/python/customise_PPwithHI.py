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
    process.particleFlowTmp.usePFConversions = cms.bool(False)

    #kill this because it uses huge amount of timing and HI doesn't need it
    process.load("RecoParticleFlow.PFTracking.particleFlowDisplacedVertexCandidate_cfi")
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.pt_min = 999999.0
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.nChi2_max = 0.0
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.pt_min_prim = 999999.0
    process.particleFlowDisplacedVertexCandidate.tracksSelectorParameters.dxy = 999999.0

    #kill the entire Tau sequence as well, takes too long to run
    #process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")
    #process.PFTau=cms.Sequence()#replace with an empty sequence

    return process

#change vertexing to use gap fitter w/ zsep of 1cm (more robust in central evts)
#also, slightly tighet d0 selection
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
def customiseTracking(process):

    #initial step
    process.load("RecoTracker.IterativeTracking.InitialStep_cff")
    process.initialStepTrajectoryFilterBase.minPt=0.3
    
    #high pt triplet
    process.load("RecoTracker.IterativeTracking.HighPtTripletStep_cff")
    process.highPtTripletStepTrajectoryFilterBase.minPt=0.3

    #detached triplet
    process.load("RecoTracker.IterativeTracking.DetachedTripletStep_cff")
    process.detachedTripletStepTrajectoryFilterBase.minPt = 0.3

    #detached quad
    process.load("RecoTracker.IterativeTracking.DetachedQuadStep_cff")
    process.detachedQuadStepTrajectoryFilterBase.minPt = 0.3

    #low pt quad step
    process.load("RecoTracker.IterativeTracking.LowPtQuadStep_cff")
    process.lowPtQuadStepTrackingRegions.RegionPSet.ptMin = 0.3  
    process.lowPtQuadStepTrajectoryFilterBase.minPt=0.3  

    #low pt triplet step
    process.load("RecoTracker.IterativeTracking.LowPtTripletStep_cff")
    process.lowPtTripletStepTrackingRegions.RegionPSet.ptMin = 0.3
    process.lowPtTripletStepStandardTrajectoryFilter.minPt = 0.3
   
    #mixed triplet step
    process.load("RecoTracker.IterativeTracking.MixedTripletStep_cff")
    process.mixedTripletStepTrajectoryFilter.minPt = 0.3
    process.mixedTripletStepPropagator.ptMin = 0.3
    process.mixedTripletStepPropagatorOpposite.ptMin = 0.3

    #pixelless step
    process.load("RecoTracker.IterativeTracking.PixelLessStep_cff")
    process.pixelLessStepTrajectoryFilter.minPt = 0.3

    #tobtec step
    process.load("RecoTracker.IterativeTracking.TobTecStep_cff")
    process.tobTecStepTrajectoryFilter.minPt = 0.3


    return process

def customisePPwithHI(process):

    process=storeCaloTowersAOD(process)
    process=customisePF(process)
    process=customiseVertexing(process)
    process=customiseTracking(process)

    return process

