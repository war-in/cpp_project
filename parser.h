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
    std::vector <std::string> pathSubjects;
    std::vector <std::string> electiveSubjects;

public:
    explicit Parser(const char* page2download);

    std::string downloadPage(const char* page2Download);

    std::vector <std::string> getSubjects() { return subjects; };
    std::vector<std::string> getPathSubjects() { return pathSubjects; };
    std::vector<std::string> getElectiveSubjects() { return electiveSubjects; };

    void parse(std::string semester);

};
