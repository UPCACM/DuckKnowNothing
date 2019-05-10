#!/bin/bash
g++ gen.cpp -o gen
g++ std.cpp -o std
g++ user.cpp -o user
while true; do
	./gen > data.in
	./std < data.in > std.out
	./user < data.in > user.out
	if diff std.out user.out; then
		date
	else
		printf "WA\n"
		exit 0
	fi
done