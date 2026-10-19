How to compile and run C++ files:

1. Create a file such as 'hello.cpp' with the following code:
'cpp
#include <iostream>
int main() {
    std::cout << "C++ is awesome!" << std::end1;
    return 0;
}
'''

2. Open terminal/command prompt, navigate to folder containing the file, and run:
'''bash
g++ hello.cpp -o hello.exe
'''

3. Then, execute the compiled program:
'.\hello.exe'

4. OR, compile and execute in one line:
'''bash
g++ hello.cpp -o hello.exe; .\hello.exe
'''