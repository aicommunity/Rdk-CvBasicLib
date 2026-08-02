#include "UPackCvBasicDocs.h"

#include <algorithm>
#include <cctype>

namespace RDK::LLM {

namespace {

std::string toLowerAscii(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

bool looksLikeCvBasicDomain(const std::string& text)
{
    const std::string lower = toLowerAscii(text);
    return lower.find("cvbasic") != std::string::npos || lower.find("opencv") != std::string::npos
           || lower.find("cvimage") != std::string::npos || lower.find("camera") != std::string::npos
           || lower.find("видео") != std::string::npos || text.find("изображен") != std::string::npos
           || lower.find("ucv") != std::string::npos;
}

} // namespace

PackMatch UPackCvBasicDocs::match(const PackTurnSnapshot& snap) const
{
    PackMatch m;
    if(!snap.req || snap.skip_pre_llm_funnel)
        return m;
    if(!looksLikeCvBasicDomain(snap.req->user_text) && !looksLikeCvBasicDomain(snap.planning_text))
        return m;
    m.score = 0.55f;
    m.reason = "cvbasic_domain_hint";
    return m;
}

PackHintContribution UPackCvBasicDocs::hints(const PackTurnSnapshot& snap) const
{
    (void)snap;
    PackHintContribution h;
    h.ephemeral_markdown =
        "## CvBasic library\n"
        "For OpenCV / image / camera component questions, prefer `search_cvbasic_docs` and "
        "`list_cvbasic_component_classes` before inventing class names.";
    h.extra_tool_names = {"search_cvbasic_docs", "list_cvbasic_component_classes", "describe_class",
                          "search_project_docs", "search_tools"};
    h.act_or_clarify_recovery_tools = {"search_cvbasic_docs", "list_cvbasic_component_classes",
                                       "search_tools", "spawn_explore_subagent", "ask_user"};
    return h;
}

} // namespace RDK::LLM
