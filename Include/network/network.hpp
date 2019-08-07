#include <string>

#define FIREFOX_USER_AGENT "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:64.0) Gecko/20100101 Firefox/64.0"

namespace network{
    std::size_t CurlStrWrite(const char* in, std::size_t size, std::size_t num, std::string* out);
    std::string RetrieveContent(std::string URL, std::string MIMEType);
}
