#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using std::vector, std::string, std::cout, std::cin;

////////////////////////////////////////////////////////////////////////////////
// TODO: add floating point numbers conversion

bool check_fp(string num) {
    return num.find('.') != string::npos;
}

vector<string> split_str(string str, char delimiter = '.') {
    string token;
    vector<string> result;
    for (const auto &ch : str) {
        if (ch == delimiter) {
            result.push_back(token);
            token.clear();
        }
        token.push_back(ch);
    }
    result.push_back(token);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

// base_from => dec => base_to
string convert(string token, int base_from, int base_to) {
    if (base_from == base_to)
        return token;

    // check if valid
    for (const auto &ch : token) {
        if (base_from <= 10 && base_from > 1) {
            if (isdigit(ch) && (ch - '0') >= base_from)
                return "this number is not a base " + std::to_string(base_from);
            else if (!isdigit(ch))
                return "[Error] only digits allowed";
        }
        else if (base_from > 10) {
            if (isdigit(ch) && (ch - '0') >= base_from)
                return "[Error] this number is not a base " + std::to_string(base_from);
            else if (isalpha(ch)) {
                if (ch > 'Z')
                    return "[Error] only Capital letters allowed";
                else if ((ch - 55) >= base_from)
                    return "[Error] this number is not a base " + std::to_string(base_from);
            }
        }
    }

    // base_from => decimal
    int dec_int {};
    for (int i = (int)token.size() - 1, idx = 0; i >= 0 ; i--, idx++) {
        if (isdigit(token.at(i)))
            dec_int += (token.at(i) - '0') * std::pow(base_from, idx);
        else if (isalpha(token.at(i))) {
            dec_int += (token.at(i) - 55) * std::pow(base_from, idx);
        }
    }

    if (base_to == 10)
        return std::to_string(dec_int);

    // decimal => base_to
    string final_res;
    int next { dec_int };
    while (true) {
        if ((next % base_to) < 10)
            final_res.push_back((next % base_to) + '0');
        else 
            final_res.push_back((char)(next % base_to) + 55);
        next /= base_to;
        if (next < base_to) {
            break;
        }
    }
    final_res.push_back(next + '0');
    std::reverse(final_res.begin(), final_res.end());

    std::ostringstream oss;
    oss << "[base " << base_to << "] " << final_res;

    return oss.str();
}

int main() 
{
    string number {};
    int base_from {};
    int base_to {};
    cout << "Enter <number> <base_from> <base_to> : ";
    cin >> number >> base_from >> base_to;

    cout << "\n" << convert(number, base_from, base_to) << "\n";
    return 0;
}
