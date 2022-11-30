#include <curl/curl.h>
#include <string>

class Server
{
    public:
        CURL *curl = curl_easy_init();

        Server(std::string host)
        {
            if(curl) 
            {
                CURLcode res;
                curl_easy_setopt(curl, CURLOPT_URL, host);
                res = curl_easy_perform(curl);
            }
        }

        void sendMsg(std::string data)
        {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1000);
        }
        
        std::string getMsg();

        void quit()
        {
            curl_easy_cleanup(curl);
        }
};