#include "WebCrawler.h"
#include <regex>
#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

WebCrawler::WebCrawler(const std::string& domain, bool allowSubdomains)
    : baseDomain(domain), includeSubdomains(allowSubdomains) {}

bool WebCrawler::isInternal(const std::string& url) const {
    std::string domain = getDomain(url);
    if (includeSubdomains) return domain.ends_with(baseDomain);
    return domain == baseDomain;
}

std::string WebCrawler::getDomain(const std::string& url) const {
    std::regex re(R"(https?:\/\/(www\.)?([^\/]+))");
    std::smatch match;
    if (std::regex_search(url, match, re)) return match[2];
    return "";
}

std::string WebCrawler::fetchHtml(const std::string& url) const {
    CURL* curl = curl_easy_init();
    std::string content;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "[fetchHtml] Failed to fetch " << url << ": " << curl_easy_strerror(res) << "\n";
        }
        curl_easy_cleanup(curl);
    }
    return content;
}

bool WebCrawler::isLinkBroken(const std::string& url) const {
    CURL* curl = curl_easy_init();
    long http_code = 0;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "[isLinkBroken] Failed to check " << url << ": " << curl_easy_strerror(res) << "\n";
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);
    }
    return (http_code >= 400 || http_code == 0);
}

std::string WebCrawler::normalizeUrl(const std::string& url) const {
    std::string clean = url;
    
    // Remover fragmentos #
    size_t pos = clean.find('#');
    if (pos != std::string::npos) clean = clean.substr(0, pos);

    // Eliminar doble slash final
    while (clean.ends_with("//")) clean.pop_back();

    // Eliminar slash final redundante (excepto si es solo dominio)
    if (clean.length() > 8 && clean.ends_with('/')) clean.pop_back();

    return clean;
}

std::vector<std::string> WebCrawler::extractLinks(const std::string& html) const {
    std::vector<std::string> links;
    std::regex re(R"(<a\s+[^>]*href=["']([^"'>]+)["'])");
    auto begin = std::sregex_iterator(html.begin(), html.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        links.push_back((*it)[1]);
    }
    return links;
}

TreeNode* WebCrawler::crawl(const std::string& url, int depth) {
    std::string normalized = normalizeUrl(url);
    if (visited.count(normalized) || depth < 0) return nullptr;

    visited.insert(normalized);

    bool internal = isInternal(normalized);
    bool broken = isLinkBroken(normalized);
    TreeNode* node = new TreeNode(normalized, broken, !internal);

    if (!internal || broken || depth == 0) return node;

    std::cerr << "[crawl] Visiting: " << normalized << " at depth " << depth << "\n";

    std::string html = fetchHtml(normalized);
    auto links = extractLinks(html);
    std::cerr << "[crawl] Found " << links.size() << " links in " << normalized << "\n";

    for (const std::string& link : links) {
        std::string absolute = link.starts_with("http") ? link : normalized + link;
        std::string normalizedLink = normalizeUrl(absolute);

        if (visited.count(normalizedLink)) continue;

        if (!isInternal(normalizedLink)) {
            TreeNode* child = new TreeNode(normalizedLink, true, true);
            node->addChild(child);
            visited.insert(normalizedLink);
            continue;
        }

        TreeNode* child = crawl(normalizedLink, depth - 1);
        if (child) node->addChild(child);
    }

    return node;
}
