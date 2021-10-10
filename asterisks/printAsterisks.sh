n=$1
str=""
end=$n
for i in $(seq 1 $n); do
    str="$str*"
    echo "$str"
done
echo
 
echo "$str"
for i in $(seq 1 $end); do
    echo "${str::-$i}"
done
 
str=""
for i in $(seq 1 $end); do
    str=""
    inner_end=$(($n-$i))
    for j in $(seq 1 $inner_end); do
        str="$str "
    done
    
    str1=""
    for j in $(seq 1 $i); do
        str1="$str1*"
    done
    
    echo "$str$str1"
done
 
echo
 
str=""
for i in $(seq 1 $end); do
    str=""
    inner_end=$(($n-$i))
    for j in $(seq 1 $inner_end); do
        str="$str "
    done
    str1=""
    inner_end=$(( 2*$i-1 ))
    for j in $(seq 1 $inner_end); do
        str1="$str1*"
    done
    echo "$str$str1"
done
 
end=$(($end-1))
for i in $(seq 1 $end); do
    str=""
    for j in $(seq 1 $i); do
        str="$str "
    done
    
    str1=""
    inner_end=$((2*$end-2*$i+1))
    for j in $(seq 1 $inner_end); do
        str1="$str1*"
    done
    
    echo "$str$str1"
done