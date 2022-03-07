#pragma once
#include <any>
#include <unordered_map>

struct Event
{
    Event() { }
    Event(void (*a_callback)(std::any)) : callback(a_callback) { } 

    void operator()(std::any& args)
    {
        callback(args);
    }

    void (*callback)(std::any);
};

class InputManager
{

public:
    bool addKey(const int& key, Event callback)
    {
        if (key_map.contains(key))
            return false;

        key_map.insert(std::pair<int, Event>(key, callback));

        return true;
    }

    bool rmKey(const int& key)
    {
        return key_map.erase(key);
    }

    bool querryKey(int& key, std::any args)
    {
        if (!key_map.contains(key))
            return false;

        Event callback = key_map[key];
        callback(args);

        return true;

    }

private:
    std::unordered_map<int, Event> key_map;
};