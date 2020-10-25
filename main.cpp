#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <fstream>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}

std::string url_Check(const std::string& url) {
    std::basic_string<char> http_code;
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long response_code;
            http_code = url;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            //std::cout << response_code;
        }
        else {
            http_code = "";
        }
        curl_easy_cleanup(curl);
    }
    return http_code;
}

int main() {
    std::vector<std::string> url_list;
    std::string user_url;
    std::string username;
    //Replace with a path to the url textfile
    std::ifstream in("links.txt");
    std::string line;
    while (std::getline(in, line)) {
        url_list.push_back(line);
    }
    std::cout << "Username: ";
    std::cin >> username;
    for (auto i = url_list.begin(); i < url_list.end(); i++) {
        user_url = *i + username;
        std::string verifiedUrl = url_Check(user_url);
        if (!verifiedUrl.empty()) {
            std::cout << verifiedUrl << std::endl;
        }
    }
}

