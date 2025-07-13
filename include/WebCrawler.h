#ifndef WEB_CRAWLER_H
#define WEB_CRAWLER_H

#include <set>
#include <string>
#include "CrawlStats.h"
#include "TreeNode.h"

class WebCrawler {
private:
    bool includeSubdomains;
    std::string baseDomain;
    std::set<std::string> visited;

    bool isInternal(const std::string& url) const;
    bool isLinkBroken(const std::string& url) const;
    std::string getDomain(const std::string& url) const;
    std::string fetchHtml(const std::string& url) const;
    std::string normalizeUrl(const std::string& url) const;
    std::vector<std::string> extractLinks(const std::string& html) const;

public:
    WebCrawler(const std::string& domain, bool allowSubdomains);
    TreeNode* crawl(const std::string& url, int depth);
};

#endif
