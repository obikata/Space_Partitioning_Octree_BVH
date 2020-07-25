#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#include <string>
#include <vector>
#include <fstream>

namespace Utils
{
    class HELPER
    {
    public:

        static const std::vector<float> array_int2float(const int* ai) 
        {
            std::vector<float> af (sizeof(ai)/sizeof(ai[0]));
            for (int i = 0; i < sizeof(ai)/sizeof(ai[0]); i++)
            {
                af[i] = (float)ai[i];
            }
        }

        template<typename T>
        static const T max(const T* numbers) 
        {
            T maxValue = numbers[0];  
            for (int i = 1; i < sizeof(numbers)/sizeof(numbers[0]); i++)
            {  
                if (numbers[i] > maxValue)
                {  
                    maxValue = numbers[i];
                }
            }  
            return maxValue;
        }

        template<typename T>
        static const T min(const T* numbers)
        {  
            T minValue = numbers[0];  
            for (int i = 1; i < sizeof(numbers)/sizeof(numbers[0]); i++) {  
                if (numbers[i] < minValue) {  
                    minValue = numbers[i];
                }
            }  
            return minValue;
        }

        static const std::vector<std::string> readASCIIfile(const char* filename)
        {
          //http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
          std::ifstream in(filename, std::ios::in | std::ios::binary);
          std::vector<std::string> lines;
          if (in)
          {
              std::string line;
              while (std::getline(in, line, '\n'))
              {
                  if(line.size() > 0)
                  {
                      lines.push_back(line);                
                  }
              }
          }
          return(lines);
        //   throw(errno);
        }

        static const float string2float(const std::string s)
        {
            return std::stof(s);
        }

        static const int string2integer(const std::string s)
        {
            return std::stoi(s);
        }

        static const bool endWith(const std::string &mainStr, const std::string &toMatch)
        {
            if(mainStr.size() >= toMatch.size() && mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };
}

#endif