#include <iostream>
#include <string>

void BuildStringTest(std::string link, std::string text) {
    std::string html;
    html = "<a href=\"" + link + "\">";
    if (!text.empty())
        html += text;
    else
        html += link;
    html += "</a>";
    
    std::cout << html << '\n';
}

void BuildStringTest2(std::string link, std::string text) {
    std::string html;
    const auto& inText = text.empty() ? link : text;
    html = "<a href=\"" + link + "\">" + inText + "</a>";
    
    std::cout << html << '\n';
}

void BuildStringTestIIFE(std::string link, std::string text) {
    const std::string html = [&]() {
        std::string out = "<a href=\"" + link + "\">";
        if (!text.empty())
            out += text;
        else
            out += link;
        out += "</a>"; 
        return out;
    }(); // call ()!
    
    std::cout << html << '\n';
}

void BuildStringTestIIFE2(std::string link, std::string text) {
    const std::string html = [&] {
        const auto& inText = text.empty() ? link : text;
        return "<a href=\"" + link + "\">" + inText + "</a>";
    }();
    
    std::cout << html << '\n';
}

int main() {
    BuildStringTest("https://isocpp.org", "ISO C++");
    BuildStringTest("https://isocpp.org", "");
    
    BuildStringTest2("https://isocpp.org", "ISO C++");
    BuildStringTest2("https://isocpp.org", "");
    
    BuildStringTestIIFE("https://isocpp.org", "ISO C++");
    BuildStringTestIIFE2("https://isocpp.org", "");
}