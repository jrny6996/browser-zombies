#pragma once
#include "IAssetStorage.hpp"
#include <emscripten/emscripten.h>

class IDBAssetStorage : public IAssetStorage
{
private:
    std::string base_path;

public:
    IDBAssetStorage(std::string base_path = "/data") : base_path(base_path)
    {
        FS.mkdir(base_path.c_str());
        FS.mount(FS.fileSfilesystems.IDBFS, {}, base_path);
    }
    virtual bool store_asset(std::ifstream file_stream, std::string storage_path)
    {
        return true;
    }
};