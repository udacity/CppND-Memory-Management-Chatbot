#include <string>
#include <memory>

#include <wx/stdpaths.h>
#include <wx/filename.h>


namespace
{
    static std::string executableDir{};
    static std::string dataDir{};
    static std::string imagesBaseDir{};

    std::string GetParentDirIfExists(const std::string& dir, const std::string& fallBackDir)
    {
        auto lastSeparator = dir.find_last_of(wxFileName::GetPathSeparator());

        if (lastSeparator != std::string::npos)
        {
            return dir.substr(0, lastSeparator);
        }

        return fallBackDir;
    }

    std::string GetExecutableDir()
    {
        if (executableDir.empty())
        {
            auto executablePath = wxStandardPaths::Get().GetExecutablePath();
            auto pathStr = executablePath.ToStdString();

            executableDir = GetParentDirIfExists(pathStr, wxGetCwd().ToStdString());
        }

        return executableDir;
    }
};

std::string GetDataPath()
{
    if (dataDir.empty())
    {
        dataDir = GetParentDirIfExists(GetExecutableDir(), GetExecutableDir()) + wxFileName::GetPathSeparator();
    }

    return dataDir;
}

std::string GetImagesBasePath()
{
    if (imagesBaseDir.empty())
    {
        imagesBaseDir = GetDataPath() + "images/";
    }

    return imagesBaseDir;
}
