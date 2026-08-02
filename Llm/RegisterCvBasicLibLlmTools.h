#ifndef RDK_REGISTER_CVBASIC_LIB_LLM_TOOLS_H
#define RDK_REGISTER_CVBASIC_LIB_LLM_TOOLS_H

namespace RDK::LLM {
class ULLMToolRegistry;
class ILLMProjectContextProvider;
class URdkDomainAccess;
}

void RegisterCvBasicLibLlmTools(RDK::LLM::ULLMToolRegistry& registry,
                                RDK::LLM::ILLMProjectContextProvider* project_context,
                                RDK::LLM::URdkDomainAccess& domain);

#endif
