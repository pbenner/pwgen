/* Copyright (C) 2014 Philipp Benner
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <iostream>
#include <string>

#include <termios.h>
#include <inttypes.h>
#include <getopt.h>

#include <boost/random.hpp>

#define SEED_INIT 0x8f2729ba

using namespace std;

// options
////////////////////////////////////////////////////////////////////////////////

typedef struct _options_t {
        size_t length;
        _options_t()
                : length(20)
                { }
} options_t;

static options_t options;

// usage
////////////////////////////////////////////////////////////////////////////////

static
void print_usage(char *pname, FILE *fp)
{
        (void)fprintf(fp, "\nUsage: %s [OPTION]\n\n", pname);
        (void)fprintf(fp,
                      "Options:\n"
                      "   --length, -l integer       - length of the password\n"
                      "\n"
                      "   --help                     - print help and exit\n"
                      "   --version                  - print version information and exit\n\n");
}

static
void wrong_usage(const char *msg)
{
        if(msg != NULL) {
                (void)fprintf(stderr, "%s\n", msg);
        }
        (void)fprintf(stderr,
                      "Try `tfbayes-generate-alignment --help' for more information.\n");

        exit(EXIT_FAILURE);
}

static
void print_version(FILE *fp)
{
        (void)fprintf(fp,
                      "This is free software, and you are welcome to redistribute it\n"
                      "under certain conditions; see the source for copying conditions.\n"
                      "There is NO warranty; not even for MERCHANTABILITY or FITNESS\n"
                      "FOR A PARTICULAR PURPOSE.\n\n");
}

// password generator
////////////////////////////////////////////////////////////////////////////////

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
        uint64_t seed = SEED_INIT;

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

        for (uint32_t i = 0; i < options.length; i++) {
                cout << static_cast<char>(char_range(gen));
        }
        cout << endl;
}

// main
////////////////////////////////////////////////////////////////////////////////

int
main(int argc, char *argv[])
{
        vector<string> tokens;

        for(;;) {
                int c, option_index = 0;
                static struct option long_options[] = {
                        { "length",          1, 0, 'l' },
                        { "help",            0, 0, 'h' },
                        { "version",         0, 0, 'v' }
                };

                c = getopt_long(argc, argv, "l:hv",
                                long_options, &option_index);

                if(c == -1) {
                        break;
                }

                switch(c) {
                case 'l':
                        options.length = atoi(optarg);
                        break;
                case 'h':
                        print_usage(argv[0], stdout);
                        exit(EXIT_SUCCESS);
                case 'v':
                        print_version(stdout);
                        exit(EXIT_SUCCESS);
                default:
                        wrong_usage(NULL);
                        exit(EXIT_FAILURE);
                }
        }
        if(optind != argc) {
                wrong_usage("Wrong number of arguments.");
                exit(EXIT_FAILURE);
        }
        generate_password();

        return 0;
}
