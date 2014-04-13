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

#include <Python.h>

#include <locale>
#include <cctype>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/python.hpp>
#include <boost/python/def.hpp>

#include <boost/format.hpp>
#include <boost/random.hpp>

using namespace std;

// alphabets
////////////////////////////////////////////////////////////////////////////////

static const char any[] =
        "!\"#$%&'()*+,-./"
        "0123456789"
        ":;<=>?@"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "[\\]^_`"
        "abcdefghijklmnopqrstuvwxyz"
        "{|}~";
static const char alpha[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
static const char numeric[] =
        "0123456789";
static const char alphanumeric[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
static const char sunrise[] =
        "$%&#()?!=[]<>*_+-.,:;"
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

// password generator
////////////////////////////////////////////////////////////////////////////////

inline void hash_combine(uint64_t& seed, uint64_t const& v)
{
        seed ^= v + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

size_t
generate_seed(size_t seed_init, string key, string domain)
{
        uint64_t seed = seed_init;

        for (size_t i = 0; i < key.size(); i++)
                hash_combine(seed, static_cast<uint64_t>(key[i]));
        for (size_t i = 0; i < domain.size(); i++)
                hash_combine(seed, static_cast<uint64_t>(domain[i]));

        return seed;
}

string
generate_password(size_t seed_init, string key, string domain, size_t length, string alphabet)
{
        const char *alphabet_ptr;

        boost::uniform_int<> range;
        if (alphabet == "any") {
                range = boost::uniform_int<>(0, sizeof(any)-2);
                alphabet_ptr = any;
        }
        else if (alphabet == "alpha") {
                range = boost::uniform_int<>(0, sizeof(alpha)-2);
                alphabet_ptr = alpha;
        }
        else if (alphabet == "numeric") {
                range = boost::uniform_int<>(0, sizeof(numeric)-2);
                alphabet_ptr = numeric;
        }
        else if (alphabet == "alphanumeric") {
                range = boost::uniform_int<>(0, sizeof(alphanumeric)-2);
                alphabet_ptr = alphanumeric;
        }
        else if (alphabet == "sunrise") {
                range = boost::uniform_int<>(0, sizeof(sunrise)-2);
                alphabet_ptr = sunrise;
        }
        else {
                return "";
        }

        boost::random::mt19937 gen;
        gen.seed(generate_seed(seed_init, key, domain));
        stringstream ss;

        for (size_t i = 0; i < length; i++) {
                ss << alphabet_ptr[range(gen)];
        }
        return ss.str();
}

// interface
////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MODULE(pwgen)
{
        boost::python::def("generate_password", generate_password);
}
