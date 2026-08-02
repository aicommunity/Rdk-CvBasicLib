#include "RegisterCvBasicLibLlmTools.h"

#include <filesystem>
#include <memory>

#include "../../../Rdk/LLM/Core/Context/ILLMProjectContextProvider.h"
#include "../../../Rdk/LLM/Core/Context/UDocSearchIndex.h"
#include "../../../Rdk/LLM/Core/Domain/URdkDomainAccess.h"
#include "../../../Rdk/LLM/Core/LlmPublicApi.h"
#include "../../../Rdk/LLM/Core/Tools/ULLMToolRegistry.h"
#include "UPackCvBasicDocs.h"

namespace fs = std::filesystem;

namespace {

RDK::LLM::LLMToolDefinition makeReadDef(const std::string& name, const std::string& desc,
                                        nlohmann::json input)
{
    RDK::LLM::LLMToolDefinition d;
    d.name = name;
    d.kind = RDK::LLM::LLMToolKind::Read;
    d.description = desc;
    d.input_schema = std::move(input);
    d.output_schema = {{"type", "object"}};
    return d;
}

fs::path cvbasicDocsRoot(RDK::LLM::ILLMProjectContextProvider* ctx)
{
    if(!ctx)
        return {};
    return ctx->paths().repository_root / "Libraries" / "Rdk-CvBasicLib" / "Docs";
}

} // namespace

void RegisterCvBasicLibLlmTools(RDK::LLM::ULLMToolRegistry& registry,
                                RDK::LLM::ILLMProjectContextProvider* project_context,
                                RDK::LLM::URdkDomainAccess& domain)
{
    registry.registerTool(
        makeReadDef("search_cvbasic_docs",
                    "Search Rdk-CvBasicLib documentation (OpenCV / image / camera components)",
                    {{"type", "object"},
                     {"required", {"query"}},
                     {"properties",
                      {{"query", {{"type", "string"}}}, {"top_k", {{"type", "integer"}}}}},
                     {"additionalProperties", false}}),
        [project_context](const nlohmann::json& args) -> RDK::LLM::ToolGatewayResult {
            RDK::LLM::ToolGatewayResult r;
            const std::string query = args.at("query").get<std::string>();
            const int top_k = args.value("top_k", 5);
            const fs::path root = cvbasicDocsRoot(project_context);
            std::vector<fs::path> roots;
            if(!root.empty())
                roots.push_back(root);
            auto snippets = RDK::LLM::searchDocsWithIndex(roots, query, top_k);
            r.result["snippets"] = nlohmann::json::array();
            r.result["library"] = "Rdk-CvBasicLib";
            for(const auto& s : snippets)
            {
                r.result["snippets"].push_back(
                    {{"path", s.path}, {"title", s.title}, {"excerpt", s.excerpt}, {"score", s.score}});
            }
            r.ok = true;
            return r;
        });

    registry.registerTool(
        makeReadDef("list_cvbasic_component_classes",
                    "Lists CvBasicLib component class names from the live registry",
                    {{"type", "object"}, {"additionalProperties", false}}),
        [&domain](const nlohmann::json& args) -> RDK::LLM::ToolGatewayResult {
            (void)args;
            RDK::LLM::ToolGatewayResult r;
            nlohmann::json out;
            // Storage library name is CvBasicLib (see ULibrary ctor).
            if(domain.listRegisteredClasses(out, "CvBasicLib").ok())
                r.result = std::move(out);
            else
                r.result["classes"] = nlohmann::json::array();
            // Also try CRLibrary historical name if present.
            nlohmann::json cr;
            if(domain.listRegisteredClasses(cr, "CRLibrary").ok())
            {
                for(const auto& item : cr.value("classes", nlohmann::json::array()))
                    r.result["classes"].push_back(item);
            }
            r.result["docs_hint"] = "Libraries/Rdk-CvBasicLib/Docs/README.md";
            r.result["mutation_hint"] = "Use add_component with class_name from this list.";
            r.ok = true;
            return r;
        });

    if(RDK::LLM::LLMServices::instance().isInitialized())
    {
        RDK::LLM::LLMServices::instance().packs().registerPack(
            std::make_unique<RDK::LLM::UPackCvBasicDocs>());
    }
}
