#pragma once
#include "fastmcpp/export.hpp"

#include "fastmcpp/providers/provider.hpp"

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace fastmcpp::providers
{

enum class SkillSupportingFiles
{
    Template,
    Resources,
};

class FASTMCPP_API SkillProvider : public Provider
{
  public:
    explicit SkillProvider(std::filesystem::path skill_path,
                           std::string main_file_name = "SKILL.md",
                           SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);

    std::vector<resources::Resource> list_resources() const override;
    std::optional<resources::Resource> get_resource(const std::string& uri) const override;

    std::vector<resources::ResourceTemplate> list_resource_templates() const override;
    std::optional<resources::ResourceTemplate>
    get_resource_template(const std::string& uri) const override;

    const std::filesystem::path& skill_path() const
    {
        return skill_path_;
    }
    const std::string& skill_name() const
    {
        return skill_name_;
    }

  private:
    std::string build_description() const;
    std::string build_manifest_json() const;
    std::vector<std::filesystem::path> list_files() const;

    std::filesystem::path skill_path_;
    std::string skill_name_;
    std::string main_file_name_;
    SkillSupportingFiles supporting_files_;
};

class FASTMCPP_API SkillsDirectoryProvider : public Provider
{
  public:
    explicit SkillsDirectoryProvider(
        std::filesystem::path root, bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);

    explicit SkillsDirectoryProvider(
        std::vector<std::filesystem::path> roots, bool reload = false,
        std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);

    std::vector<resources::Resource> list_resources() const override;
    std::optional<resources::Resource> get_resource(const std::string& uri) const override;

    std::vector<resources::ResourceTemplate> list_resource_templates() const override;
    std::optional<resources::ResourceTemplate>
    get_resource_template(const std::string& uri) const override;

  private:
    void ensure_discovered() const;
    void discover_skills() const;

    std::vector<std::filesystem::path> roots_;
    bool reload_{false};
    std::string main_file_name_;
    SkillSupportingFiles supporting_files_{SkillSupportingFiles::Template};
    mutable bool discovered_{false};
    mutable std::vector<std::shared_ptr<SkillProvider>> providers_;
};

class FASTMCPP_API ClaudeSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit ClaudeSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API CursorSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit CursorSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API VSCodeSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit VSCodeSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API CodexSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit CodexSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API GeminiSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit GeminiSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API GooseSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit GooseSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API CopilotSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit CopilotSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

class FASTMCPP_API OpenCodeSkillsProvider : public SkillsDirectoryProvider
{
  public:
    explicit OpenCodeSkillsProvider(
        bool reload = false, std::string main_file_name = "SKILL.md",
        SkillSupportingFiles supporting_files = SkillSupportingFiles::Template);
};

using SkillsProvider = SkillsDirectoryProvider;

} // namespace fastmcpp::providers
