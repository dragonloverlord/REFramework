namespace sdk {
class ResourceManager;
class Resource;
}

#pragma once

#include <string_view>

class REManagedObject;

namespace sdk {
class Resource {
public:
    void add_ref();
    void release();

private:
    friend class sdk::ResourceManager;

    static void update_pointers();
    static void (*s_add_ref_fn)(Resource*);
    static void (*s_release_fn)(Resource*);
};

class ResourceManager {
public:
    static ResourceManager* get();

public:
    sdk::Resource* create_resource(void* type_info, std::wstring_view name);

    static auto get_create_resource_function() {
        update_pointers();

        return s_create_resource_fn;
    }

private:
    friend class sdk::Resource;

    static void update_pointers();
    static sdk::Resource* (*s_create_resource_fn)(ResourceManager*, void*, const wchar_t*);
    static uintptr_t s_create_resource_reference;
};
}