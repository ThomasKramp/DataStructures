#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "quadtree/axis_aligned_bounding_box.h"
#include "quadtree/quadtree.h"

TEST_CASE("time_complexity_output" "[output]") {
    int loops = 1024;
    float x = 0, y = 0, w = 0, h = 0;
    std::srand((unsigned)time(NULL));

    for (int i = 1; i <= loops; i++) {
        // Create a quadtree
        AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
        Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

        for (int j = 1; j <= i; j++) {
            // Generate random float between 0 and 10
            x = (float) std::rand() / RAND_MAX * 10;
            y = (float) std::rand() / RAND_MAX * 10;
            do { w = (float) std::rand() / RAND_MAX * 10 / loops; } while ((w == 0) || (x + w > 10));
            do { h = (float) std::rand() / RAND_MAX * 10 / loops; } while ((h == 0) || (y + h > 10));
            quadTree.insert(AxisAlignedBoundingBox(x, y, w, h), "figure" + std::to_string(i));
        }

        // for(auto box: quadTree){ std::cout << static_cast<std::string>(*box) << "\n"; }

        // Start Clock
        auto start = std::chrono::steady_clock::now();
        // Search boxes
        // Generate random float between 0 and 8
        x = (float) std::rand() / RAND_MAX * 8;
        y = (float) std::rand() / RAND_MAX * 8;
        auto boxes = quadTree.query_region(AxisAlignedBoundingBox(x, y, 2, 2));
        // Stop Clock
        auto end = std::chrono::steady_clock::now();
        // Display time
        std::chrono::duration<double> diff = end - start;
        // std::cout << "Time elapsed: " << std::setprecision(5) << diff.count() * 1000 << " ms\n";
        // std::cout << "Amount of boxes: " << i << " \n";
        std::cout << std::setprecision(5) << diff.count() * 1000 << "," << i << std::endl;

        // for(auto box: boxes){ std::cout << static_cast<std::string>(box) << "\n"; }
    }
}

TEST_CASE("time_complexity_file" "[file]") {
    std::fstream dataFile;
    dataFile.open("data");

    if (!dataFile.is_open()){  // Check if file opens
        std::cout << "Could not open file data" << std::endl;
    } else {
        int loops = 8192;
        float x = 0, y = 0, w = 0, h = 0;
        std::srand((unsigned)time(NULL));

        for (int i = 1; i <= loops; i++) {
            // Create a quadtree
            AxisAlignedBoundingBox bounds = AxisAlignedBoundingBox(0, 0, 10, 10);
            Quadtree<std::string> quadTree = Quadtree<std::string>(bounds, 3);

            for (int j = 1; j <= i; j++) {
                // Generate random float between 0 and 10
                x = (float) std::rand()/RAND_MAX * 10;
                y = (float) std::rand()/RAND_MAX * 10;
                do { w = (float) std::rand()/RAND_MAX * 10 / loops; } while ((w == 0) || (x + w > 10));
                do { h = (float) std::rand()/RAND_MAX * 10 / loops; } while ((h == 0) || (y + h > 10));
                quadTree.insert(AxisAlignedBoundingBox(x, y, w, h), "figure" + std::to_string(i));
            }

            // for(auto box: quadTree){ std::cout << static_cast<std::string>(*box) << "\n"; }

            // Start Clock
            auto start = std::chrono::steady_clock::now();
            // Search boxes
            // Generate random float between 0 and 8
            x = (float) std::rand()/RAND_MAX * 8;
            y = (float) std::rand()/RAND_MAX * 8;
            auto boxes = quadTree.query_region(AxisAlignedBoundingBox(x, y, 2, 2));
            // Stop Clock
            auto end = std::chrono::steady_clock::now();
            // Display time
            std::chrono::duration<double> diff = end - start;
            // std::cout << "Time elapsed: " << std::setprecision(5) << diff.count() << " s\n";
            // std::cout << "Amount of boxes: " << i << " \n";
            dataFile << std::setprecision(5) << diff.count() << ',' << i << std::endl;

            // for(auto box: boxes){ std::cout << static_cast<std::string>(box) << "\n"; }
        }
        dataFile.close();
    }
}
