import FWCore.ParameterSet.Config as cms

# NEW CLUSTERS (remove previously used clusters)
hiMixedTripletClusters = cms.EDProducer("HITrackClusterRemover",
                                        clusterLessSolution= cms.bool(True),
                                        oldClusterRemovalInfo = cms.InputTag("hiLowPtTripletStepClusters"),
                                        trajectories = cms.InputTag("hiLowPtTripletStepTracks"),
                                        overrideTrkQuals = cms.InputTag('hiLowPtTripletStepSelector','hiLowPtTripletStep'),
                                        TrackQuality = cms.string('highPurity'),
                                        pixelClusters = cms.InputTag("siPixelClusters"),
                                        stripClusters = cms.InputTag("siStripClusters"),
                                        Common = cms.PSet(
    maxChi2 = cms.double(9.0),
    ),
                                        Strip = cms.PSet(
    maxChi2 = cms.double(9.0),
    #Yen-Jie's mod to preserve merged clusters
    maxSize = cms.uint32(2)
    )
                                        )


# SEEDING LAYERS
from RecoLocalTracker.SiStripClusterizer.SiStripClusterChargeCut_cfi import *
hiMixedTripletSeedLayersA = cms.EDProducer("SeedingLayersEDProducer",
    #layerList = cms.vstring('FPix1_pos+FPix2_pos+TEC1_pos', 'FPix1_neg+FPix2_neg+TEC1_neg'),
                            #'FPix2_pos+TEC2_pos+TEC3_pos', 'FPix2_neg+TEC2_neg+TEC3_neg'),
    layerList = cms.vstring(
        'BPix2+FPix1_pos+FPix2_pos', 'BPix2+FPix1_neg+FPix2_neg',
        'FPix2_pos+FPix3_pos+TEC1_pos', 'FPix2_neg+FPix3_neg+TEC1_neg'
    ),
                                   BPix = cms.PSet(
    TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4MixedTriplets'),
    HitProducer = cms.string('siPixelRecHits'),
    skipClusters = cms.InputTag('hiMixedTripletClusters')
    ),
                                   FPix = cms.PSet(
    TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4MixedTriplets'),
    HitProducer = cms.string('siPixelRecHits'),
    skipClusters = cms.InputTag('hiMixedTripletClusters')
    ),
                                   TEC = cms.PSet(
    matchedRecHits = cms.InputTag("siStripMatchedRecHits","matchedRecHit"),
    useRingSlector = cms.bool(True),
    TTRHBuilder = cms.string('WithTrackAngle'),
    clusterChargeCut = cms.PSet(refToPSet_ = cms.string('SiStripClusterChargeCutNone')),
    minRing = cms.int32(1),
    maxRing = cms.int32(2),
    skipClusters = cms.InputTag('hiMixedTripletClusters')
    )
                                   )

# SEEDS
from RecoPixelVertexing.PixelTriplets.PixelTripletLargeTipGenerator_cfi import *
PixelTripletLargeTipGenerator.extraHitRZtolerance = 0.0
PixelTripletLargeTipGenerator.extraHitRPhitolerance = 0.0
import RecoTracker.TkSeedGenerator.GlobalSeedsFromTriplets_cff
hiMixedTripletSeedsA = RecoTracker.TkSeedGenerator.GlobalSeedsFromTriplets_cff.globalSeedsFromTriplets.clone()
hiMixedTripletSeedsA.OrderedHitsFactoryPSet.SeedingLayers = 'hiMixedTripletSeedLayersA'
hiMixedTripletSeedsA.OrderedHitsFactoryPSet.GeneratorPSet = cms.PSet(PixelTripletLargeTipGenerator)
hiMixedTripletSeedsA.SeedCreatorPSet.ComponentName = 'SeedFromConsecutiveHitsTripletOnlyCreator'
#hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.ptMin = 1.0
#hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.originRadius = 0.8
#hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.nSigmaZ = 4.0
#hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.originHalfLength = 5
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.ptMin = 0.4
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.originRadius = 1.5
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.originHalfLength = 15
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.originRScaling4BigEvts = cms.bool(True)
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.minOriginR = 0
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.scalingStartNPix = 20000
hiMixedTripletSeedsA.RegionFactoryPSet.RegionPSet.scalingEndNPix = 35000

hiMixedTripletSeedsA.OrderedHitsFactoryPSet.GeneratorPSet.maxElement = 5000000
hiMixedTripletSeedsA.ClusterCheckPSet.MaxNumberOfPixelClusters = 5000000
hiMixedTripletSeedsA.ClusterCheckPSet.MaxNumberOfCosmicClusters = 50000000


# SEEDING LAYERS
from RecoLocalTracker.SiStripClusterizer.SiStripClusterChargeCut_cfi import *
hiMixedTripletSeedLayersB = cms.EDProducer("SeedingLayersEDProducer",
                                   layerList = cms.vstring(
    #'BPix1+BPix2+TIB1',
    #'BPix1+BPix2+TIB2',    
    #'BPix1+BPix3+TIB1',
    #'BPix1+BPix3+TIB2',    
    'BPix3+BPix4+TIB1',
    #'BPix4+BPix4+TIB2'
    ),
                                   BPix = cms.PSet(
    TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4MixedTriplets'),
    HitProducer = cms.string('siPixelRecHits'),
    skipClusters = cms.InputTag('hiMixedTripletClusters')
    ),
                                   TIB = cms.PSet(
    matchedRecHits = cms.InputTag("siStripMatchedRecHits","matchedRecHit"),
    TTRHBuilder = cms.string('WithTrackAngle'),
    clusterChargeCut = cms.PSet(refToPSet_ = cms.string('SiStripClusterChargeCutNone')),
    skipClusters = cms.InputTag('hiMixedTripletClusters')
    )
                                   )

# SEEDS
from RecoPixelVertexing.PixelTriplets.PixelTripletLargeTipGenerator_cfi import *
PixelTripletLargeTipGenerator.extraHitRZtolerance = 0.0
PixelTripletLargeTipGenerator.extraHitRPhitolerance = 0.0
import RecoTracker.TkSeedGenerator.GlobalSeedsFromTriplets_cff
hiMixedTripletSeedsB = RecoTracker.TkSeedGenerator.GlobalSeedsFromTriplets_cff.globalSeedsFromTriplets.clone()
hiMixedTripletSeedsB.OrderedHitsFactoryPSet.SeedingLayers = 'hiMixedTripletSeedLayersB'
hiMixedTripletSeedsB.OrderedHitsFactoryPSet.GeneratorPSet = cms.PSet(PixelTripletLargeTipGenerator)
hiMixedTripletSeedsB.SeedCreatorPSet.ComponentName = 'SeedFromConsecutiveHitsTripletOnlyCreator'
#hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.ptMin = 1.0
#hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.originRadius = 0.7
#hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.nSigmaZ = 4.0
#hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.originHalfLength = 5
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.ptMin = 0.4
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.originRadius = 1.0
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.originHalfLength = 15
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.originRScaling4BigEvts = cms.bool(True)
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.minOriginR = 0
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.scalingStartNPix = 20000
hiMixedTripletSeedsB.RegionFactoryPSet.RegionPSet.scalingEndNPix = 35000

hiMixedTripletSeedsB.OrderedHitsFactoryPSet.GeneratorPSet.maxElement = 5000000
hiMixedTripletSeedsB.ClusterCheckPSet.MaxNumberOfPixelClusters = 5000000
hiMixedTripletSeedsB.ClusterCheckPSet.MaxNumberOfCosmicClusters = 50000000

import RecoTracker.TkSeedGenerator.GlobalCombinedSeeds_cfi
hiMixedTripletSeeds = RecoTracker.TkSeedGenerator.GlobalCombinedSeeds_cfi.globalCombinedSeeds.clone()
hiMixedTripletSeeds.seedCollections = cms.VInputTag(
    cms.InputTag('hiMixedTripletSeedsA'),
    cms.InputTag('hiMixedTripletSeedsB'),
    )

# QUALITY CUTS DURING TRACK BUILDING
import TrackingTools.TrajectoryFiltering.TrajectoryFilter_cff
hiMixedTripletTrajectoryFilter = TrackingTools.TrajectoryFiltering.TrajectoryFilter_cff.CkfBaseTrajectoryFilter_block.clone(
    #maxLostHits = 0,
    minimumNumberOfHits = 4,
    minPt = 0.3
    )

# Propagator taking into account momentum uncertainty in multiple scattering calculation.
import TrackingTools.MaterialEffects.MaterialPropagator_cfi
hiMixedTripletPropagator = TrackingTools.MaterialEffects.MaterialPropagator_cfi.MaterialPropagator.clone(
    ComponentName = 'hiMixedTripletPropagator',
    ptMin = 0.3
    )
import TrackingTools.MaterialEffects.OppositeMaterialPropagator_cfi
hiMixedTripletPropagatorOpposite = TrackingTools.MaterialEffects.OppositeMaterialPropagator_cfi.OppositeMaterialPropagator.clone(
    ComponentName = 'hiMixedTripletPropagatorOpposite',
    ptMin = 0.3
    )

import TrackingTools.KalmanUpdators.Chi2MeasurementEstimator_cfi
hiMixedTripletChi2Est = TrackingTools.KalmanUpdators.Chi2MeasurementEstimator_cfi.Chi2MeasurementEstimator.clone(
    ComponentName = cms.string('hiMixedTripletChi2Est'),
    nSigma = cms.double(3.0),
    MaxChi2 = cms.double(16.0)
    )

# TRACK BUILDING
import RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cfi
hiMixedTripletTrajectoryBuilder = RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cfi.GroupedCkfTrajectoryBuilder.clone(
    MeasurementTrackerName = '',
    trajectoryFilter = cms.PSet(refToPSet_ = cms.string('hiMixedTripletTrajectoryFilter')),
    propagatorAlong = cms.string('hiMixedTripletPropagator'),
    propagatorOpposite = cms.string('hiMixedTripletPropagatorOpposite'),
    maxCand = 2,
    estimator = cms.string('hiMixedTripletChi2Est'),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7) 
    )

# MAKING OF TRACK CANDIDATES
import RecoTracker.CkfPattern.CkfTrackCandidates_cfi
hiMixedTripletTrackCandidates = RecoTracker.CkfPattern.CkfTrackCandidates_cfi.ckfTrackCandidates.clone(
    src = cms.InputTag('hiMixedTripletSeeds'),
    clustersToSkip = cms.InputTag('hiMixedTripletClusters'),
    TrajectoryBuilderPSet = cms.PSet(refToPSet_ = cms.string('hiMixedTripletTrajectoryBuilder')),
    numHitsForSeedCleaner = cms.int32(50),
    doSeedingRegionRebuilding = True,
    useHitsSplitting = True
    )

# TRACK FITTING
import RecoTracker.TrackProducer.TrackProducer_cfi
hiMixedTripletStepTracks = RecoTracker.TrackProducer.TrackProducer_cfi.TrackProducer.clone(
    AlgorithmName = cms.string('mixedTripletStep'),
    src = 'hiMixedTripletTrackCandidates',
    Fitter = cms.string('FlexibleKFFittingSmoother')
    )

# Final selection
import RecoHI.HiTracking.hiMultiTrackSelector_cfi
hiMixedTripletStepSelector = RecoHI.HiTracking.hiMultiTrackSelector_cfi.hiMultiTrackSelector.clone(
    src='hiMixedTripletStepTracks',
    trackSelectors= cms.VPSet(
    RecoHI.HiTracking.hiMultiTrackSelector_cfi.hiLooseMTS.clone(
    name = 'hiMixedTripletStepLoose',
    ), #end of pset
    RecoHI.HiTracking.hiMultiTrackSelector_cfi.hiTightMTS.clone(
    name = 'hiMixedTripletStepTight',
    preFilterName = 'hiMixedTripletStepLoose',
    ),
    RecoHI.HiTracking.hiMultiTrackSelector_cfi.hiHighpurityMTS.clone(
    name = 'hiMixedTripletStep',
    preFilterName = 'hiMixedTripletStepTight',
    min_nhits = 8
    ),
    ) #end of vpset
    ) #end of clone



# Final sequence

hiMixedTripletStep = cms.Sequence(
                          hiMixedTripletClusters*
                          hiMixedTripletSeedLayersA*
                          hiMixedTripletSeedsA*
                          hiMixedTripletSeedLayersB*
                          hiMixedTripletSeedsB*
                          hiMixedTripletSeeds*
                          hiMixedTripletTrackCandidates*
                          hiMixedTripletStepTracks*
                          hiMixedTripletStepSelector)

