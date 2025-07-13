#ifndef CRAWL_STATS_H
#define CRAWL_STATS_H

struct CrawlStats {
    int total = 0;
    int internal = 0;
    int broken = 0;
    int external = 0;

    void merge(const CrawlStats& other);
};

#endif
