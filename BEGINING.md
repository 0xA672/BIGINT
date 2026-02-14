This is our big integer library, meow!!

We've wrapped a layer around the obscure Boost.Multiprecision to provide a `Bigint` type for representing big integers.  
After completing the setup, you only need one line `#include "bigint.hpp"` to start using our library~  

[![C++17](https://img.shields.io/badge/C++-17-blue)](https://en.cppreference.com/w/cpp/17)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Boost](https://img.shields.io/badge/Boost-1.75+-orange)](https://www.boost.org/)

If your system is Debian or Ubuntu (including WSL), you can copy and run the following commands step by step:  
`sudo apt update`  
Enter your password to update the download list!  
`sudo apt install libboost-all-dev`  
Install the Boost headers — this step is essential!  
`sudo apt install libgmp3-dev`  
Optionally install GMP for faster computation!!

If your system is macOS:  
We recommend installing Homebrew if you don’t have it yet!  
`/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`  
Then run:  
`brew install boost`  
If you want to speed up calculations, you can also install GMP:  
`brew install gmp`

For other users (e.g., Windows), you can ask AI assistants like Deepseek for help.

Once the environment is ready, you can obtain `bigint.hpp` in two ways:  
1. Click `bigint.hpp` in the repository, then click the **Raw** button in the top-right corner, and right-click to save as `bigint.hpp`.  
2. Copy and run:  
   `git clone https://gitee.com/cero0xA672/BIGINT.git`  
   `cd BIGINT`

Next, make sure `bigint.hpp` is in the same directory as your project file.  
In your project source file, write `#include "bigint.hpp"` — and you're ready to use our library!  

You can use `BigInt` just like you would with ordinary unsigned integer types.  
For more detailed usage, see README.md.

After that, compile your file with the following command:  
`g++ -std=c++17 your_project_file.cpp -o your_output_filename && ./your_output_filename`  
Make sure both instances of `your_output_filename` are the same.

If GMP is already installed on your system, you'll need to add two extra flags when compiling:  
`g++ -std=c++17 your_project_file.cpp -o your_output_filename -lgmp -lgmpxx && ./your_output_filename`

Encountered an error?  
`'g++' is not recognized as an internal or external command`: You don't have a compiler installed — if you're unsure what to do, ask an AI for help!  
`fatal error: bigint.hpp: No such file or directory`: `bigint.hpp` is not in the same directory as your project file! Move it to the project directory!  
`#error "This header requires Boost 1.75 or higher"`: Please install the latest Boost!
