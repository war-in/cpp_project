#include <iostream>
#include "parser.h"
#include <cctype>

using namespace std;

std::string strip(const std::string& inpt)
{
    auto start_it = inpt.begin();
    auto end_it = inpt.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

int bufferMoreData(char* data, size_t size, size_t nmemb, std::string* buffer) {
    int result = 0;
    if (buffer != nullptr)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

std::string Parser::downloadPage(const char* page2Download)
{
    std::string buffer;
    buffer.reserve(1000);

    CURL* curl;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, page2Download);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bufferMoreData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    return buffer;
}

void Parser::parse(std::string semester) {
    
    int i = 0;
    for (i = 0; i < html.length() - semester.length(); i++) {
        if (html.substr(i, semester.length()).compare(semester) == 0) {

            string pattern = "style=\"max-width: 180px; padding-left: 50px;\">";
            for (int j = i+1; j < html.length() - pattern.length(); j++) {
                if (html.substr(j, 7).compare("Semestr") == 0)
                    break;

                if (html.substr(j, pattern.length()).compare(pattern) == 0) {
                    pathSubjects.push_back(strip(html.substr(j + pattern.length() + 195, 60)));

                    string hours = "";
                    string lecture = "Wyk";
                    string lab = "boratoryjne: ";
                    string ex = "dytoryjne: ";

                    for (int m = j; m < j + 700; m++) {

                        if (html.substr(m, lecture.length()).compare(lecture) == 0) {
                            hours.append(";");
                            hours += html.substr(m+9, 2);
                        }

                        if (html.substr(m, lab.length()).compare(lab) == 0) {
                            hours.append(";");

                            if (hours.length() == 4)
                                hours.append("0;");

                            hours += html.substr(m + lab.length(), 2);
                        }

                        if (html.substr(m, ex.length()).compare(ex) == 0) {
                            hours.append(";");
                            hours += html.substr(m + ex.length(), 2);
                        }
                    }

                    if (hours.length() == 0)
                        hours.append(";0;0;0");

                    else if (hours.length() == 3)
                        hours.append(";0;0");

                    else if(hours.length() == 6)
                        hours.append(";0");

                    pathSubjectsInfo.push_back(hours);
                }
            }
            break;
        }
    }

    string tmp = "Zasady wyboru: Student wybiera";

    for (i = 0; i < html.length() - tmp.length(); i++) {

        if (html.substr(i, semester.length()).compare(semester) == 0) {

            for (int k = i+1; k < html.length() - tmp.length(); k++) {

                if (html.substr(k, 7).compare("Semestr") == 0)
                    break;

                if (html.substr(k, tmp.length()).compare(tmp) == 0) {

                    string pattern = "style=\"max-width: 180px; padding-left: 30px;\">";

                    for (int j = k; j < html.length() - pattern.length(); j++) {

                        if (html.substr(j, 7).compare("Semestr") == 0)
                            break;

                        if (html.substr(j, pattern.length()).compare(pattern) == 0) {
                            string subject = strip(html.substr(j + pattern.length() + 195, 50));
                            if (subject.length() > 45 || subject.compare("<span class=\"pull-right\"><i class=\"") == 0)
                                continue;
                            faculties.push_back(subject);

                            string hours = "";
                            string lecture = "Wyk";
                            string lab = "boratoryjne: ";
                            string ex = "dytoryjne: ";

                            for (int m = j; m < j + 700; m++) {

                                if (html.substr(m, lecture.length()).compare(lecture) == 0) {
                                    hours.append(";");
                                    hours += html.substr(m + 9, 2);
                                }

                                if (html.substr(m, lab.length()).compare(lab) == 0) {
                                    hours.append(";");

                                    if (hours.length() == 4)
                                        hours.append("0;");

                                    hours += html.substr(m + lab.length(), 2);
                                }

                                if (html.substr(m, ex.length()).compare(ex) == 0) {
                                    hours.append(";");
                                    hours += html.substr(m + ex.length(), 2);
                                }
                            }

                            if (hours.length() == 0)
                                hours.append(";0;0;0");

                            else if (hours.length() == 3)
                                hours.append(";0;0");

                            else if (hours.length() == 6)
                                hours.append(";0");

                            facultiesInfo.push_back(hours);
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

    tmp = "<td scope=\"row\" style=\"max-width: 180px; padding-left: 10px;\">";

    for (i = 0; i < html.length() - tmp.length(); i++) {

        if (html.substr(i, semester.length()).compare(semester) == 0) {

            for (int k = i; k < html.length() - tmp.length(); k++) {
                if (html.substr(k, tmp.length()).compare(tmp) == 0) {

                    string pattern = "<div class=\"syl-get-document syl-pointer\"";

                    for (int j = k; j < html.length() - pattern.length(); j++) {

                        if (html.substr(j, 7).compare("Semestr") == 0)
                            break;

                        if (html.substr(j, tmp.length()).compare(tmp) == 0 && html.substr(j + tmp.length() + 37, pattern.length()).compare(pattern) == 0) {
                            subjects.push_back(strip(html.substr(j + pattern.length() + 195, 70)));

                            string hours = "";
                            string lecture = "Wyk";
                            string lab = "boratoryjne: ";
                            string ex = "dytoryjne: ";

                            for (int m = j; m < j + 700; m++) {

                                if (html.substr(m, lecture.length()).compare(lecture) == 0) {
                                    hours.append(";");
                                    hours += html.substr(m + 9, 2);
                                }

                                if (html.substr(m, lab.length()).compare(lab) == 0) {
                                    hours.append(";");

                                    if (hours.length() == 4)
                                        hours.append("0;");

                                    hours += html.substr(m + lab.length(), 2);
                                }

                                if (html.substr(m, ex.length()).compare(ex) == 0) {
                                    hours.append(";");
                                    hours += html.substr(m + ex.length(), 2);
                                }
                            }

                            if (hours.length() == 0)
                                hours.append(";0;0;0");

                            else if (hours.length() == 3)
                                hours.append(";0;0");

                            else if (hours.length() == 6)
                                hours.append(";0");

                            subjectsInfo.push_back(hours);
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
}

Parser::Parser(const char* page2download) {
    html = downloadPage(page2download);
}