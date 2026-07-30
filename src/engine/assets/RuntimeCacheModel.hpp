#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include <iostream>
#include "./IAssetStorage.hpp"

#if defined(PLATFORM_WEB)
#include "./IDBAssetStorage.hpp"

#endif

class RuntimeCachedModel
{
private:
    u_int16_t model_idx;
    std::vector<std::string> model_download_urls;
    Model current_model;
    bool has_collison = true;

    bool _verify_model()
    {
        return IsModelValid(this->current_model);
    }

public:
    RuntimeCachedModel(std::vector<std::string> model_urls) : model_download_urls(model_urls)
    {
    }
    bool load(u_int16_t idx = 0, bool allow_lower_quality = false, bool ignore_cache = false)
    {
        if (idx > this->model_download_urls.size())
        {
            std::cout << "Model url at index:" << idx << " does not exist" << std::endl;
            std::cout << "Model urls: \n";
            for (const auto &url : this->model_download_urls)
            {
                std::cout << url << std::endl;
            }
            std::cout << "***" << std::endl;
            return false;
        }
        bool verified = this->_verify_model();

        if (this->model_idx == idx)
        {
            if (!verified)
            {
            }
            return true;
        }
    };
};