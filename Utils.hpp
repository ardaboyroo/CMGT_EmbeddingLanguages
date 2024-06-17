#pragma once

#include "Includes.hpp"

using namespace std;

enum MEM_TYPE
{
    IN_B,     // Bytes
    IN_KB,    // KiloBytes
    IN_MB,    // MegaBytes
    IN_GB     // GigaBytes
};

class Utils
{
public:

    static double GetElapsedTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end)
    {
        chrono::duration<double> elapsedSeconds = end - start;
        double elapsedMilliseconds = elapsedSeconds.count() * 1000.0;
        return elapsedMilliseconds;
    }

    static long long get_mem_usage(MEM_TYPE t = MEM_TYPE::IN_B)
    {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

        switch (t)
        {
        case MEM_TYPE::IN_B:
            return pmc.PrivateUsage;

        case MEM_TYPE::IN_KB:
            return pmc.PrivateUsage / 1024;

        case MEM_TYPE::IN_MB:
            return pmc.PrivateUsage / 1024 / 1024;

        case MEM_TYPE::IN_GB:
            return pmc.PrivateUsage / 1024 / 1024 / 1024;
        }
    }

    static int CoolPrint(lua_State* l)
    {
        string output = lua_tostring(l, 1);
        cout << "Lua: " << output << "\n";
        return 0;
    }

    static void CheckSyntaxError(lua_State* L, int e)
    {
        if (e == LUA_OK)
        {
            lua_call(L, 0, 0);
        }
        else
        {
            cout << lua_tostring(L, -1) << endl;
        }
    }

    static void PrintStackSize(lua_State* L)
    {
        cout << "Stack size: " << lua_gettop(L) << endl;
    }

    static double GetAverageResult(vector<double>& data)
    {
        double total = 0;
        for (int i = 0; i < data.size(); i++)
        {
            total += data[i];
        }

        return total / (double)data.size();
    }
};