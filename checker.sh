echo "compiling..."
if !(g++ gen.cpp -o gen.out && g++ code1.cpp -o code1.out && g++ code2.cpp -o code2.out)
then
	echo "compilation failed, program exiting..."
	exit
fi

printf "enter number of attempts:"
read N

RAND_FILE=rand.txt
i=1
while [ $i -le $N ];
do
	FILENAME=attempt_${i}.txt
	printf "attempt `echo $i`: generating..."
	echo $i > $RAND_FILE
	./gen.out < $RAND_FILE > $FILENAME
	printf "code1 running..."
	./code1.out < $FILENAME > code1_output.txt
	printf "code2 running..."
	./code2.out < $FILENAME > code2_output.txt

	if diff code1_output.txt code2_output.txt
	then
		printf "passed.\n"
		rm $FILENAME
	else
		printf "OUTPUT NOT IDENTICAL!\n"
	fi

	i=$((i+1))
done

rm code1_output.txt code2_output.txt
