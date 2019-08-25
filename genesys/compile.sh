echo "Compiling source files" 
sources=`ls *.cpp`
for f in $sources
do
   fobj=$(echo "$f" | cut -f 1 -d '.').o
   #echo "$f => $fobj"
   if [ "$f" -nt "$fobj" ]
   then
      echo "g++ -fpermissive -c -std=c++11 -o $fobj $f"
      g++ -fpermissive -c -std=c++11 -o $fobj $f
   fi
   #echo "g++ -fpermissive -c -std=c++11 $f"
   #g++ -fpermissive -c -std=c++11 $f
done



echo "Linking object files"
objects=`ls *.o parserBisonFlex/*.o`
echo "g++ -fpermissive *.o -o myregenesysapplication.out"
g++ -fpermissive $objects -o myregenesysapplication.out

