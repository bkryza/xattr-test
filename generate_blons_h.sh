#!/bin/bash

BLNS=$(curl https://raw.githubusercontent.com/minimaxir/big-list-of-naughty-strings/master/blns.txt)

echo "/*"
echo " Big list of naughty strings"
echo " Generated from https://github.com/minimaxir/big-list-of-naughty-strings"
echo "*/"
echo ""
echo "#pragma once"
echo "#include <string>"
echo "#include <vector>"
echo "std::vector<std::string> big_list_of_naughty_strings = {"

for naughty_string in $BLNS; do
    if [ "$naughty_string" != "" ] && [ ${naughty_string:0:1} != '#' ]; then
        echo '    R"###('$naughty_string')###",'
    fi
done

echo '    R"###()###"};'
