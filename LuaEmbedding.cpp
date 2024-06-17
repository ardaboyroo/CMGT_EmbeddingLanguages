#include "Utils.hpp"
#include "Config.hpp"

#pragma optimize("", off)

int main(int argc, char** argv)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "cprint", Utils::CoolPrint);

    // Run it once to compile the file and print any error messages to the console
    Utils::CheckSyntaxError(L, luaL_loadfile(L, "helloworld.lua"));


    // Read integer
    {
        // Load the object onto the stack
        lua_getglobal(L, "a");

        // Check if it is a number
        if (lua_isnumber(L, -1))
        {
            vector<double> elapsedTimeResult;

            // Run the test SAMPLES amount of times to get the average result
            for (int i = 0; i < SAMPLES; i++)
            {
                double num;

                // Start keeping track of time
                auto start = chrono::steady_clock::now();

                // Read the top of the stack (which is a double) ITERATIONS amount of times
                for (int j = 0; j < ITERATIONS; j++)
                {
                    num = lua_tonumber(L, -1);
                }

                // Keep track of the end time and print the result
                auto end = chrono::steady_clock::now();

                // Add result of current sample to the list
                elapsedTimeResult.push_back(Utils::GetElapsedTime(start, end));
            }

            // Print out the result
            cout << "Average read time: " << Utils::GetAverageResult(elapsedTimeResult) << " ms" << endl;
        }

        // Pop the top of the stack
        lua_pop(L, 1);
    }


    // Write integer
    {
        vector<double> elapsedTimeResult;

        for (int i = 0; i < SAMPLES; i++)
        {
            auto start = chrono::steady_clock::now();

            for (int j = 0; j < ITERATIONS; j++)
            {
                // Push number onto the stack
                lua_pushnumber(L, 69);

                // Assign the top value of the stack to the variable 'b' and pop the top of the stack
                lua_setglobal(L, "b");
            }

            auto end = chrono::steady_clock::now();

            // Add result of current sample to the list
            elapsedTimeResult.push_back(Utils::GetElapsedTime(start, end));
        }

        cout << "Average write time: " << Utils::GetAverageResult(elapsedTimeResult) << " ms" << endl;
    }

    // Function call
    {
        vector<double> elapsedTimeResult;

        for (int i = 0; i < SAMPLES; i++)
        {
            auto start = chrono::steady_clock::now();

            for (int i = 0; i < ITERATIONS; i++)
            {
                // Load the function onto the stack
                lua_getglobal(L, "luaFunc");

                // Call the top of stack with 0 arguments and 0 returns
                lua_call(L, 0, 0);
            }

            auto end = chrono::steady_clock::now();

            elapsedTimeResult.push_back(Utils::GetElapsedTime(start, end));
        }

        cout << "Average function call time: " << Utils::GetAverageResult(elapsedTimeResult) << " ms" << endl;
    }

    // Function call with parameters
    {
        vector<double> elapsedTimeResult;

        for (int i = 0; i < SAMPLES; i++)
        {
            auto start = chrono::steady_clock::now();

            for (int i = 0; i < ITERATIONS; i++)
            {
                // Load the function onto the stack
                lua_getglobal(L, "luaFunc2");

                // Push the argument to the stack
                lua_pushnumber(L, 1);

                // Call the top of the stack with 1 argument and 0 returns
                lua_call(L, 1, 0);
            }

            auto end = chrono::steady_clock::now();

            elapsedTimeResult.push_back(Utils::GetElapsedTime(start, end));
        }

        cout << "Average function call with parameters time: " << Utils::GetAverageResult(elapsedTimeResult) << " ms" << endl;
    }

    // Function call with returns
    {
        vector<double> elapsedTimeResult;

        for (int i = 0; i < SAMPLES; i++)
        {
            double num;

            auto start = chrono::steady_clock::now();

            for (int i = 0; i < ITERATIONS; i++)
            {
                // Load the function onto the stack
                lua_getglobal(L, "luaFunc3");

                // Call the top of the stack with 0 arguments and 1 return
                lua_call(L, 0, 1);

                // Cast the top of the stack to a number (assumed that it is a number)
                num = lua_tonumber(L, -1);

                // Pop the returned value from the stack
                lua_pop(L, 1);
            }

            auto end = chrono::steady_clock::now();

            elapsedTimeResult.push_back(Utils::GetElapsedTime(start, end));
        }

        cout << "Average function call with returns time: " << Utils::GetAverageResult(elapsedTimeResult) << " ms" << endl;
    }

    // Difference between get_mem_usage and visual studio debugger

    //cout << "Current memory usage: " << Utils::get_mem_usage(MEM_TYPE::IN_B) << endl;

    lua_close(L);
}
