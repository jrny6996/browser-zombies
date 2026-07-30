#pragma once
#include <string>
#include <fstream>

class IAssetStorage
{
    virtual bool store_asset(std::ifstream &file_stream, std::string storage_path) = 0;
    virtual bool check_asset_exists(std::string storage_path) = 0;
    virtual ~IAssetStorage() = default;
};
