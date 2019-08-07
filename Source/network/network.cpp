#include <network/network.hpp>
#include <curl/curl.h>
#include <switch.h> //socketInitializeDefault
#include <string> //std::string

namespace network{

  std::size_t CurlStrWrite(const char* in, std::size_t size, std::size_t num, std::string* out){
      const size_t totalBytes(size * num);
      out->append(in, totalBytes);
      return totalBytes;
  }

  std::string RetrieveContent(std::string URL, std::string MIMEType){
      socketInitializeDefault();
      std::string cnt;
      CURL *curl = curl_easy_init();
      if(!MIMEType.empty()){
          curl_slist *headerdata = NULL;
          headerdata = curl_slist_append(headerdata, ("Content-Type: " + MIMEType).c_str());
          headerdata = curl_slist_append(headerdata, ("Accept: " + MIMEType).c_str());
          curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerdata);
      }
      curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
      curl_easy_setopt(curl, CURLOPT_USERAGENT, FIREFOX_USER_AGENT);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlStrWrite);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cnt);
      curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      socketExit();
      return cnt;
  }
}
