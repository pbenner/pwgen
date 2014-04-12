#include <iostream>
#include <string>
#include <termios.h>
#include <inttypes.h>

#include <boost/random.hpp>

#define PWLENGTH 20

using namespace std;

inline void hash_combine(uint64_t& seed, uint64_t const& v)
{
        seed ^= v + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

string
read_key(void)
{
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        string input = "";
        cout << "Private key: ";
        
        getline(cin, input);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        cout << endl;

        return input;
}

string
read_domain(void)
{
        string input = "";
        cout << "Domain: ";
        
        getline(cin, input);

        return input;
}

size_t
generate_seed(void)
{
        uint64_t seed = 0;

        string key = read_key();
        string domain = read_domain();

        for (size_t i = 0; i < key.size(); i++)
                hash_combine(seed, static_cast<uint64_t>(key[i]));
        for (size_t i = 0; i < domain.size(); i++)
                hash_combine(seed, static_cast<uint64_t>(domain[i]));

        return seed;
}

void
generate_password(void)
{
        boost::uniform_int<> char_range(33, 126);
        boost::random::mt19937 gen;
        gen.seed(generate_seed());

        for (uint32_t i = 0; i < PWLENGTH; i++) {
                cout << static_cast<char>(char_range(gen));
        }
        cout << endl;
}

int
main(void)
{
        generate_password();
}
