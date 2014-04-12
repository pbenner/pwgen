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
using namespace boost::python;

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
generate_password(size_t seed_init, string key, string domain, size_t length)
{
        boost::uniform_int<> char_range(33, 126);
        boost::random::mt19937 gen;
        gen.seed(generate_seed(seed_init, key, domain));
        stringstream ss;

        for (uint32_t i = 0; i < length; i++) {
                ss << static_cast<char>(char_range(gen));
        }
        return ss.str();
}

// interface
////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MODULE(pwgen)
{
        def("generate_password", generate_password);
}
