#include<cstdio>
#include<cstdlib>
#include<chrono>

namespace cx{
    class timer{
        private:
        std::chrono::time_point<std::chrono::high_resolution_clock>lap;
        public:
        timer(){
            lap=std::chrono::high_resolution_clock::now();
        }
        void start(){
            lap=std::chrono::high_resolution_clock::now();
        }
        void reset(){
            lap=std::chrono::high_resolution_clock::now();
        }
       double lap_us(){
        auto old_lap=lap;
        lap=std::chrono::high_resolution_clock::now();
        std::chrono::duration<double,std::micro> elapsed=lap-old_lap;
        return elapsed.count();
       }
       double lap_ms(){
        auto old_lap=lap;
        lap=std::chrono::high_resolution_clock::now();
        std::chrono::duration<double,std::milli> elapsed=lap-old_lap;
        return elapsed.count();
       }
    };

}