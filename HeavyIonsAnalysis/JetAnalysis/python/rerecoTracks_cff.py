import FWCore.ParameterSet.Config as cms

highPurityTracks = cms.EDFilter(
    "TrackSelector",
    src = cms.InputTag("generalTracks"),
    cut = cms.string('quality("highPurity")'))

from RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi import *
offlinePrimaryVertices.TrackLabel = 'highPurityTracks'
