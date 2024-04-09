#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>
#include <ctime>

void num_core()
{
    std::cout << "Количество ядер 6\n" << std::endl;
}

std::vector<int> sum_vec(std::vector<int> vec1, std::vector<int> vec2) {
    std::vector<int> vec3(vec1.size());
    for (int i = 0; i < vec1.size(); i++) {
        vec3[i] = vec1[i] + vec2[i];
    }
    return vec3;
}

void times(std::vector<int> vec1, std::vector<int> vec2) {
  
    auto start = std::chrono::steady_clock::now();

    std::vector<int> vec3 = sum_vec(vec1, vec2);
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "s\t";
}




std::vector<int> sum_n_vec(std::vector<int> vec1, std::vector<int> vec2, std::vector<int> vec3, int& start_index, int& end_index) {
    
    for (int i = start_index; i < end_index; i++) {
        vec3[i] = vec1[i] + vec2[i];
    }
    return vec3;
}




int main()
{
    setlocale(LC_ALL, "russian");

    std::vector<int> el1_1000(1000);
    std::vector<int> el2_1000(1000);

    std::vector<int> el1_10000(10000);
    std::vector<int> el2_10000(10000);

    std::vector<int> el1_100000(100000);
    std::vector<int> el2_100000(100000);

    std::vector<int> el1_1000000(1000000);
    std::vector<int> el2_1000000(1000000);



    std::thread t1;

    t1 = std::thread(num_core);
    t1.join();

    std::cout << "\t   1000\t\t10000\t\t100000\t\t1000000" << std::endl;
    std::cout << "1 потоков ";
    t1 = std::thread(times, el1_1000, el2_1000);
    t1.join();
    t1 = std::thread(times, el1_10000, el2_10000);
    t1.join();
    t1 = std::thread(times, el1_100000, el2_100000);
    t1.join();
    t1 = std::thread(times, el1_1000000, el2_1000000);
    t1.join();

    int start_index = 0;
    int end_index = 0;
    std::vector<int> el3_1000(1000);
    std::vector<int> el3_10000(10000);
    std::vector<int> el3_100000(100000);
    std::vector<int> el3_1000000(1000000);

    //2 потока
    {

        std::cout << std::endl << "2 потоков ";
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads_2;
        for (size_t i = 0; i < 2; ++i)
        {
            start_index = end_index * i;
            end_index = (el1_1000.size() / 2) * (i + 1);
            threads_2.push_back(std::thread(sum_n_vec, el1_1000, el2_1000, el3_1000, std::ref(start_index), std::ref(end_index)));
            threads_2[i].detach();
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";


        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 2; ++i)
        {
            start_index = end_index * i;
            end_index = (el1_10000.size() / 2) * (i + 1);
            threads_2[i] = std::thread(sum_n_vec, el1_10000, el2_10000, el3_10000, std::ref(start_index), std::ref(end_index));
            threads_2[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";


        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 2; ++i)
        {
            start_index = end_index * i;
            end_index = (el1_100000.size() / 2) * (i + 1);
            threads_2[i] = std::thread(sum_n_vec, el1_100000, el2_100000, el3_100000, std::ref(start_index), std::ref(end_index));
            threads_2[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";


        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 2; ++i)
        {
            start_index = end_index * i;
            end_index = (el1_1000000.size() / 2) * (i + 1);
            threads_2[i] = std::thread(sum_n_vec, el1_1000000, el2_1000000, el3_1000000, std::ref(start_index), std::ref(end_index));
            threads_2[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

    }

    //4 потока
    {

        start_index = 0;
        end_index = 0;

        std::cout << std::endl << "4 потоков ";
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads_4;
        for (size_t i = 0; i < 4; ++i)
        {
            start_index = end_index ;
            end_index = (el1_1000.size() / 4) * (i + 1);
            threads_4.push_back(std::thread(sum_n_vec, el1_1000, el2_1000, el3_1000, std::ref(start_index), std::ref(end_index)));
            threads_4[i].detach();
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 4; ++i)
        {
            start_index = end_index ;
            end_index = (el1_10000.size() / 4) * (i + 1);
            threads_4[i] = std::thread(sum_n_vec, el1_10000, el2_10000, el3_10000, std::ref(start_index), std::ref(end_index));
            threads_4[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        start_index = 0; 
        end_index = 0; 

        start = std::chrono::steady_clock::now(); 
        for (size_t i = 0; i < 4; ++i)
        {
            start_index = end_index;
            end_index = (el1_100000.size() / 4) * (i + 1);
            threads_4[i] = std::thread(sum_n_vec, el1_100000, el2_100000, el3_100000, std::ref(start_index), std::ref(end_index));
            threads_4[i].detach();
        }

        end = std::chrono::steady_clock::now(); 
        elapsed_seconds = end - start; 
        std::cout << elapsed_seconds.count() << "s\t"; 

        start_index = 0; 
        end_index = 0; 

        start = std::chrono::steady_clock::now(); 
        for (size_t i = 0; i < 4; ++i) 
        {
            start_index = end_index;
            end_index = (el1_1000000.size() / 4) * (i + 1);
            threads_4[i] = std::thread(sum_n_vec, el1_1000000, el2_1000000, el3_1000000, std::ref(start_index), std::ref(end_index));
            threads_4[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";
    }

    //8 потоков
    {

        start_index = 0;
        end_index = 0;

        std::cout << std::endl << "8 потоков ";
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads_8;
        for (size_t i = 0; i < 8; ++i)
        {
            start_index = end_index;
            end_index = (el1_1000.size() / 8) * (i + 1);
            threads_8.push_back(std::thread(sum_n_vec, el1_1000, el2_1000, el3_1000, std::ref(start_index), std::ref(end_index)));
            threads_8[i].detach();
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 8; ++i)
        {
            start_index = end_index;
            end_index = (el1_10000.size() / 8) * (i + 1);
            threads_8[i] = std::thread(sum_n_vec, el1_10000, el2_10000, el3_10000, std::ref(start_index), std::ref(end_index));
            threads_8[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 8; ++i)
        {
            start_index = end_index;
            end_index = (el1_100000.size() / 8) * (i + 1);
            threads_8[i] = std::thread(sum_n_vec, el1_100000, el2_100000, el3_100000, std::ref(start_index), std::ref(end_index));
            threads_8[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 8; ++i)
        {
            start_index = end_index;
            end_index = (el1_1000000.size() / 8) * (i + 1);
            threads_8[i] = std::thread(sum_n_vec, el1_1000000, el2_1000000, el3_1000000, std::ref(start_index), std::ref(end_index));
            threads_8[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        
    }

    //16 потоков
    {
        start_index = 0;
        end_index = 0;

        std::cout << std::endl << "16 потоков ";
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads_16;
        for (size_t i = 0; i < 16; ++i)
        {
            start_index = end_index;
            end_index = (el1_1000.size() / 16) * (i + 1);
            threads_16.push_back(std::thread(sum_n_vec, el1_1000, el2_1000, el3_1000, std::ref(start_index), std::ref(end_index)));
            threads_16[i].detach();
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 16; ++i)
        {
            start_index = end_index;
            end_index = (el1_10000.size() / 16) * (i + 1);
            threads_16[i] = std::thread(sum_n_vec, el1_10000, el2_10000, el3_10000, std::ref(start_index), std::ref(end_index));
            threads_16[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";
        
        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 16; ++i)
        {
            start_index = end_index;
            end_index = (el1_100000.size() / 16) * (i + 1);
            threads_16[i] = std::thread(sum_n_vec, el1_100000, el2_100000, el3_100000, std::ref(start_index), std::ref(end_index));
            threads_16[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";
        
        start_index = 0;
        end_index = 0;

        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < 16; ++i)
        {
            start_index = end_index;
            end_index = (el1_1000000.size() /16) * (i + 1);
            threads_16[i] = std::thread(sum_n_vec, el1_1000000, el2_1000000, el3_1000000, std::ref(start_index), std::ref(end_index));
            threads_16[i].detach();
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";
    
    }
    
    return 0;
}
