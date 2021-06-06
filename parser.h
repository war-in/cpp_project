#include <string>
#include <string.h>
#include <memory>
#include <curl/curl.h>
#include <vector>


class Parser
{
private:
    std::string html;
    std::vector <std::string> subjects;
    std::vector <std::string> subjectsInfo;
    std::vector <std::string> pathSubjects;
    std::vector <std::string> pathSubjectsInfo;
    std::vector <std::string> faculties;
    std::vector <std::string> facultiesInfo;

public:
    explicit Parser(const char* page2download);

    std::string downloadPage(const char* page2Download);

    std::vector <std::string> getSubjects() { return subjects; };
    std::vector <std::string> getPathSubjects() { return pathSubjects; };
    std::vector <std::string> getFaculties() { return faculties; };

    std::vector <std::string> getSubjectsInfo() { return subjectsInfo; };
    std::vector <std::string> getPathSubjectsInfo() { return pathSubjectsInfo; };
    std::vector <std::string> getFacultiesInfo() { return facultiesInfo; };

    void parse(std::string semester);

};
