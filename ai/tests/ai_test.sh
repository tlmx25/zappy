#!/bin/bash

#Result
test_succ=0
test_fail=0

#Color
jaune="\e[33m"
vert="\e[32m"
rouge="\e[31m"
gras="\033[1m"
end_gras="\033[0m"
end_color="\e[0m"

inputs=(
    "host localhost"
)

expected_outputs=(
    "Host successfully set."
)

# Tester
run_test() {
    echo -e "$jaune  > Test [$1] => [$2]$end_color"
    tmp_file=$(mktemp)
    echo -e "$1\nstop\n" > $tmp_file
    output=$(./tests/zappy_ai_test < $tmp_file 2>&1 > /dev/null)
    if [[ $output == $2 ]]; then
        echo -e "\t$vert$gras> Test passed\n$end_color"
        ((test_succ++))
    else
        echo -e "\t$rouge> Test fail\n$end_color"
        ((test_fail++))
    fi
    rm $tmp_file
}

#Test runner
echo -e "$gras[=========================== HISTORY ===========================]\n$end_gras"
for ((i = 0; i < "${#inputs[@]}"; i++)); do
    run_test "${inputs[i]}" "${expected_outputs[i]}"
done
echo -e "$gras[===============================================================]\n$end_gras"

#Result
echo -e "$gras[=========================== RESULT ===========================]\n"
echo -e "\t\t   [Succes : $vert$test_succ$end_color$gras || Fail : $rouge$test_fail$end_color$gras]\n"
echo -e "[==============================================================]$end_gras"
