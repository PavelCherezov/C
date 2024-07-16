#!/bin/bash

COUNTER=0
SUCCESS=0
FAIL=0
DIFF_RES=""

declare -a tests=(
"VAR test.txt"
)


 testing() {
    t=$(echo $@ | sed "s/VAR/$var/")
    ./cat $t > test_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
      if [ "$DIFF_RES" == "Files test_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "\tSUCCESS cat $t"
    else
      (( FAIL++ ))
        echo "\tFAIL cat $t"
    fi
    rm test_cat.log test_sys_cat.log
}

for var1 in b e n s t
do
   for i in "${tests[@]}"
   do
       echo
       echo "Test number $COUNTER: -$var1"
       var="-$var1"
       testing $i
   done
done


for var1 in b e n s t
do 
  for i in "${tests[@]}"
  do
   var="-$var1 "
   testing $i
  done
done


for var1 in b e n s t
 do 
  for var2 in b e n s t
   do
    for i in "${tests[@]}"
     do
       var="-$var1 -$var2"
       testing $i
    done
  done
done

for var1 in b e n s t
 do
  for var2 in b e n s t
   do
    for var3 in b e n s t
     do
      for i in "${tests[@]}"
       do
        var="-$var1 -$var2 -$var3"
        testing $i
      done
    done
  done
done

for var1 in b e n s t
 do
  for var2 in b e n s t
   do
    for var3 in b e n s t
     do
      for var4 in b e n s t
       do
        for i in "${tests[@]}"
        do
        var="-$var1 -$var2 -$var3 -$var4"
        testing $i
        done
      done
    done
  done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"