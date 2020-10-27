#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <fstream>

void printLogo() {


    std::cout << "\033[1;34m88888b.                                              dP\033[0m\n"
        "\033[1;34m8'   `88                                              88\n"
        "\033[1;34m88        .d8888b. .d8888b. 88d888b. 88d888b. .d8888b. 88d888b. .d8888b. 88d888b.\033[0m\n"
        "\033[1;34m88        88ooood8 88'  `88 88'  `88 88'  `88 88'  `"" 88'  `88 88ooood8 88'  `88\033[0m\n"
                                                              "\033[1;34mY8.   .88 88.  ... 88.  .88 88       88       "
                                                              "\033[1;34m88.  ... 88    88 88.  ... 88\n"
                                                              "\033[1;34mY88888P' `88888P' `88888P8 dP       dP       "
                                                              "\033[1;34m`88888P' dP    dP `88888P' dP\n";
    std::cout << std::endl;
}

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
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            http_code = "";
        }
        /**if (res == CURLE_OK) {
            long response_code;
            std::cout << res << std::endl;
            http_code = url;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            //std::cout << response_code
        }**/
        else {
            http_code = url;
        }
        curl_easy_cleanup(curl);
    }
    return http_code;
}

int main() {
    printLogo();

    std::vector<std::string> url_list;
    std::string user_url;
    std::string username;
    std::ifstream in("/PATH/TO/FILE");
    std::string line;
    while (std::getline(in, line)) {
        url_list.push_back(line);
    }
    std::cout << "Enter a username: ";
    std::cin >> username;
    for (auto i = url_list.begin(); i < url_list.end(); i++) {
        user_url = *i + username;
        std::string verifiedUrl = url_Check(user_url);
        if (!verifiedUrl.empty()) {
            std::cout << "\033[1;34mFound: \033[0m" << verifiedUrl << std::endl;
        }
    }
}
