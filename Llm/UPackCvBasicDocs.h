#ifndef RDK_LLM_PACK_CVBASIC_DOCS_H
#define RDK_LLM_PACK_CVBASIC_DOCS_H

#include "../../../Rdk/LLM/Core/Packs/ILLMCapabilityPack.h"

namespace RDK::LLM {

/// Library pack adapter: Rdk-CvBasicLib docs / class discovery hints.
class UPackCvBasicDocs : public ILLMCapabilityPack {
public:
    const char* id() const override { return "cvbasic_docs"; }
    PackMatch match(const PackTurnSnapshot& snap) const override;
    PackHintContribution hints(const PackTurnSnapshot& snap) const override;
};

} // namespace RDK::LLM

#endif
