#! /bin/bash  
for f in $(find . -name '*.c' -or -name '*.cpp' -or -name '*.h' -or -name '*.cc' -or -name '*.hpp' -type f)  
do  
     astyle --style=mozilla -pP -H -xL $f  
done  
  
for f in $(find . -name '*.orig' -type f)  
do  
     rm $f  
done 