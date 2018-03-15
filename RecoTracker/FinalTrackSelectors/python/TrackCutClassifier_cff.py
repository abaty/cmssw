from RecoTracker.FinalTrackSelectors.TrackCutClassifier_cfi import *
from Configuration.Eras.Modifier_trackingLowPU_cff import trackingLowPU
trackingLowPU.toModify(TrackCutClassifier,
    vertices = "pixelVertices"
)
from Configuration.Eras.Modifier_pp_on_AA_2018_cff import pp_on_AA_2018
pp_on_AA_2018.toModify(TrackCutClassifier,
    mva = dict(
        maxChi2 = [30,10,3],  # default [9999.,9999.,9999.]; actually cuts on normalized chi2
        maxRelPtErr = [0.2,0.1,0.05],  # default [9999.,9999.,9999.]
    ),
)

