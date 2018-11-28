import FWCore.ParameterSet.Config as cms
#use import as to mask it to process.load() 
#import RecoBTag.SecondaryVertex.candidateCombinedSecondaryVertexSoftLeptonComputer_cfi as sl_cfg 
import RecoBTag.SecondaryVertex.candidateCombinedSecondaryVertexV2Computer_cfi as sl_cfg 
from RecoBTag.CSVscikit.training_settings import csvscikit_vpset
from RecoBTag.CSVscikit.helpers import get_vars

weightfilename = 'RecoBTag/PerformanceMeasurements/test/TMVA_weights.xml'

#charmTagsComputerCvsL = cms.ESProducer(
CSVscikitTags = cms.ESProducer(
   #'CharmTaggerESProducer',
   'CSVscikitESProducer',
   #clone the cfg only
   slComputerCfg = cms.PSet(
      #**sl_cfg.candidateCombinedSecondaryVertexSoftLeptonComputer.parameters_()
      **sl_cfg.candidateCombinedSecondaryVertexV2Computer.parameters_()
      ),
   weightFile = cms.FileInPath(weightfilename),

   variables = csvscikit_vpset,
   #variables = get_vars(weightfilename),

   #computer = cms.ESInputTag('combinedSecondaryVertexSoftLeptonComputer'),
   computer = cms.ESInputTag('justastupiddummyname'),
   #computer = cms.ESInputTag('combinedSecondaryVertexComputer'),
   tagInfos = cms.VInputTag(
      cms.InputTag('pfImpactParameterTagInfos'),
      #cms.InputTag('pfInclusiveSecondaryVertexFinderCvsLTagInfos'),
      cms.InputTag('pfInclusiveSecondaryVertexFinderTagInfos'),
      #cms.InputTag('softPFMuonsTagInfos'),
      #cms.InputTag('softPFElectronsTagInfos'),
      ),
   mvaName = cms.string('BDT'),
   useCondDB = cms.bool(False),
   gbrForestLabel = cms.string(''),
   useGBRForest = cms.bool(True),
   useAdaBoost = cms.bool(False)
   )

#charmTagsComputerCvsL.slComputerCfg.correctVertexMass = False
#CSVscikitTags.slComputerCfg.correctVertexMass = False

#charmTagsComputerCvsB = charmTagsComputerCvsL.clone(
#CSVscikitTagsdummy = CSVscikitTags.clone(
#   weightFile = cms.FileInPath('RecoBTag/CSVscikit/data/TMVAClassification_BDTG.weights.xml'),   
#   variables = c_vs_b_vars_vpset
#   )

