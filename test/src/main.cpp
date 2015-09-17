/**
 * @brief Main function for testing genesis using Gtest.
 *
 * @file
 * @ingroup test
 */

#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "common.hpp"

GenesisTestEnvironment* environment;

/**
 * @brief Return true iff the directory exists.
 *
 * This is copied from the genesis library `./lib/utils/utils.hpp`
 * because we do not want to rely on something that we are about to test...
 */
bool dir_exists (const std::string& dir)
{
    struct stat info;
    if (stat (dir.c_str(), &info) != 0) {
        return false;
    }
    return info.st_mode & S_IFDIR;
}

/**
 * @brief Initializes and starts the test run.
 *
 * The main sets the environment for testing and then runs the tests.
 *
 * @return      Zero if all tests were successfull, non-zero otherwise.
 */
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    environment = new GenesisTestEnvironment();

    // Set data dir using the program path.
    std::string call = argv[0];
    std::size_t found = call.find_last_of("/\\");
    if (found != std::string::npos) {
        environment->data_dir = call.substr(0,found) + "/../data/";
    }

    // If user provided one via command line, overwrite data dir.
    std::string data_dir_prefix = "--test_data_dir=";
    for (int i = 1; i < argc; ++i) {
        std::string argument = argv[i];
        if(argument.substr(0, data_dir_prefix.size()) == data_dir_prefix) {
            environment->data_dir = argument.substr(data_dir_prefix.size());
        }
    }

    // Actually, use the data dir only if it exists.
    if (!dir_exists(environment->data_dir)) {
        environment->data_dir = "";
    }

    // We want to see Logging information while testing.
    genesis::Logging::log_to_stdout();
    genesis::Logging::max_level(genesis::Logging::kDebug4);

    ::testing::AddGlobalTestEnvironment(environment);
    return RUN_ALL_TESTS();
}