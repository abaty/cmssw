#ifndef RecoBTag_CSVscikit_CSVscikitTagger_h
#define RecoBTag_CSVscikit_CSVscikitTagger_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/Utils/interface/TMVAEvaluator.h"
#include "RecoBTau/JetTagComputer/interface/JetTagComputer.h"
#include <mutex>
#include "FWCore/Utilities/interface/ESInputTag.h"
#include "RecoBTag/SecondaryVertex/interface/CombinedSVSoftLeptonComputer.h"
#include "DataFormats/BTauReco/interface/TaggingVariable.h"
#include "RecoBTau/JetTagComputer/interface/JetTagComputerRecord.h"

#include <memory>

/** \class CSVscikitTagger
 *  \author J. Vizan, U. Oviedo (Spain).
 *  copied from CharmTagger.h (by M. Verzetti)
 */

class CSVscikitTagger : public JetTagComputer {
public:
  /// explicit ctor 
	CSVscikitTagger(const edm::ParameterSet & );
	~CSVscikitTagger();//{}
  virtual float discriminator(const TagInfoHelper & tagInfo) const override;
	virtual void initialize(const JetTagComputerRecord & record) override;
	
	typedef std::vector<edm::ParameterSet> vpset;
	
	struct MVAVar {
		std::string name;
		reco::btau::TaggingVariableName id;
		size_t index;
		bool has_index;
		float default_value;
	};

private:
	std::unique_ptr<TMVAEvaluator> mvaID_;
	CombinedSVSoftLeptonComputer sl_computer_;
	CombinedSVComputer sv_computer_;
	std::vector<MVAVar> variables_;

	std::string mva_name_;
  bool use_condDB_;
	std::string gbrForest_label_;
	edm::FileInPath weight_file_;
  bool use_GBRForest_;
  bool use_adaBoost_;
};

#endif
